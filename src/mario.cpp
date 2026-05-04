#include "mario.h"
#include "mushroom.h"
#include <iostream>

Mario::Mario(int x, int y, Texture2D sprites) : posX((float)x), posY((float)y), sprites(sprites) {}

Rectangle Mario::returnRec() {
    float height = isBig ? (float)TILE_SIZE * 2 : (float)TILE_SIZE;
    return {(float)posX, (float)posY, (float)TILE_SIZE, height};
}

Vector2 Mario::getPos() {
    return (Vector2){ (float)posX, (float)posY };
}

void Mario::update(
    const std::vector<Rectangle>& statics,
    float cameraX,
    std::vector<std::unique_ptr<Mushroom>>& mushrooms,
    std::vector<std::unique_ptr<FireFlower>>& fireFlowers,
    std::vector<std::unique_ptr<Fireball>>& fireballs,
    Texture2D fireballSheet
) {
    if (isInvincible) {
        invincibilityTimer -= GetFrameTime();
        if (invincibilityTimer <= 0) isInvincible = false;
    }
    
    if (isTransforming || isFireTransforming) {
        transformationTimer -= GetFrameTime();
        fireTransformTimer -= GetFrameTime();
        
        if (transformationTimer <= 0 && fireTransformTimer <= 0) {
            isTransforming = false;
            isFireTransforming = false;
        }
        return;
    }

    bool isRunning = IsKeyDown(KEY_LEFT_SHIFT);
    float currentMaxSpeed = isRunning ? runMaxSpeed : walkMaxSpeed;
    float currentAccel = isRunning ? runAcceleration : walkAcceleration;

    bool moving = false;
    
    if (IsKeyDown(KEY_D)) { 
        velX += currentAccel; 
        facingRight = true; 
        moving = true; 
    }
    if (IsKeyDown(KEY_A)) { 
        velX -= currentAccel; 
        facingRight = false; 
        moving = true; 
    }

    if (!moving) {
        if (velX > 0) velX = (velX - friction < 0) ? 0 : velX - friction;
        else if (velX < 0) velX = (velX + friction > 0) ? 0 : velX + friction;
    }

    if (velX > currentMaxSpeed) velX = currentMaxSpeed;
    if (velX < -currentMaxSpeed) velX = -currentMaxSpeed;

    posX += velX;
    for (const auto& rect : statics) {
        if (CheckCollisionRecs(returnRec(), rect)) {
            if (velX > 0) posX = rect.x - TILE_SIZE;
            else if (velX < 0) posX = rect.x + rect.width;
            velX = 0;
        }
    }

    velY += gravity;
    if (velY > terminalVelocity) velY = terminalVelocity;

    if (IsKeyReleased(KEY_SPACE) && velY < -4.0f) velY = -4.0f; 
    
    if (IsKeyPressed(KEY_SPACE) && isGrounded) {
        float jumpBoost = (std::abs(velX) > walkMaxSpeed) ? -2.0f : 0.0f;
        velY = jumpForce + jumpBoost;
        isGrounded = false;
    }

    if (isFire && IsKeyPressed(KEY_F) && fireballs.size() < 2) {
        float fireballX = facingRight ? posX + TILE_SIZE - 4.0f : posX - 14.0f;
        float fireballY = posY + (isBig ? 24.0f : 12.0f);
        fireballs.push_back(std::make_unique<Fireball>(fireballX, fireballY, facingRight, fireballSheet));
    }

    posY += velY;
    isGrounded = false;

    for (const auto& rect : statics) {
        if (CheckCollisionRecs(returnRec(), rect)) {
            float height = isBig ? (float)TILE_SIZE * 2 : (float)TILE_SIZE;
            if (velY > 0) {
                posY = rect.y - height;
                velY = 0;
                isGrounded = true;
            } else if (velY < 0) {
                posY = rect.y + rect.height;
                velY = 0;
            }
        }
    }

    if (isGrounded && std::abs(velX) > 0.1f) {
        frameTimer += GetFrameTime();
        float dynamicFrameDuration = 0.15f - (std::abs(velX) / runMaxSpeed) * 0.1f;
        if (frameTimer >= dynamicFrameDuration) {
            frameTimer = 0.0f;
            currentFrame = (currentFrame + 1) % 3;
        }
    } else {
        currentFrame = 0;
    }

    if (posX < cameraX) {
        posX = cameraX;
        if (velX < 0) velX = 0;
    }

    for (auto it = mushrooms.begin(); it != mushrooms.end(); ) {
        if (CheckCollisionRecs(this->returnRec(), (*it)->returnRec())) {
            if (!isBig && !isTransforming) {
                isBig = true;
                isTransforming = true;
                transformationTimer = transformationDuration;
                posY -= TILE_SIZE;
            }
            it = mushrooms.erase(it);
        } else {
            ++it;
        }
    }

    for (auto it = fireFlowers.begin(); it != fireFlowers.end(); ) {
        if (CheckCollisionRecs(this->returnRec(), (*it)->returnRec())) {
            if (!isFire) {
                isFireTransforming = true;
                fireTransformTimer = fireTransformDuration;
                
                if (!isBig) {
                    isBig = true;
                    posY -= TILE_SIZE; 
                }
                isFire = true;
            }
            it = fireFlowers.erase(it);
        } else {
            ++it;
        }
    }
}

void Mario::draw() {
    if (isInvincible && !isTransforming && !isFireTransforming) {
        if ((int)(GetTime() * 15) % 2 == 0) return; 
    }

    float sourceX;
    float sourceY = 8.0f; 
    float sourceHeight = 16.0f;
    float drawHeight = (float)TILE_SIZE;
    float drawY = posY;

    if (!isGrounded) {
        sourceX = 96.0f;
    } else if (std::abs(velX) > 0.1f) {
        sourceX = walkFrames[currentFrame];
    } else {
        sourceX = 0.0f;
    }

    if (isTransforming) {
        bool toggle = (int)(transformationTimer * 15) % 2 == 0;
        sourceY = toggle ? 32.0f : 8.0f;
        sourceHeight = toggle ? 32.0f : 16.0f;
        drawHeight = toggle ? (float)TILE_SIZE * 2 : (float)TILE_SIZE;
        drawY = toggle ? (isBig ? posY : posY - TILE_SIZE) : (isBig ? posY + TILE_SIZE : posY);
    } 
    else if (isFireTransforming) {
        bool toggle = (int)(fireTransformTimer * 20) % 2 == 0;
        sourceY = toggle ? 140.0f : 32.0f;
        sourceHeight = 32.0f;
        drawHeight = (float)TILE_SIZE * 2;
        drawY = posY;
    }
    else if (isBig) {
        sourceY = isFire ? 140.0f : 32.0f; 
        sourceHeight = 32.0f;
        drawHeight = (float)TILE_SIZE * 2;
        drawY = posY;
    }

    Rectangle sourceRec = { sourceX, sourceY, 16.0f, sourceHeight };
    if (!facingRight) sourceRec.width = -16.0f;

    DrawTexturePro(
        sprites,
        sourceRec,
        (Rectangle){ posX, drawY, (float)TILE_SIZE, drawHeight },
        (Vector2){ 0, 0 },
        0.0f,
        WHITE 
    );
}

void Mario::reset(float x, float y) {
    posX = x;
    posY = y;
    velX = 0;
    velY = 0;
    isGrounded = false;
    isBig = false;
    isFire = false;
    isTransforming = false;
    currentFrame = 0;
    frameTimer = 0.0f;
}

void Mario::setScriptedPose(float x, float y, bool faceRight) {
    posX = x;
    posY = y;
    velX = 0.0f;
    velY = 0.0f;
    facingRight = faceRight;
    isGrounded = true;
}

void Mario::drawDebug() {
    DrawRectangleLinesEx(returnRec(), 2.0f, GREEN);
    
    DrawCircle(posX, posY, 5, RED);
}

void Mario::startShrink() {
    if (!isTransforming && isBig) {
        isFire = false;
        isBig = false;
        posY += TILE_SIZE;

        isTransforming = true;
        transformationTimer = transformationDuration;
        
        isInvincible = true;
        invincibilityTimer = invincibilityDuration + transformationDuration; 
    }
}
