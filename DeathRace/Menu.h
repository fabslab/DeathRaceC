#pragma once

#include "AggregatedPlayerInput.h"
#include "Button.h"
#include "ControllerPlayerInput.h"
#include "ECS.h"
#include "KeyboardPlayerInput.h"

class Menu {
public:
    Menu();
    virtual ~Menu();
    // TODO: add Load method to reset focused button state
    virtual void Update(ECS::World* world) = 0;
    virtual void Draw() = 0;

protected:
    AggregatedPlayerInput inputAggregator;
    KeyboardPlayerInput* keyboardInput;
    ControllerPlayerInput *controllerInputOne, *controllerInputTwo;
};
