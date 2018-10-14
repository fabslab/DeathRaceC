#include "ScoreRenderSystem.h"
#include "Components.h"
#include "EnemyMovementSystem.h"
#include "Entities.h"
#include "Events.h"
#include "Fonts.h"
#include "GameAudio.h"
#include "GameConstants.h"
#include "GameState.h"
#include "GameStateChangedEventSubscriber.h"
#include "GraphicsUtil.h"
#include <algorithm>
#include <cmath>
#include <string>

void ScoreRenderSystem::configure(ECS::World* world)
{
    Reset();
    world->subscribe<Events::GameStateChangedEvent>(this);
    world->subscribe<Events::CollisionEnteredEvent>(this);
}

void ScoreRenderSystem::unconfigure(ECS::World* world)
{
    world->unsubscribeAll(this);
}

void ScoreRenderSystem::receive(ECS::World* world, const Events::GameStateChangedEvent& event)
{
    if (event.state == GameState::MainMenu) {
        Reset();
    }
}

void ScoreRenderSystem::receive(ECS::World* world, const Events::CollisionEnteredEvent& event)
{
    auto firstEntity = event.firstEntity;
    auto secondEntity = event.secondEntity;
    auto playerMovementComponent = firstEntity->get<Components::PlayerMovementComponent>();
    if (playerMovementComponent) {
        if (secondEntity->get<Components::EnemyMovementComponent>()) {
            if (!EnemyMovementSystem::IsEnemySafe(world, secondEntity)) {
                KillEnemy(world, secondEntity, firstEntity);
            }
        }
    }
}

void ScoreRenderSystem::tick(ECS::World* world, float deltaTime)
{
    Update(world, deltaTime);
    Draw();
}

void ScoreRenderSystem::Update(ECS::World* world, float deltaTime)
{
    auto gameState = GameStateChangedEventSubscriber::GetGameState();
    if (gameState != GameState::GameRunning) {
        return;
    }

    world->each<Components::ScoreComponent>(
        [&](ECS::Entity* entity,
            ECS::ComponentHandle<Components::ScoreComponent> scoreComponent) {
            SetScore(scoreComponent->playerIndex, scoreComponent->score);
        });

    gameTime = std::max(gameTime - deltaTime / 1000, 0.f);
    if (gameTime == 0.f) {
        world->emit(Events::GameStateChangedEvent { GameState::GameOver, { player1Score, player2Score } });
    }
}

void ScoreRenderSystem::Draw()
{
    auto gameState = GameStateChangedEventSubscriber::GetGameState();
    if (gameState == GameState::MainMenu) {
        return;
    }

    float fontSize = 32;
    float letterSpacing = 4;
    std::string remainingTime = IntToDisplayString(static_cast<int>(std::ceil(gameTime)));
    Vector2 remainingTimeTextSize = GraphicsUtil::MeasureText(Fonts::defaultFont32px, remainingTime, fontSize, letterSpacing);
    GraphicsUtil::DrawText(Fonts::defaultFont32px, remainingTime, Vector2 { GameConstants::GAME_BOUNDS.x + GameConstants::GAME_BOUNDS.width / 2 - remainingTimeTextSize.x / 2, 0 }, fontSize, letterSpacing, WHITE);

    if (player1Score != -1) {
        std::string player1ScoreDisplay = IntToDisplayString(player1Score);
        GraphicsUtil::DrawText(Fonts::defaultFont32px, player1ScoreDisplay, Vector2 { GameConstants::GAME_BOUNDS.x + GameConstants::SIDEWALK_WIDTH + GameConstants::BORDER_WIDTH, 0 }, fontSize, letterSpacing, WHITE);
    }

    if (player2Score != -1) {
        std::string player2ScoreDisplay = IntToDisplayString(player2Score);
        Vector2 scoreTextSize = GraphicsUtil::MeasureText(Fonts::defaultFont32px, player2ScoreDisplay, fontSize, letterSpacing);
        GraphicsUtil::DrawText(Fonts::defaultFont32px, player2ScoreDisplay, Vector2 { GameConstants::GAME_BOUNDS.x + GameConstants::GAME_BOUNDS.width - GameConstants::SIDEWALK_WIDTH - scoreTextSize.x, 0 }, fontSize, letterSpacing, WHITE);
    }
}

std::string ScoreRenderSystem::IntToDisplayString(int num)
{
    auto str = std::to_string(num);
    if (str.length() < 2) {
        str = "0" + str;
    }
    return str;
}

void ScoreRenderSystem::SetScore(PlayerIndex playerIndex, int score)
{
    if (playerIndex == PlayerIndex::One) {
        player1Score = score;
    } else if (playerIndex == PlayerIndex::Two) {
        player2Score = score;
    }
}

void ScoreRenderSystem::KillEnemy(ECS::World* world, ECS::Entity* enemy, ECS::Entity* player)
{
    PlaySound(GameAudio::scream);
    auto enemyTransformComponent = enemy->get<Components::Transform2DComponent>();
    Entities::CreateTombstone(world, enemyTransformComponent->position);
    EnemyMovementSystem::ResetEnemy(enemy);
    player->get<Components::ScoreComponent>()->score++;
}

void ScoreRenderSystem::Reset()
{
    gameTime = GameConstants::GAME_TIME;
    player1Score = -1;
    player2Score = -1;
}
