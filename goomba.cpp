#include "goomba.h"

Goomba::Goomba(float x, float y, Texture2D s) : pos({x, y}), sprites(s) {}

void Goomba::updatePhysics(const std::vector<Rectangle>& statics) {
    if (isSquashed) return;

    velY += 0.97f; 
    pos.y += velY;
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

void Goomba::update(const std::vector<Rectangle>& statics, Mario& marioObj, bool& marioIsDead, float& deathTimer) {
    if (isSquashed) {
        squashTimer -= GetFrameTime();
        if (squashTimer <= 0) isAlive = false;
        return;
    }

    updatePhysics(statics);

    Rectangle marioRec = marioObj.returnRec();
    float marioVelY = marioObj.getVelY();

    if (CheckCollisionRecs({pos.x, pos.y, 42, 42}, marioRec)) {
        if (marioVelY > 0.0f && (marioRec.y + marioRec.height) < (pos.y + 20) && !marioObj.getIsTransforming()) {
            isSquashed = true;
            marioObj.setVelY(-15.0f);
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

void Goomba::draw() {
    if (!isAlive) return;

    const float normalSize = 42.0f;
    const float squashedHeight = 21.0f;
    const float yOffset = normalSize - squashedHeight; 

    if (isSquashed) {
        Rectangle source = { 36.0f, 24.0f, 16.0f, 8.0f };
        Rectangle dest   = { pos.x, pos.y + yOffset, normalSize, squashedHeight }; 
        
        DrawTexturePro(sprites, source, dest, { 0, 0 }, 0.0f, WHITE);
    } else {
        Rectangle source = (currentFrame == 0) ? 
            (Rectangle){ 0.0f, 16.0f, 16.0f, 16.0f } : 
            (Rectangle){ 18.0f, 16.0f, 16.0f, 16.0f };
            
        Rectangle dest = { pos.x, pos.y, normalSize, normalSize };
        
        DrawTexturePro(sprites, source, dest, { 0, 0 }, 0.0f, WHITE);
    }
}

void Goomba::drawDebug() {
    if (!isAlive || isSquashed) return;

    DrawRectangleLinesEx({pos.x, pos.y, 42, 42}, 1.0f, RED);

    DrawRectangleLinesEx({pos.x, pos.y, 42, 20}, 2.0f, GREEN);
}