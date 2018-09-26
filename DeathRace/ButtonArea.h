#pragma once

#include "Button.h"
#include <vector>

enum class MenuOrientation {
    Horizontal,
    Vertical
};

class ButtonArea {
public:
    ButtonArea() = default;
    ButtonArea(MenuOrientation orientation, std::vector<Button*> buttons);
    void Update();
    void Draw();
    Button* GetFocusedButton();

private:
    int focusedIndex = 0;
    std::vector<Button*> buttons;
    MenuOrientation orientation;
};
