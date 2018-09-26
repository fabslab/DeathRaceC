#pragma once

#include "ECS.h"

class IMenu {

public:
    virtual ~IMenu() = default;
    // TODO: add Load method to reset focused button state
    virtual void Update(ECS::World* world) = 0;
    virtual void Draw() = 0;
};
