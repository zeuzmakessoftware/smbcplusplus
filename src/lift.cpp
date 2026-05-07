#include "lift.h"
#include <algorithm>
#include <cmath>

namespace {
const Rectangle LiftSource = {116.0f, 64.0f, 48.0f, 8.0f};
constexpr float Pi = 3.14159265358979323846f;

float WrapDistance(float distance, float span) {
    if (span <= 0.0f) return 0.0f;
    float wrapped = std::fmod(distance, span);
    return wrapped < 0.0f ? wrapped + span : wrapped;
}

float InitialSinePhase(float value, float minTravel, float maxTravel, int direction) {
    const float amplitude = (maxTravel - minTravel) * 0.5f;
    if (amplitude <= 0.0f) return 0.0f;

    const float center = (minTravel + maxTravel) * 0.5f;
    const float normalized = std::max(-1.0f, std::min(1.0f, (value - center) / amplitude));
    float phase = std::asin(normalized);
    const float velocitySign = std::cos(phase) >= 0.0f ? 1.0f : -1.0f;
    if ((direction >= 0 && velocitySign < 0.0f) || (direction < 0 && velocitySign > 0.0f)) {
        phase = Pi - phase;
    }
    return phase;
}
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
    movement(movement) {
    if (movement == LiftMovement::HorizontalBounce) {
        phase = InitialSinePhase(pos.x, this->minTravel, this->maxTravel, this->direction);
    } else if (movement == LiftMovement::VerticalBounce) {
        phase = InitialSinePhase(pos.y, this->minTravel, this->maxTravel, this->direction);
    }
}

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
        const float amplitude = (maxTravel - minTravel) * 0.5f;
        if (amplitude > 0.0f) {
            phase += (speed / amplitude) * GetFrameTime();
            pos.x = ((minTravel + maxTravel) * 0.5f) + std::sin(phase) * amplitude;
            direction = std::cos(phase) >= 0.0f ? 1 : -1;
        }
    } else {
        if (movement == LiftMovement::VerticalWrap) {
            pos.y += distance * direction;
            const float span = (maxTravel - minTravel) + height;
            if (direction > 0 && pos.y > maxTravel) {
                pos.y = (minTravel - height) + WrapDistance(pos.y - maxTravel, span);
                wrapped = true;
            }
            if (direction < 0 && pos.y + height < minTravel) {
                pos.y = maxTravel - WrapDistance(minTravel - (pos.y + height), span);
                wrapped = true;
            }
        } else {
            const float amplitude = (maxTravel - minTravel) * 0.5f;
            if (amplitude > 0.0f) {
                phase += (speed / amplitude) * GetFrameTime();
                pos.y = ((minTravel + maxTravel) * 0.5f) + std::sin(phase) * amplitude;
                direction = std::cos(phase) >= 0.0f ? 1 : -1;
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
