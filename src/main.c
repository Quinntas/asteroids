#include <stdlib.h>
#include <time.h>

#include "raylib.h"
#include "asteroid.h"

const int screenWidth = 600;
const int screenHeight = 600;
const Vector2 screenSize = {screenWidth, screenHeight};
#define NEARBLACK CLITERAL(Color){15, 15,15,255}

#define MAX_ASTEROIDS 10
static Asteroid _asteroids[MAX_ASTEROIDS] = {0};

void AddAsteroid (Vector2 postion, Vector2 velocity, AsteroidSize size)
{
    bool created = false;

    for (int i=0;i<MAX_ASTEROIDS;i++)
    {
        if (_asteroids[i].active)
        {
            continue;
        }

        _asteroids[i] = CreateAsteroid(postion, velocity, size);
        created = true;
        break;
    }

    if (!created)
    {
        TraceLog(LOG_ERROR, "Failed to create asteroid, no space left");
    }
}

void UpdateDrawFrame(void)
{
    float frameTime = GetFrameTime();

    for (int i=0;i<MAX_ASTEROIDS;i++)
    {
        AsteroidUpdate(_asteroids+i, frameTime);
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        AddAsteroid(GetMousePosition(), (Vector2){200,0}, ASTEROID_SMALL);
    }

    BeginDrawing();
    ClearBackground(NEARBLACK);

    for (int i=0;i<MAX_ASTEROIDS;i++)
    {
        AsteroidDraw(_asteroids[i]);
    }

    EndDrawing();
}

int main(void)
{
    srand(time(0));

    InitWindow(screenWidth, screenHeight, "Asteroids");

    while(!WindowShouldClose())
    {
        UpdateDrawFrame();
    }

    CloseWindow();

    return 0;
}
