#include "ScoreRenderSystem.h"
#include "Components.h"
#include "Constants.h"
#include "Events.h"
#include "GameState.h"
#include "GraphicsUtil.h"
#include <algorithm>
#include <cmath>
#include <string>

ScoreRenderSystem::ScoreRenderSystem(float gameTime)
    : gameTime(gameTime)
{
}

void ScoreRenderSystem::tick(ECS::World* world, float deltaTime)
{
    gameTime = std::max(gameTime - deltaTime / 1000, 0.f);
    if (gameTime == 0.f) {
        world->emit(Events::GameStateChangedEvent{ GameState::GameOver });
    }

    float fontSize = 32;
    float letterSpacing = 4;
    std::string remainingTime = IntToDisplayString(static_cast<int>(std::round(gameTime)));
    Vector2 textSize = GraphicsUtil::MeasureText(remainingTime, fontSize, letterSpacing);
    GraphicsUtil::DrawText(remainingTime, Vector2{ GameConstants::GAME_BOUNDS.x + GameConstants::GAME_BOUNDS.width / 2 - textSize.x / 2, 0 }, fontSize, letterSpacing);

    world->each<Components::ScoreComponent>(
        [&](ECS::Entity* entity,
            ECS::ComponentHandle<Components::ScoreComponent> scoreComponent) {
            std::string score = IntToDisplayString(scoreComponent->score);
            if (scoreComponent->playerIndex == PlayerIndex::One) {
                GraphicsUtil::DrawText(score, Vector2{ GameConstants::GAME_BOUNDS.x + GameConstants::SIDEWALK_WIDTH + GameConstants::BORDER_WIDTH, 0 }, fontSize, letterSpacing);
            } else if (scoreComponent->playerIndex == PlayerIndex::Two) {
                Vector2 textSize = GraphicsUtil::MeasureText(score, fontSize, letterSpacing);
                GraphicsUtil::DrawText(score, Vector2{ GameConstants::GAME_BOUNDS.x + GameConstants::GAME_BOUNDS.width - GameConstants::SIDEWALK_WIDTH - textSize.x, 0 }, fontSize, letterSpacing);
            }
        });
}

void ScoreRenderSystem::SetGameTime(float gameTime)
{
    this->gameTime = gameTime;
}

std::string ScoreRenderSystem::IntToDisplayString(int num)
{
    auto str = std::to_string(num);
    if (str.length() < 2) {
        str = "0" + str;
    }
    return str;
}
