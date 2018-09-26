#include "RenderSystem.h"
#include "Components.h"
#include "GameState.h"
#include "GameStateChangedEventSubscriber.h"
#include "MathUtil.h"

void RenderSystem::tick(ECS::World* world, float deltaTime)
{
    world->each<Components::Transform2DComponent, Components::TextureComponent>(
        [&](ECS::Entity* entity,
            ECS::ComponentHandle<Components::Transform2DComponent> transformComponent,
            ECS::ComponentHandle<Components::TextureComponent> textureComponent) {
            Texture2D texture = textureComponent->texture;
            Vector2 position = transformComponent->position;
            Rectangle sourceRect = textureComponent->sourceRect;
            Vector2 origin = Vector2{ sourceRect.width / 2.f, sourceRect.height / 2.f };
            Rectangle destRect = Rectangle{ position.x, position.y, sourceRect.width, sourceRect.height };
            float rotation = transformComponent->rotation;
            auto snappedRotationComponent = entity->get<Components::SnappedRotationComponent>();
            if (snappedRotationComponent) {
                rotation = MathUtil::Snap(rotation, snappedRotationComponent->snapAngle);
            }
            DrawTexturePro(
                texture,
                sourceRect,
                destRect,
                origin,
                rotation * RAD2DEG,
                textureComponent->tint);
        });
}
