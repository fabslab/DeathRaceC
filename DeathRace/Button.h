#pragma once

#include "raylib.h"

class Button {
public:
    Button(const char* text);
    void Draw();
    void Focus();
    void Unfocus();
    void SetPosition(Vector2 pos);
    float width = 120.f;
    float height = 30.f;
    float x = 0;
    float y = 0;

private:
    Color defaultBorderColor = Fade(WHITE, .5f);
    Color focusedBorderColor = WHITE;
    Color borderColor = defaultBorderColor;
    const char* text;
};
