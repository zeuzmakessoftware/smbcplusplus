#include "lift.h"
#include <algorithm>
#include <cmath>

namespace {
const Rectangle LiftSource = {116.0f, 64.0f, 48.0f, 8.0f};
}

Lift::Lift(
    float x,
    float y,
    float platformWidth,
    Texture2D sprites,
    LiftMovement movement,
    float minTravel,
    float maxTravel,
    float speed,
    int direction
) : pos({x, y}),
    previousPos({x, y}),
    sprites(sprites),
    width(platformWidth),
    speed(speed),
    minTravel(std::min(minTravel, maxTravel)),
    maxTravel(std::max(minTravel, maxTravel)),
    direction(direction >= 0 ? 1 : -1),
    movement(movement) {}

Lift Lift::VerticalWrap(float x, float y, float width, Texture2D sprites, float topY, float bottomY, float speed, bool movesDown) {
    return Lift(x, y, width, sprites, LiftMovement::VerticalWrap, topY, bottomY, speed, movesDown ? 1 : -1);
}

Lift Lift::VerticalBounce(float x, float y, float width, Texture2D sprites, float topY, float bottomY, float speed, bool startsDown) {
    return Lift(x, y, width, sprites, LiftMovement::VerticalBounce, topY, bottomY, speed, startsDown ? 1 : -1);
}

Lift Lift::HorizontalBounce(float x, float y, float width, Texture2D sprites, float leftX, float rightX, float speed, bool startsRight) {
    return Lift(x, y, width, sprites, LiftMovement::HorizontalBounce, leftX, rightX, speed, startsRight ? 1 : -1);
}

void Lift::update(Mario& mario, const std::vector<Rectangle>& solids, float cameraX) {
    previousPos = pos;
    float distance = speed * GetFrameTime();
    bool wrapped = false;

    if (movement == LiftMovement::HorizontalBounce) {
        pos.x += distance * direction;
        if (pos.x < minTravel) {
            pos.x = minTravel;
            direction = 1;
        } else if (pos.x > maxTravel) {
            pos.x = maxTravel;
            direction = -1;
        }
    } else {
        pos.y += distance * direction;
        if (movement == LiftMovement::VerticalWrap) {
            if (direction > 0 && pos.y > maxTravel) {
                pos.y = minTravel - height;
                wrapped = true;
            }
            if (direction < 0 && pos.y + height < minTravel) {
                pos.y = maxTravel;
                wrapped = true;
            }
        } else {
            if (pos.y < minTravel) {
                pos.y = minTravel;
                direction = 1;
            } else if (pos.y > maxTravel) {
                pos.y = maxTravel;
                direction = -1;
            }
        }
    }

    Rectangle oldRec = {previousPos.x, previousPos.y, width, height};
    Vector2 move = delta();
    if (!wrapped && (std::abs(move.x) > 0.0f || std::abs(move.y) > 0.0f) && mario.isStandingOnPlatform(oldRec)) {
        mario.moveByPlatformDelta(move.x, move.y, solids, cameraX);
    }
}

void Lift::draw() const {
    DrawTexturePro(
        sprites,
        LiftSource,
        returnRec(),
        (Vector2){0.0f, 0.0f},
        0.0f,
        WHITE
    );
}

Rectangle Lift::returnRec() const {
    return {pos.x, pos.y, width, height};
}

Vector2 Lift::delta() const {
    return {pos.x - previousPos.x, pos.y - previousPos.y};
}
