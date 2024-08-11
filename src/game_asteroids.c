//
// Created by quintas on 8/10/2024.
//

#include "game_asteroids.h"
#include "constants.h"
#include "asteroid.h"
#include "raymath.h"

static Asteroid _asteroids[MAX_ASTEROIDS] = {0};
static float _lastAsteroidCreationTime = -1.0f;

Vector2 GetNextAsteroidPosition(void)
{
    int padding = 128;
    Vector2 result = {-padding, -padding};

    if (GetRandomValue(0, 1))
    {
        if (GetRandomValue(0, 1))
        {
            result.y = SCREEN_HEIGHT+padding;
        }

        result.x = GetRandomValue(-padding, SCREEN_WIDTH+padding);
    }
    else
    {
        if (GetRandomValue(0, 1))
        {
            result.x = SCREEN_WIDTH+padding;
        }

        result.y = GetRandomValue(-padding, SCREEN_HEIGHT+padding);
    }

    return result;
}

void AddAsteroid (Vector2 postion, AsteroidSize size)
{
    bool created = false;
    Vector2 velocity = Vector2Subtract(SCREEN_CENTER, postion);
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

void SpawnAsteroids(float time)
{
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
}

void UpdateAsteroids(float frameTime, float time)
{
    for (int i=0;i<MAX_ASTEROIDS;i++)
    {
        AsteroidUpdate(_asteroids+i, frameTime, time);
    }
}

void DrawAsteroids()
{
    for (int i=0;i<MAX_ASTEROIDS;i++)
    {
        AsteroidDraw(_asteroids[i]);
    }
}
