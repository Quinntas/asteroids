#include <stdlib.h>
#include <time.h>

#include "raylib.h"
#include "asteroid.h"
#include "raymath.h"
#include "constants.h"
#include "game_asteroids.h"


void UpdateDrawFrame(void)
{
    float frameTime = GetFrameTime();
    float time = GetTime();

    UpdateAsteroids(frameTime, time);
    SpawnAsteroids(time);

    BeginDrawing();
    ClearBackground(NEARBLACK);

    DrawAsteroids();

    EndDrawing();
}

int main(void)
{
    srand(time(0));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Asteroids");

    while(!WindowShouldClose())
    {
        UpdateDrawFrame();
    }

    CloseWindow();

    return 0;
}
