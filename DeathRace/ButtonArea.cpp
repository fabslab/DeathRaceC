#include "ButtonArea.h"

ButtonArea::ButtonArea(MenuOrientation orientation, std::vector<Button*> buttons)
    : buttons(buttons)
    , orientation(orientation)
{
    if (!buttons.empty()) {
        buttons.front()->Focus();
    }
}

void ButtonArea::Update()
{
    if (buttons.empty()) {
        return;
    }

    int previousFocusedIndex = focusedIndex;

    int keyNext;
    int keyPrevious;

    if (orientation == MenuOrientation::Horizontal) {
        keyPrevious = KEY_LEFT;
        keyNext = KEY_RIGHT;
    } else if (orientation == MenuOrientation::Vertical) {
        keyPrevious = KEY_UP;
        keyNext = KEY_DOWN;
    }

    if (IsKeyPressed(keyPrevious) && focusedIndex > 0) {
        focusedIndex--;
    }
    if (IsKeyPressed(keyNext) && focusedIndex < buttons.size() - 1) {
        focusedIndex++;
    }

    if (previousFocusedIndex != focusedIndex) {
        buttons[previousFocusedIndex]->Unfocus();
        buttons[focusedIndex]->Focus();
    }
}

void ButtonArea::Draw()
{
    for (Button* button : buttons) {
        button->Draw();
    }
}

Button* ButtonArea::GetFocusedButton()
{
    return buttons[focusedIndex];
}
