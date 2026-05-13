#include "bowserBoss.h"
#include <algorithm>
#include <cmath>

namespace {
constexpr Rectangle BowserFrames[] = {
    {-0.0f, 208.0f, 32.0f, 32.0f},
    {34.0f, 208.0f, 32.0f, 32.0f},
    {68.0f, 208.0f, 32.0f, 32.0f},
    {102.0f, 208.0f, 32.0f, 32.0f},
};

constexpr Rectangle BowserFlameFrames[] = {
    {102.0f, 242.0f, 24.0f, 8.0f},
    {102.0f, 252.0f, 24.0f, 8.0f},
};
}

BowserBoss::BowserBoss(float x, float y, float leftBound, float rightBound, Texture2D sprites)
    : pos({x, y}), sprites(sprites), leftBound(leftBound), rightBound(rightBound) {}

Rectangle BowserBoss::returnRec() const {
    return {pos.x + 8.0f, pos.y + 8.0f, Width - 16.0f, Height - 8.0f};
}

void BowserBoss::hurtMario(Mario& marioObj, bool& marioIsDead, float& deathTimer) {
    if (marioObj.getIsInvincible() || marioObj.getIsTransforming()) return;

    if (marioObj.getIsStarPowered()) {
        dropFromBridge();
        defeatedThisFrame = true;
        return;
    }

    if (marioObj.getIsBig()) {
        marioObj.startShrink();
    } else {
        marioIsDead = true;
        deathTimer = 4.0f;
    }
}

void BowserBoss::spawnFlame() {
    flames.push_back({{pos.x - FlameWidth + 8.0f, pos.y + 30.0f}, 0.0f, 0});
    firePoseTimer = 0.35f;
}

void BowserBoss::updateFlames(Mario& marioObj, bool& marioIsDead, float& deathTimer, float cameraX) {
    const float dt = GetFrameTime();
    for (auto& flame : flames) {
        flame.pos.x -= 198.0f * dt;
        flame.animTimer += dt;
        if (flame.animTimer >= 0.1f) {
            flame.animTimer = 0.0f;
            flame.frame = (flame.frame + 1) % 2;
        }

        Rectangle flameRec = {flame.pos.x, flame.pos.y, FlameWidth, FlameHeight};
        if (CheckCollisionRecs(flameRec, marioObj.returnRec())) {
            hurtMario(marioObj, marioIsDead, deathTimer);
        }
    }

    for (auto it = flames.begin(); it != flames.end(); ) {
        if (it->pos.x + FlameWidth < cameraX - 96.0f) it = flames.erase(it);
        else ++it;
    }
}

void BowserBoss::update(
    const std::vector<Rectangle>& statics,
    Mario& marioObj,
    bool& marioIsDead,
    float& deathTimer,
    float cameraX,
    std::vector<std::unique_ptr<Fireball>>& fireballs
) {
    if (!alive && !falling) return;

    if (!active) {
        if (pos.x > cameraX + 700.0f) return;
        active = true;
    }

    if (falling) {
        updateFalling(marioObj, marioIsDead, deathTimer, cameraX);
        return;
    }

    updateFlames(marioObj, marioIsDead, deathTimer, cameraX);

    for (auto& fireball : fireballs) {
        if (CheckCollisionRecs(fireball->returnRec(), returnRec())) {
            fireball->destroy();
            hp--;
            if (hp <= 0) {
                dropFromBridge();
                defeatedThisFrame = true;
                break;
            }
        }
    }

    const float dt = GetFrameTime();
    if (firePoseTimer > 0.0f) firePoseTimer -= dt;

    jumpTimer -= dt;
    if (jumpTimer <= 0.0f && grounded) {
        velY = -430.0f;
        grounded = false;
        jumpTimer = 2.35f;
    }

    flameTimer -= dt;
    if (flameTimer <= 0.0f) {
        spawnFlame();
        flameTimer = 1.85f;
    }

    velY += Gravity * dt;
    if (velY > 520.0f) velY = 520.0f;
    pos.y += velY * dt;
    grounded = false;
    for (const auto& rect : statics) {
        if (CheckCollisionRecs(returnRec(), rect)) {
            if (velY > 0.0f) {
                pos.y = rect.y - Height;
                velY = 0.0f;
                grounded = true;
            } else if (velY < 0.0f) {
                pos.y = rect.y + rect.height - 8.0f;
                velY = 0.0f;
            }
        }
    }

    pos.x += velX * dt;
    if (pos.x < leftBound) {
        pos.x = leftBound;
        velX = std::abs(velX);
    } else if (pos.x > rightBound) {
        pos.x = rightBound;
        velX = -std::abs(velX);
    }

    frameTimer += dt;
    if (frameTimer >= 0.16f) {
        frameTimer = 0.0f;
        frame = (frame + 1) % 2;
    }

    if (CheckCollisionRecs(returnRec(), marioObj.returnRec())) {
        hurtMario(marioObj, marioIsDead, deathTimer);
    }
}

void BowserBoss::updateFalling(Mario& marioObj, bool& marioIsDead, float& deathTimer, float cameraX) {
    updateFlames(marioObj, marioIsDead, deathTimer, cameraX);
    if (!falling) return;

    const float dt = GetFrameTime();
    velY += Gravity * dt;
    pos.y += velY * dt;
    if (pos.y > 760.0f) {
        falling = false;
        alive = false;
    }
}

void BowserBoss::dropFromBridge() {
    if (falling || !alive) return;

    falling = true;
    velX = 0.0f;
    velY = -120.0f;
}

bool BowserBoss::justDefeated() {
    if (defeatedThisFrame) {
        defeatedThisFrame = false;
        return true;
    }
    return false;
}

void BowserBoss::draw() const {
    if (!alive) return;

    for (const auto& flame : flames) {
        DrawTexturePro(
            sprites,
            BowserFlameFrames[flame.frame],
            {flame.pos.x, flame.pos.y, FlameWidth, FlameHeight},
            {0.0f, 0.0f},
            0.0f,
            WHITE
        );
    }

    int sourceFrame = frame;
    if (falling || !grounded) {
        sourceFrame = 2;
    } else if (firePoseTimer > 0.0f) {
        sourceFrame = 3;
    }

    DrawTexturePro(
        sprites,
        BowserFrames[sourceFrame],
        {pos.x, pos.y, Width, Height},
        {0.0f, 0.0f},
        0.0f,
        WHITE
    );
}
