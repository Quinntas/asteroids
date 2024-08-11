//
// Created by quintas on 8/10/2024.
//

#ifndef ASTEROID_H
#define ASTEROID_H

#include "raylib.h"

#define ASTEROID_ROTATION_MIN_SPEED 5
#define ASTEROID_ROTATION_MAX_SPEED 240

typedef enum AsteroidSize
{
    ASTEROID_SMALL = 1,
    ASTEROID_MEDIUM = 2,
    ASTEROID_LARGE = 4
} AsteroidSize;

typedef struct Asteroid
{
    bool active;
    AsteroidSize size;
    Vector2 position;
    float rotation;
    float rotationSpeed;
    Vector2 velocity;
} Asteroid;

Asteroid CreateAsteroid(Vector2 position, Vector2 velocity, AsteroidSize size);
void AsteroidUpdate(Asteroid *asteroid, float frameTime);
void AsteroidDraw(Asteroid asteroid);

#endif //ASTEROID_H
