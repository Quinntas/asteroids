//
// Created by quintas on 8/10/2024.
//

#include "asteroid.h"


#include "raymath.h"

Asteroid CreateAsteroid(Vector2 position, Vector2 velocity, AsteroidSize size)
{
    return (Asteroid) {
        .active = true,
        .position = position,
        .velocity = velocity,
        .size = size,
        .creationTime = GetTime(),
        .rotation = GetRandomValue(0, 360),
        .rotationSpeed = GetRandomValue(ASTEROID_ROTATION_MIN_SPEED, ASTEROID_ROTATION_MAX_SPEED)
    };
}

void AsteroidUpdate(Asteroid *asteroid, float frameTime, float time)
{
    if(!asteroid->active)
    {
        return;
    }

    if (time > asteroid->creationTime + ASTEROID_LIFE)
    {
        asteroid->active = false;
        return;
    }

    asteroid->position = Vector2Add(asteroid->position, Vector2Scale(asteroid->velocity, frameTime));
    asteroid->rotation += asteroid->rotationSpeed * frameTime;
}

void AsteroidDraw(Asteroid asteroid)
{
    if(!asteroid.active)
    {
        return;
    }

    DrawPolyLines(asteroid.position, 3,16*(int)(asteroid.size), asteroid.rotation, WHITE);
}