//
// Created by quintas on 8/10/2024.
//

#ifndef ASTEROID_H
#define ASTEROID_H

#include "raylib.h"

#define ASTEROID_ROTATION_MIN_SPEED 5
#define ASTEROID_ROTATION_MAX_SPEED 240

#define ASTEROID_MIN_SPEED 100
#define ASTEROID_MAX_SPEED 300

#define ASTEROID_LIFE 7.5f

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
    float creationTime;
} Asteroid;

Asteroid CreateAsteroid(Vector2 position, Vector2 velocity, AsteroidSize size);
void AsteroidUpdate(Asteroid *asteroid, float frameTime, float time);
void AsteroidDraw(Asteroid asteroid);

#endif //ASTEROID_H
