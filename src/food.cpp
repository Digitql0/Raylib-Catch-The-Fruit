#include "food.h"
#include "raylib.h"
#include <iostream>

food::food(float x, float y, float w, Color co)
{
    pos = {x, y};
    dim = w;
    color = co;
}

void food::show()
{
    DrawRectangle(pos.x, pos.y, dim, dim, color);
    DrawRectangleLinesEx({pos.x, pos.y, dim, dim}, 5.0f, BLACK);
}

void food::fall(float speed)
{
    pos.y += speed * GetFrameTime();
}