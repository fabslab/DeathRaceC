#include "AnimationSystem.h"
#include "Components.h"
#include "GameState.h"
#include "GameStateChangeEventSubscriber.h"

void AnimationSystem::tick(ECS::World* world, float deltaTime)
{
    auto gameState = GameStateChangeEventSubscriber::GetGameState();
    if (!(gameState == GameState::GameRunning || gameState == GameState::GameOver)) {
        return;
    }

    world->each<Components::TextureAnimationComponent, Components::TextureComponent>(
        [&](ECS::Entity* entity,
            ECS::ComponentHandle<Components::TextureAnimationComponent> animationComponent,
            ECS::ComponentHandle<Components::TextureComponent> textureComponent) {
            animationComponent->remainingFrameTime -= deltaTime;
            if (animationComponent->remainingFrameTime <= 0) {
                ++animationComponent->currentFrameIndex %= animationComponent->frameCount;
                textureComponent->sourceRect.x = animationComponent->currentFrameIndex * textureComponent->sourceRect.width;
                animationComponent->remainingFrameTime = animationComponent->frameDurationMs;
            }
        });
}
