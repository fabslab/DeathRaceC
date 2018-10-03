#pragma once

#include "AggregatedPlayerInput.h"
#include "Button.h"
#include "ControllerPlayerInput.h"
#include "KeyboardPlayerInput.h"
#include <vector>

enum class MenuOrientation {
    Horizontal,
    Vertical
};

class ButtonArea {
public:
    ButtonArea(MenuOrientation orientation, std::vector<Button*> buttons);
    ~ButtonArea();
    void Update();
    void Draw();
    Button* GetFocusedButton();
    void SetFocus(int focusIndex);
    void ResetFocus();

private:
    int focusedIndex;
    std::vector<Button*> buttons;
    MenuOrientation orientation;
    AggregatedPlayerInput inputAggregator;
    KeyboardPlayerInput* keyboardInput;
    ControllerPlayerInput *controllerInputOne, *controllerInputTwo;
};
