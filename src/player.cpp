#include "player.h"
#include "raylib.h"
#include "raymath.h"

Player::Player(float x, float y, float width, float height, float sp, float velx, float vely)
{
    pos = {x, y};
    vel = {velx, vely};
    speed = sp;
    w = width;
    h = height;
}

void Player::show(Color color)
{
    DrawRectangle(pos.x, pos.y, w, h, color);
}

void Player::move()
{
    if (IsKeyDown(KEY_A))
    {
        vel.x -= 1;
    }

    if (IsKeyDown(KEY_D))
    {
        vel.x += 1;
    }

    pos.x += vel.x * speed * GetFrameTime();
    pos.y += vel.y * GetFrameTime();
    vel = {0, 0};

    pos.x = Clamp(pos.x, 0, GetScreenWidth() - w);
}