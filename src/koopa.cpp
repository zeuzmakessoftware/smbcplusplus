#include "koopa.h"

Koopa::Koopa(float x, float y, Texture2D s, const SceneType& scene) : pos({x, y}), sprites(s), scene(&scene) {}

float Koopa::height() const {
    return state == State::Walking ? WalkHeight : ShellHeight;
}

Rectangle Koopa::returnRec() const {
    return {pos.x, pos.y, Width, height()};
}

void Koopa::updatePhysics(const std::vector<Rectangle>& statics) {
    velY += Gravity;
    pos.y += velY;

    if (state == State::Flipped) {
        rotation += 540.0f * GetFrameTime();
        pos.x += velX;
        if (pos.y > 800.0f) isAlive = false;
        return;
    }

    for (const auto& rect : statics) {
        if (CheckCollisionRecs(returnRec(), rect)) {
            if (velY > 0.0f) {
                pos.y = rect.y - height();
                velY = 0.0f;
            }
        }
    }

    pos.x += velX;
    for (const auto& rect : statics) {
        if (CheckCollisionRecs(returnRec(), rect)) {
            if (velX > 0.0f) pos.x = rect.x - Width;
            else if (velX < 0.0f) pos.x = rect.x + rect.width;
            velX *= -1.0f;
            facingRight = velX > 0.0f;
        }
    }

    if (state == State::Walking || state == State::ShellMoving) {
        frameTimer += GetFrameTime();
        float frameDuration = state == State::ShellMoving ? 0.08f : 0.16f;
        if (frameTimer >= frameDuration) {
            frameTimer = 0.0f;
            currentFrame = (currentFrame + 1) % 2;
        }
    } else {
        currentFrame = 0;
    }
}

void Koopa::hurtMario(Mario& marioObj, bool& marioIsDead, float& deathTimer) {
    if (marioObj.getIsInvincible() || marioObj.getIsTransforming()) return;

    if (marioObj.getIsBig()) {
        marioObj.startShrink();
    } else {
        marioIsDead = true;
        deathTimer = 4.0f;
    }
}

void Koopa::becomeShell() {
    if (state != State::Walking) return;

    state = State::ShellStill;
    defeatedThisFrame = true;
    velX = 0.0f;
    pos.y += WalkHeight - ShellHeight;
}

void Koopa::kickShell(float marioCenterX) {
    state = State::ShellMoving;
    ignoreMarioUntilSeparated = true;
    float shellCenterX = pos.x + Width * 0.5f;
    velX = marioCenterX < shellCenterX ? ShellSpeed : -ShellSpeed;
    facingRight = velX > 0.0f;
}

void Koopa::update(const std::vector<Rectangle>& statics, Mario& marioObj, bool& marioIsDead, float& deathTimer, float cameraX) {
    if (!isAlive) return;

    if (!isActivated) {
        if (pos.x < cameraX + 700.0f) {
            isActivated = true;
        } else {
            return;
        }
    }

    updatePhysics(statics);
    if (state == State::Flipped) return;

    Rectangle marioRec = marioObj.returnRec();
    Rectangle koopaRec = returnRec();
    bool touchingMario = CheckCollisionRecs(koopaRec, marioRec);
    if (state == State::ShellMoving && ignoreMarioUntilSeparated) {
        if (touchingMario) return;
        ignoreMarioUntilSeparated = false;
    }
    if (!touchingMario) return;

    float marioVelY = marioObj.getVelY();
    bool stomped = marioVelY > 0.0f && (marioRec.y + marioRec.height) < (koopaRec.y + 22.0f);

    if (marioObj.getIsStarPowered() && !marioObj.getIsTransforming()) {
        flip();
    } else if (state == State::ShellStill && !marioObj.getIsTransforming()) {
        kickShell(marioRec.x + marioRec.width * 0.5f);
        marioObj.setVelY(-10.0f);
    } else if (state == State::ShellMoving && stomped && !marioObj.getIsTransforming()) {
        state = State::ShellStill;
        velX = 0.0f;
        currentFrame = 0;
        ignoreMarioUntilSeparated = false;
        marioObj.setVelY(-10.0f);
    } else if (stomped && !marioObj.getIsTransforming()) {
        becomeShell();
        marioObj.setVelY(-10.0f);
    } else {
        hurtMario(marioObj, marioIsDead, deathTimer);
    }
}

void Koopa::flip() {
    if (state == State::Flipped) return;

    state = State::Flipped;
    defeatedThisFrame = true;
    velY = -15.0f;
    velX = facingRight ? 2.0f : -2.0f;
}

void Koopa::hitByShell() {
    flip();
}

bool Koopa::justDefeated() {
    if (defeatedThisFrame) {
        defeatedThisFrame = false;
        return true;
    }
    return false;
}

void Koopa::draw() {
    if (!isAlive) return;

    Rectangle source = scene->koopaFrames[currentFrame];
    float drawHeight = WalkHeight;
    if (state == State::ShellStill || state == State::ShellMoving || state == State::Flipped) {
        source = scene->koopaShellFrames[currentFrame];
        drawHeight = ShellHeight;
    }
    if (facingRight && state == State::Walking) {
        source.width *= -1.0f;
    }

    if (state == State::Flipped) {
        DrawTexturePro(
            sprites,
            source,
            {pos.x + Width * 0.5f, pos.y + drawHeight * 0.5f, Width, drawHeight},
            {Width * 0.5f, drawHeight * 0.5f},
            rotation,
            WHITE
        );
    } else {
        DrawTexturePro(sprites, source, {pos.x, pos.y, Width, drawHeight}, {0.0f, 0.0f}, 0.0f, WHITE);
    }
}

void Koopa::drawDebug() {
    if (!isAlive) return;
    DrawRectangleLinesEx(returnRec(), 1.0f, ORANGE);
}
