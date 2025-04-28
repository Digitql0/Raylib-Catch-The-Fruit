#include "raylib.h"
#include "food.h"
#include "player.h"
#include <ctime>
#include <iostream>
#include <vector>
#include <string>

const int screenWidth = 800;
const int screenHeight = 600;
const float playerWidth = 100;
const float playerHeight = 10;
const float playerSpeed = 500;
const int maxFails = 10;
unsigned int foodSpawnHeight = 150;
unsigned int foodSize = 5;
unsigned int minFoodWidth = 20;
unsigned int playerBottomDistance = 20;
float fallSpeed = 250;
float fallSpeedMultiplier = 2;
bool gameOver = false;
std::vector<food> meal = {};
Player player(screenWidth / 2 - playerWidth / 2, screenHeight - playerHeight - playerBottomDistance, playerWidth, playerHeight, playerSpeed, 0, 0);
unsigned int score = 0;
unsigned int fails = 10;
std::time_t start = std::time(nullptr);

Color GetRandomColor()
{
    Color color = {(unsigned char)GetRandomValue(0, 255),
                   (unsigned char)GetRandomValue(0, 255),
                   (unsigned char)GetRandomValue(0, 255),
                   255};
    return color;
}

food generateNewFood()
{
    float width = GetRandomValue(minFoodWidth, playerWidth);
    float dx = GetRandomValue(0, screenWidth - width);
    float dy = 0 - width;
    Color color = GetRandomColor();
    food newFood(dx, dy, width, color);
    return newFood;
}

int main()
{
    // Initialization
    InitWindow(screenWidth, screenHeight, "Food Collector Game");
    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())
    {

        // fallSpeed = std::difftime(std::time(nullptr), start) * fallSpeedMultiplier;

        if (!gameOver)
        {
            // Generate new Food
            if (meal.size() < foodSize)
            {

                float highestPoint = GetScreenHeight();
                for (food f : meal)
                {
                    if (f.pos.y < highestPoint)
                    {
                        highestPoint = f.pos.y;
                    }
                }

                if (highestPoint >= foodSpawnHeight)
                {
                    meal.push_back(generateNewFood());
                }
            }

            // Move Food
            for (int i = 0; i < meal.size(); ++i)
            {
                meal[i].fall(fallSpeed);
            }

            // Move Player
            player.move();

            Rectangle play = {player.pos.x, player.pos.y, player.w, player.h};
            // Check Food Collisions
            for (int i = meal.size() - 1; i >= 0; --i)
            {

                if (meal[i].pos.y >= GetScreenHeight())
                {
                    meal.erase(meal.begin() + i);
                    fails += 1;
                }

                else
                {
                    Rectangle fod = {meal[i].pos.x, meal[i].pos.y, meal[i].dim, meal[i].dim};
                    if (CheckCollisionRecs(fod, play))
                    {
                        meal.erase(meal.begin() + i);
                        score += 1;
                    }
                }
            }

            if (fails >= maxFails)
            {
                gameOver = true;
            }
        }

        if (gameOver)
        {
            if (IsKeyDown(KEY_SPACE))
            {
                gameOver = false;
                start = std::time(nullptr);
                fails = 0;
                score = 0;
                meal = {};
                fallSpeed = 250;
                player.pos = {screenWidth / 2 - playerWidth / 2, screenHeight - playerHeight - playerBottomDistance};
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(SKYBLUE);
        std::string str = std::to_string(score);
        std::string stri = std::to_string(fails);
        std::string st = "max. " + std::to_string(maxFails);
        DrawText(str.c_str(), GetScreenWidth() / 4 - MeasureText(str.c_str(), 100) / 2, 100, 100, RAYWHITE);
        DrawText(stri.c_str(), GetScreenWidth() / 4 * 3 - MeasureText(stri.c_str(), 100) / 2, 100, 100, RED);
        DrawText(st.c_str(), GetScreenWidth() / 4 * 3 - MeasureText(st.c_str(), 25) / 2, 75, 25, RED);
        player.show(BLACK);

        for (int i = 0; i < meal.size(); ++i)
        {
            meal[i].show();
        }

        if (gameOver)
        {
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), {0, 0, 0, 255 / 4 * 3});
            DrawText("Press Space to Retry", GetScreenWidth() / 2 - MeasureText("Pres Space to Retry", 50) / 2, GetScreenHeight() / 2 - 50 / 2, 50, RAYWHITE);
        }

        EndDrawing();
    }

    // De-Initialization
    CloseWindow();
    return 0;
}