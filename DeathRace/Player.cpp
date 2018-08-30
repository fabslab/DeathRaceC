#include "Player.h"
#include "Components.h"
#include "Constants.h"
#include "GraphicUtil.h"
#include "MathUtil.h"
#include "Textures.h"
#include "raylib.h"
#include "raymath.h"

Player::Player(ECS::Entity* entity, int playerIndex, Vector2 position, Color color)
{
    entity->assign<Components::Transform2DComponent>(position, PI);
    entity->assign<Components::TextureComponent>(Textures::player, color);
    entity->assign<Components::SnappedRotationComponent>();
    entity->assign<Components::PlayerMovementComponent>(playerIndex, 2.f, 1.f);
    entity->assign<Components::CollisionComponent>(12, 16, CollisionLayer::Player, ~CollisionLayer::None);
}
