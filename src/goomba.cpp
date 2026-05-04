#include "goomba.h"

Goomba::Goomba(float x, float y, Texture2D s, const SceneType& scene) : pos({x, y}), sprites(s), scene(&scene) {}

void Goomba::updatePhysics(const std::vector<Rectangle>& statics) {
    if (isSquashed) return;

    velY += 0.97f; 
    pos.y += velY;

    if (isFlipped) {
        rotation = 180.0f; 
        if (pos.y > 800) isAlive = false;
        pos.x += velX;
        return;
    }

    for (const auto& rect : statics) {
        if (CheckCollisionRecs({pos.x, pos.y, 42, 42}, rect)) {
            if (velY > 0) { pos.y = rect.y - 42; velY = 0; }
        }
    }

    pos.x += velX;
    for (const auto& rect : statics) {
        if (CheckCollisionRecs({pos.x, pos.y, 42, 42}, rect)) {
            velX *= -1; 
            pos.x += velX;
        }
    }

    frameTimer += GetFrameTime();
    if (frameTimer >= 0.15f) {
        frameTimer = 0;
        currentFrame = (currentFrame + 1) % 2;
    }
}

void Goomba::update(const std::vector<Rectangle>& statics, Mario& marioObj, bool& marioIsDead, float& deathTimer, float cameraX) {
    if (!isAlive) return;

    if (!isActivated) {
        if (pos.x < cameraX + 700) {
            isActivated = true;
        } else {
            return;
        }
    }
    
    if (isSquashed) {
        squashTimer -= GetFrameTime();
        if (squashTimer <= 0) isAlive = false;
        return;
    }

    updatePhysics(statics);

    if (isFlipped) return; 

    Rectangle marioRec = marioObj.returnRec();
    float marioVelY = marioObj.getVelY();

    if (CheckCollisionRecs({pos.x, pos.y, 42, 42}, marioRec)) {
        if (marioVelY > 0.0f && (marioRec.y + marioRec.height) < (pos.y + 20) && !marioObj.getIsTransforming()) {
            isSquashed = true;
            defeatedThisFrame = true;
            marioObj.setVelY(-5.0f);
        } 
        else if (!marioObj.getIsInvincible() && !marioObj.getIsTransforming()) {
            if (marioObj.getIsBig()) {
                marioObj.startShrink();
            } else {
                marioIsDead = true;
                deathTimer = 4.0f;
            }
        }
    }
}

bool Goomba::justDefeated() {
    if (defeatedThisFrame) {
        defeatedThisFrame = false;
        return true;
    }
    return false;
}

void Goomba::draw() {
    if (!isAlive) return;
    
    const float normalSize = 42.0f;
    Rectangle source = scene->goombaFrames[currentFrame];

    if (isSquashed) {
        source = scene->goombaSquashed;
        DrawTexturePro(sprites, source, { pos.x, pos.y + 21.0f, 42, 21 }, { 0, 0 }, 0.0f, WHITE);
    } else if (isFlipped) {
        DrawTexturePro(sprites, source, 
            { pos.x + 21, pos.y + 21, 42, 42 },
            { 21, 21 }, rotation, WHITE);
    } else {
        DrawTexturePro(sprites, source, { pos.x, pos.y, 42, 42 }, { 0, 0 }, 0.0f, WHITE);
    }
}

void Goomba::drawDebug() {
    if (!isAlive || isSquashed) return;

    DrawRectangleLinesEx({pos.x, pos.y, 42, 42}, 1.0f, RED);

    DrawRectangleLinesEx({pos.x, pos.y, 42, 20}, 2.0f, GREEN);
}
