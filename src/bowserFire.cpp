#include "bowserFire.h"

namespace {
constexpr Rectangle BowserFireFrames[] = {
    {102.0f, 242.0f, 24.0f, 8.0f},
    {102.0f, 252.0f, 24.0f, 8.0f},
};
}

BowserFire::BowserFire(float triggerX, float y, Texture2D sprites)
    : trigger({triggerX, y}), pos({triggerX, y}), sprites(sprites) {}

void BowserFire::hurtMario(Mario& marioObj, bool& marioIsDead, float& deathTimer) {
    if (marioObj.getIsInvincible() || marioObj.getIsStarPowered() || marioObj.getIsTransforming()) return;

    if (marioObj.getIsBig()) {
        marioObj.startShrink();
    } else {
        marioIsDead = true;
        deathTimer = 4.0f;
    }
}

void BowserFire::update(Mario& marioObj, bool& marioIsDead, float& deathTimer, float cameraX, float screenWidth) {
    if (spent) return;

    if (!active) {
        if (trigger.x > cameraX + screenWidth + ActivationPadding) return;
        if (trigger.x + Width < cameraX - ActivationPadding) {
            spent = true;
            return;
        }

        pos = {cameraX + screenWidth + SpawnPadding, trigger.y};
        active = true;
    }

    float dt = GetFrameTime();
    pos.x -= Speed * dt;

    animTimer += dt;
    if (animTimer >= 0.12f) {
        animTimer = 0.0f;
        frame = (frame + 1) % 2;
    }

    if (pos.x + Width < cameraX - SpawnPadding) {
        spent = true;
        return;
    }

    if (CheckCollisionRecs(returnRec(), marioObj.returnRec())) {
        hurtMario(marioObj, marioIsDead, deathTimer);
    }
}

void BowserFire::draw() const {
    if (!active || spent) return;

    DrawTexturePro(
        sprites,
        BowserFireFrames[frame],
        {pos.x, pos.y, Width, Height},
        {0.0f, 0.0f},
        0.0f,
        WHITE
    );
}

Rectangle BowserFire::returnRec() const {
    return {pos.x, pos.y, Width, Height};
}
