#include "Menu.h"

Menu::Menu()
{
    keyboardInput = new KeyboardPlayerInput(Input::UI_NAVIGATION);
    controllerInputOne = new ControllerPlayerInput(Input::PS4_GAMEPAD, PlayerIndex::One);
    controllerInputTwo = new ControllerPlayerInput(Input::PS4_GAMEPAD, PlayerIndex::Two);
    inputAggregator.SetInputs({ keyboardInput, controllerInputOne, controllerInputTwo });
}

Menu::~Menu()
{
    delete keyboardInput;
    delete controllerInputOne;
    delete controllerInputTwo;
}
