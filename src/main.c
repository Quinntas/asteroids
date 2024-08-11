#include <stdlib.h>
#include <time.h>

#include "raylib.h"
#include "asteroid.h"
#include "raymath.h"

const int screenWidth = 600;
const int screenHeight = 600;
const Vector2 screenCenter = {screenWidth/2, screenHeight/2};
#define NEARBLACK CLITERAL(Color){15, 15,15,255}

#define MAX_ASTEROIDS 64
#define ASTEROID_DELAY 0.90f
#define ASTEROID_RANDOM_ANGLE 20 * DEG2RAD
static Asteroid _asteroids[MAX_ASTEROIDS] = {0};
static float _lastAsteroidCreationTime = -1.0f;

Vector2 GetNextAsteroidPosition(void)
{
    int padding = 128;
    Vector2 result = {padding, padding};

    if (GetRandomValue(0, 1))
    {
        if (GetRandomValue(0, 1))
        {
            result.y = screenHeight+padding;
        }

        result.x = GetRandomValue(-padding, screenWidth+padding);
    }
    else
    {
        if (GetRandomValue(0, 1))
        {
            result.x = screenWidth+padding;
        }

        result.y = GetRandomValue(-padding, screenHeight+padding);
    }

    return result;
}

void AddAsteroid (Vector2 postion, AsteroidSize size)
{
    bool created = false;
    Vector2 velocity = Vector2Subtract(screenCenter, postion);
    velocity = Vector2Scale(Vector2Normalize(velocity), GetRandomValue(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED));
    velocity = Vector2Rotate(velocity, GetRandomValue(-ASTEROID_RANDOM_ANGLE, ASTEROID_RANDOM_ANGLE));

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
    float time = GetTime();

    for (int i=0;i<MAX_ASTEROIDS;i++)
    {
        AsteroidUpdate(_asteroids+i, frameTime, time);
    }

    if (time > _lastAsteroidCreationTime+ASTEROID_DELAY)
    {
        AsteroidSize size;
        int r = GetRandomValue(1, 3);
        if (r == 1)
        {
            size = ASTEROID_SMALL;
        }
        else if (r == 2)
        {
            size = ASTEROID_MEDIUM;
        }
        else
        {
            size = ASTEROID_LARGE;
        }
        AddAsteroid(GetNextAsteroidPosition(), size);
        _lastAsteroidCreationTime = time;
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
