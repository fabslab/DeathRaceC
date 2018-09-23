#include "GameBounds.h"
#include "Components.h"
#include "GameConstants.h"
#include "GraphicsUtil.h"

using namespace GameConstants;

void GameBounds::Init(ECS::World* world)
{
    auto borderLeft = world->create();
    borderLeft->assign<Components::CollisionComponent>(BORDER_WIDTH, GAME_BOUNDS.height, true, CollisionLayer::GameBounds, CollisionLayer::All);
    borderLeft->assign<Components::Transform2DComponent>(Vector2{ GAME_BOUNDS.x + BORDER_WIDTH / 2, GAME_BOUNDS.y + GAME_BOUNDS.height / 2 });
    auto borderRight = world->create();
    borderRight->assign<Components::CollisionComponent>(BORDER_WIDTH, GAME_BOUNDS.height, true, CollisionLayer::GameBounds, CollisionLayer::All);
    borderRight->assign<Components::Transform2DComponent>(Vector2{ GAME_BOUNDS.x + GAME_BOUNDS.width - BORDER_WIDTH / 2, GAME_BOUNDS.y + GAME_BOUNDS.height / 2 });
    auto borderTop = world->create();
    borderTop->assign<Components::CollisionComponent>(GAME_BOUNDS.width, BORDER_WIDTH, true, CollisionLayer::GameBounds, CollisionLayer::All);
    borderTop->assign<Components::Transform2DComponent>(Vector2{ GAME_BOUNDS.x + GAME_BOUNDS.width / 2, GAME_BOUNDS.y + BORDER_WIDTH / 2 });
    auto borderBottom = world->create();
    borderBottom->assign<Components::CollisionComponent>(GAME_BOUNDS.width, BORDER_WIDTH, true, CollisionLayer::GameBounds, CollisionLayer::All);
    borderBottom->assign<Components::Transform2DComponent>(Vector2{ GAME_BOUNDS.x + GAME_BOUNDS.width / 2, GAME_BOUNDS.y + GAME_BOUNDS.height - BORDER_WIDTH / 2 });

    auto leftSidewalk = world->create();
    leftSidewalk->assign<Components::EnemySafeAreaComponent>();
    leftSidewalk->assign<Components::CollisionComponent>(SIDEWALK_WIDTH, GAME_BOUNDS.height, true, CollisionLayer::Sidewalk, CollisionLayer::Player);
    leftSidewalk->assign<Components::Transform2DComponent>(Vector2{ GAME_BOUNDS.x + SIDEWALK_WIDTH / 2, GAME_BOUNDS.y + GAME_BOUNDS.height / 2 });
    auto rightSidewalk = world->create();
    rightSidewalk->assign<Components::EnemySafeAreaComponent>();
    rightSidewalk->assign<Components::CollisionComponent>(SIDEWALK_WIDTH, GAME_BOUNDS.height, true, CollisionLayer::Sidewalk, CollisionLayer::Player);
    rightSidewalk->assign<Components::Transform2DComponent>(Vector2{ GAME_BOUNDS.x + GAME_BOUNDS.width - SIDEWALK_WIDTH / 2, GAME_BOUNDS.y + GAME_BOUNDS.height / 2 });
}

void GameBounds::Draw()
{
    DrawRectangleLinesEx(GAME_BOUNDS, BORDER_WIDTH, WHITE);

    float sidewalkStartY = SCOREBOARD_HEIGHT + BORDER_WIDTH * 3;
    float sidewalkEndY = sidewalkStartY + GAME_BOUNDS.height - BORDER_WIDTH * 3;

    float sidewalkLeftX = SIDEWALK_WIDTH;
    float sidewalkRightX = GAME_BOUNDS.width - SIDEWALK_WIDTH;

    Vector2 sidewalkLeftStartPos = Vector2{ sidewalkLeftX, sidewalkStartY };
    Vector2 sidewalkLeftEndPos = Vector2{ sidewalkLeftX, sidewalkEndY };

    Vector2 sidewalkRightStartPos = Vector2{ sidewalkRightX, sidewalkStartY };
    Vector2 sidewalkRightEndPos = Vector2{ sidewalkRightX, sidewalkEndY };

    GraphicsUtil::DrawDottedLine(sidewalkLeftStartPos, sidewalkLeftEndPos, BORDER_WIDTH, WHITE);
    GraphicsUtil::DrawDottedLine(sidewalkRightStartPos, sidewalkRightEndPos, BORDER_WIDTH, WHITE);
}
