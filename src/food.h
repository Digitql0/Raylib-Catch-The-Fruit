#ifndef FOOD_H
#define FOOD_H

#include "raylib.h"

class food
{
public:
    food(float x, float y, float w, Color color);
    void show();
    void fall(float speed);
    Vector2 pos;
    float dim;
    Color color;

private:
};

#endif