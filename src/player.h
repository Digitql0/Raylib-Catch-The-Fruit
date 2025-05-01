#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

class Player
{
public:
    Player(float x, float y, float w, float h, float sp, float velx, float vely);
    void move();
    void show(Color color);
    float w;
    float h;
    Vector2 pos;

private:
    float speed;
    Vector2 vel;
};

#endif