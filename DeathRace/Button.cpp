#include "Button.h"
#include "Fonts.h"
#include "GraphicsUtil.h"
#include "raylib.h"

Button::Button(float x, float y, float width, float height, const char* text)
    : height(height)
    , text(text)
    , width(width)
    , x(x)
    , y(y)
{
}

void Button::Draw()
{
    int borderWidth = 2;
    Rectangle border = Rectangle{ x, y, width, height };
    DrawRectangleRec(border, BLACK);
    DrawRectangleLinesEx(border, borderWidth, borderColor);

    float fontSize = 14.f;
    Vector2 textSize = GraphicsUtil::MeasureText(Fonts::defaultFont14px, text, fontSize, 0);
    float textX = x + (width / 2 - textSize.x / 2);
    float textY = y + (height / 2 - Fonts::defaultFont14px.baseSize / 2);
    GraphicsUtil::DrawText(Fonts::defaultFont14px, text, Vector2{ textX, textY }, fontSize, 0);
}

void Button::Focus()
{
    borderColor = focusedBorderColor;
}

void Button::Unfocus()
{
    borderColor = defaultBorderColor;
}
