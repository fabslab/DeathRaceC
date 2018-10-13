#include "ButtonArea.h"
#include "KeyboardInputMap.h"
#include "PlayerIndex.h"

ButtonArea::ButtonArea(MenuOrientation orientation, std::vector<Button*> buttons)
    : buttons(buttons)
    , orientation(orientation)
{
    keyboardInput = new KeyboardPlayerInput(Input::UI_NAVIGATION);
    controllerInputOne = new ControllerPlayerInput(PlayerIndex::One);
    controllerInputTwo = new ControllerPlayerInput(PlayerIndex::Two);
    inputAggregator.SetInputs({ keyboardInput, controllerInputOne, controllerInputTwo });

    focusedIndex = 0;
    if (!buttons.empty()) {
        buttons[focusedIndex]->Focus();
    }
}

ButtonArea::~ButtonArea()
{
    delete keyboardInput;
    delete controllerInputOne;
    delete controllerInputTwo;
}

void ButtonArea::Update()
{
    Input::InputCommand next;
    Input::InputCommand previous;

    if (orientation == MenuOrientation::Horizontal) {
        next = Input::InputCommand::Right;
        previous = Input::InputCommand::Left;
    } else {
        next = Input::InputCommand::Down;
        previous = Input::InputCommand::Up;
    }

    if (inputAggregator.WasCommandEntered(next)) {
        SetFocus(focusedIndex + 1);
    }
    if (inputAggregator.WasCommandEntered(previous)) {
        SetFocus(focusedIndex - 1);
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

void ButtonArea::SetFocus(int focusIndex)
{
    if (focusedIndex != focusIndex && focusIndex >= 0 && focusIndex < buttons.size()) {
        buttons[focusedIndex]->Unfocus();
        buttons[focusIndex]->Focus();
        focusedIndex = focusIndex;
    }
}

void ButtonArea::ResetFocus()
{
    SetFocus(0);
}
