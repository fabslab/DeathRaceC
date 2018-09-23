#pragma once

#include "raylib.h"

class Button {
public:
    Button() = default;
    Button(float x, float y, float width, float height, const char* text);
    void Draw();
    void Focus();
    void Unfocus();
    /*void Select();*/

private:
    Color defaultBorderColor = Color{ 100, 100, 100, 255 };
    const char* text;
    Color borderColor = defaultBorderColor;
    float height;
    float width;
    float x;
    float y;
};
