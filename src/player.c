//
// Created by quintas on 8/10/2024.
//

#include "player.h"

Player SpawnPlayer()
{
    return (Player){
        .position = SCREEN_CENTER,
        .rotation = 0,
        .velocity = (Vector2){0}
    };
}

Vector2 PlayerFacingDirection(Player player)
{
    return Vector2Rotate((Vector2){0, -1}, player.rotation * DEG2RAD);
}

static void UpdateAngle(Player* player, float frameTime)
{
    int xIn = (int)IsKeyDown(KEY_RIGHT) - (int)IsKeyDown(KEY_LEFT);
    player->rotation += (xIn * PLAYER_ROTATION_SPEED * frameTime);
}


static void UpdateVelocity(Player* player, float frameTime)
{
    int yIn = (int)IsKeyDown(KEY_UP) - (int)IsKeyDown(KEY_DOWN);
    float magSqr = Vector2LengthSqr(player->velocity);
    float mag = sqrt(magSqr);
    Vector2 facingDirection = PlayerFacingDirection(*player);
    if (yIn > 0)
    {
        player->velocity = Vector2Add(player->velocity,
            Vector2Scale(facingDirection, PLAYER_ACCELERATION * frameTime));
        if (mag > PLAYER_SPEED)
        {
            player->velocity = Vector2Scale(player->velocity, PLAYER_SPEED / mag);
        }
    }
    else
    {
        if (mag > 0)
        {
            float xSign = (player->velocity.x < 0) ? -1.0f: 1.0f;
            float ySign = (player->velocity.y < 0) ? -1.0f: 1.0f;

            float xAbs = player->velocity.x * xSign;
            float yAbs = player->velocity.y * ySign;

            float xWeight = xAbs * xAbs / magSqr;
            float yWeight = yAbs * yAbs / magSqr;

            float xDecel = xWeight * PLAYER_DECELERATION * xSign * frameTime;
            float yDecel = yWeight * PLAYER_DECELERATION * ySign * frameTime;

            player->velocity.x = (xAbs > xDecel) ? player->velocity.x - xDecel : 0;
            player->velocity.y = (yAbs > yDecel) ? player->velocity.y - yDecel : 0;
        }
    }
}


static void UpdateWrap(Player* player)
{
    if (player->position.x > FIELD_MAX_X)
    {
        player->position.x = FIELD_MIN_X;

        if (player->velocity.x < PLAYER_NUDGE_VELOCITY)
        {
            player->velocity.x = PLAYER_NUDGE_VELOCITY;
        }
    }
    else if (player->position.x < FIELD_MIN_X)
    {
        player->position.x = FIELD_MAX_X;

        if (player->velocity.x > -PLAYER_NUDGE_VELOCITY)
        {
            player->velocity.x = -PLAYER_NUDGE_VELOCITY;
        }
    }

    if (player->position.y > FIELD_MAX_Y)
    {
        player->position.y = FIELD_MIN_Y;

        if (player->velocity.y < PLAYER_NUDGE_VELOCITY)
        {
            player->velocity.y = PLAYER_NUDGE_VELOCITY;
        }
    }
    else if (player->position.y < FIELD_MIN_Y)
    {
        player->position.y = FIELD_MAX_Y;

        if (player->velocity.y > -PLAYER_NUDGE_VELOCITY)
        {
            player->velocity.y = -PLAYER_NUDGE_VELOCITY;
        }
    }
}


void UpdatePlayer(Player *player, float frameTime)
{

    UpdateAngle(player, frameTime);
    UpdateVelocity(player, frameTime);

    player->position = Vector2Add(player->position, Vector2Scale(player->velocity, frameTime));
    UpdateWrap(player);
}

void DrawPlayer(Player player, Texture2D texture)
{
    const Rectangle source = {0, 0, 32, 32};
    Rectangle dest = {player.position.x, player.position.y, PLAYER_RADIUS * 2, PLAYER_RADIUS * 2};
    Vector2 origin = {dest.width / 2, dest.height / 2};
    DrawTexturePro(texture, source, dest, origin, player.rotation, WHITE);
}
