#include "Button.h"
#include "Fonts.h"
#include "GraphicsUtil.h"

Button::Button(const char* text)
    : text(text)
{
}

void Button::SetPosition(Vector2 position)
{
    x = position.x;
    y = position.y;
}

void Button::Draw()
{
    int borderWidth = 2;
    Rectangle border = Rectangle { x, y, width, height };
    DrawRectangleRec(border, BLACK);
    DrawRectangleLinesEx(border, borderWidth, borderColor);

    float fontSize = 14.f;
    float letterSpacing = 2.f;
    Vector2 textSize = GraphicsUtil::MeasureText(Fonts::defaultFont14px, text, fontSize, letterSpacing);
    float textX = x + (width / 2 - textSize.x / 2);
    float textY = y + (height / 2 - Fonts::defaultFont14px.baseSize / 2);
    GraphicsUtil::DrawText(Fonts::defaultFont14px, text, Vector2 { textX, textY }, fontSize, letterSpacing, WHITE);
}

void Button::Focus()
{
    borderColor = focusedBorderColor;
}

void Button::Unfocus()
{
    borderColor = defaultBorderColor;
}
