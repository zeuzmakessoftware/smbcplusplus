#include "piranhaPlant.h"

#include <algorithm>

PiranhaPlant::PiranhaPlant(float pipeX, float pipeY, float pipeWidth, Texture2D sprites)
    : pos({pipeX + (pipeWidth - Width) * 0.5f, pipeY}), pipeRec({pipeX, pipeY, pipeWidth, 0.0f}), sprites(sprites) {}

float PiranhaPlant::hiddenY() const {
    return pipeRec.y;
}

float PiranhaPlant::exposedY() const {
    return pipeRec.y - Height;
}

bool PiranhaPlant::marioBlocksEmergence(Rectangle marioRec) const {
    Rectangle guard = {
        pipeRec.x - 42.0f,
        pipeRec.y - 84.0f,
        pipeRec.width + 84.0f,
        168.0f
    };
    return CheckCollisionRecs(guard, marioRec);
}

void PiranhaPlant::hurtMario(Mario& marioObj, bool& marioIsDead, float& deathTimer) {
    if (marioObj.getIsInvincible() || marioObj.getIsTransforming()) return;

    if (marioObj.getIsBig()) {
        marioObj.startShrink();
    } else {
        marioIsDead = true;
        deathTimer = 4.0f;
    }
}

void PiranhaPlant::update(Mario& marioObj, bool& marioIsDead, float& deathTimer, float cameraX) {
    if (!isAlive) return;

    if (!isActivated) {
        if (pipeRec.x < cameraX + 760.0f) {
            isActivated = true;
        } else {
            return;
        }
    }

    float dt = GetFrameTime();
    Rectangle marioRec = marioObj.returnRec();

    frameTimer += dt;
    if (frameTimer >= 0.18f) {
        frameTimer = 0.0f;
        currentFrame = (currentFrame + 1) % 2;
    }

    switch (state) {
        case State::Hidden:
            pos.y = hiddenY();
            stateTimer += dt;
            if (stateTimer >= HiddenDelay && !marioBlocksEmergence(marioRec)) {
                state = State::Emerging;
                stateTimer = 0.0f;
            }
            break;
        case State::Emerging:
            pos.y -= MoveSpeed * dt;
            if (pos.y <= exposedY()) {
                pos.y = exposedY();
                state = State::Exposed;
                stateTimer = 0.0f;
            }
            break;
        case State::Exposed:
            stateTimer += dt;
            if (stateTimer >= ExposedDelay) {
                state = State::Retreating;
                stateTimer = 0.0f;
            }
            break;
        case State::Retreating:
            pos.y += MoveSpeed * dt;
            if (pos.y >= hiddenY()) {
                pos.y = hiddenY();
                state = State::Hidden;
                stateTimer = 0.0f;
            }
            break;
    }

    if (CheckCollisionRecs(returnRec(), marioRec)) {
        if (marioObj.getIsStarPowered() && !marioObj.getIsTransforming()) {
            defeat();
        } else {
            hurtMario(marioObj, marioIsDead, deathTimer);
        }
    }
}

Rectangle PiranhaPlant::returnRec() const {
    float visibleTop = std::min(pos.y, pipeRec.y);
    float visibleHeight = std::max(0.0f, pipeRec.y - visibleTop);
    return {pos.x, visibleTop, Width, visibleHeight};
}

void PiranhaPlant::defeat() {
    if (!isAlive) return;

    isAlive = false;
    defeatedThisFrame = true;
}

bool PiranhaPlant::justDefeated() {
    if (defeatedThisFrame) {
        defeatedThisFrame = false;
        return true;
    }
    return false;
}

void PiranhaPlant::draw() {
    if (!isAlive) return;

    Rectangle source = {currentFrame == 0 ? 0.0f : 18.0f, 138.0f, 16.0f, 24.0f};
    DrawTexturePro(
        sprites,
        source,
        {pos.x, pos.y, Width, Height},
        {0.0f, 0.0f},
        0.0f,
        WHITE
    );
}

void PiranhaPlant::drawDebug() {
    if (!isAlive) return;
    DrawRectangleLinesEx(returnRec(), 1.0f, RED);
}
