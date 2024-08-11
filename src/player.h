//
// Created by quintas on 8/10/2024.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "constants.h"
#include "raymath.h"

#define PLAYER_RADIUS 24
#define PLAYER_ROTATION_SPEED 360
#define PLAYER_ACCELERATION 200
#define PLAYER_DECELERATION 300
#define PLAYER_SPEED 250
#define PLAYER_NUDGE_VELOCITY 150

#define FIELD_MIN_X (-PLAYER_RADIUS / 2)
#define FIELD_MAX_X (SCREEN_WIDTH + PLAYER_RADIUS / 2)
#define FIELD_MIN_Y (-PLAYER_RADIUS / 2)
#define FIELD_MAX_Y (SCREEN_HEIGHT + PLAYER_RADIUS / 2)

typedef struct Player
{
    Vector2 position;
    Vector2 velocity;
    float rotation;
} Player;

Player SpawnPlayer();
void DrawPlayer(Player player);
void UpdatePlayer(Player *player, float frameTime);

#endif //PLAYER_H
