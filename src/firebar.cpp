#include "firebar.h"

#include <cmath>

namespace {
constexpr float Pi = 3.14159265358979323846f;
constexpr float DegToRad = Pi / 180.0f;
}

FireBar::FireBar(float pivotX, float pivotY, int length, Texture2D sprites, bool clockwise, float startAngle)
    : pivot({pivotX, pivotY}),
      length(length),
      clockwise(clockwise),
      angle(startAngle),
      angularSpeed(90.0f),
      sprites(sprites) {}

Vector2 FireBar::ballCenter(int index) const {
    float radians = angle * DegToRad;
    float distance = FireballSpacing * (float)index;
    return {
        pivot.x + std::cos(radians) * distance,
        pivot.y + std::sin(radians) * distance
    };
}

void FireBar::hurtMario(Mario& marioObj, bool& marioIsDead, float& deathTimer) {
    if (marioObj.getIsInvincible() || marioObj.getIsStarPowered() || marioObj.getIsTransforming()) return;

    if (marioObj.getIsBig()) {
        marioObj.startShrink();
    } else {
        marioIsDead = true;
        deathTimer = 4.0f;
    }
}

void FireBar::update(Mario& marioObj, bool& marioIsDead, float& deathTimer, float cameraX) {
    float reach = FireballSpacing * (float)(length - 1) + ActivationPadding;
    if (pivot.x + reach < cameraX || pivot.x - reach > cameraX + 672.0f) return;

    float dt = GetFrameTime();
    angle += (clockwise ? 1.0f : -1.0f) * angularSpeed * dt;
    if (angle >= 360.0f) angle -= 360.0f;
    if (angle < 0.0f) angle += 360.0f;

    animTimer += dt;
    if (animTimer >= 0.08f) {
        animTimer = 0.0f;
        frame = (frame + 1) % 4;
    }

    Rectangle marioRec = marioObj.returnRec();
    for (int i = 0; i < length; i++) {
        Vector2 center = ballCenter(i);
        if (CheckCollisionCircleRec(center, FireballRadius, marioRec)) {
            hurtMario(marioObj, marioIsDead, deathTimer);
            return;
        }
    }
}

void FireBar::draw() const {
    Rectangle source = {180.0f + (frame * 10.0f), 54.0f, 8.0f, 8.0f};

    for (int i = 0; i < length; i++) {
        Vector2 center = ballCenter(i);
        DrawTexturePro(
            sprites,
            source,
            {center.x - FireballRadius, center.y - FireballRadius, FireballSize, FireballSize},
            {0.0f, 0.0f},
            0.0f,
            WHITE
        );
    }
}
