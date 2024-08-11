#include <stdlib.h>
#include <time.h>

#include "raylib.h"
#include "constants.h"
#include "game_asteroids.h"
#include "player.h"

static Player _player = {0};
static Texture2D _playerTexture;

void UpdateDrawFrame(void)
{
    float frameTime = GetFrameTime();
    float time = GetTime();

    UpdateAsteroids(frameTime, time);
    SpawnAsteroids(time);

    UpdatePlayer(&_player, frameTime);

    BeginDrawing();
    ClearBackground(NEARBLACK);

    DrawAsteroids();
    DrawPlayer(_player,_playerTexture);

    EndDrawing();
}

int main(void)
{
    srand(time(0));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Asteroids");

    _player = SpawnPlayer();
    _playerTexture = LoadTexture("../resources/ship.png");

    while(!WindowShouldClose())
    {
        UpdateDrawFrame();
    }

    CloseWindow();

    return 0;
}
