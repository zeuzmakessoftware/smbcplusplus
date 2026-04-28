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

void Mario::update(const std::vector<Rectangle>& statics, float cameraX, std::vector<std::unique_ptr<Mushroom>>& mushrooms) {
    if (isInvincible) {
        invincibilityTimer -= GetFrameTime();
        if (invincibilityTimer <= 0) isInvincible = false;
    }

    if (isTransforming) {
        transformationTimer -= GetFrameTime();
        if (transformationTimer <= 0) {
            isTransforming = false;
        }
        return; 
    }
    
    if (isTransforming) {
        transformationTimer -= GetFrameTime();
        if (transformationTimer <= 0) {
            isTransforming = false;
            isBig = true;
        }
        return;
    }

    bool moving = false;
    if (IsKeyDown(KEY_D)) { velX += acceleration; facingRight = true; moving = true; }
    if (IsKeyDown(KEY_A)) { velX -= acceleration; facingRight = false; moving = true; }

    if (!moving) {
        if (velX > 0) velX = (velX - friction < 0) ? 0 : velX - friction;
        else if (velX < -0) velX = (velX + friction > 0) ? 0 : velX + friction;
    }

    if (velX > maxSpeed) velX = maxSpeed;
    if (velX < -maxSpeed) velX = -maxSpeed;

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

    if (IsKeyReleased(KEY_SPACE) && velY < -2.0f) velY = -2.0f;
    if (IsKeyPressed(KEY_SPACE) && isGrounded) {
        velY = jumpForce;
        isGrounded = false;
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

    if (isGrounded && (velX > 0.1f || velX < -0.1f)) {
        frameTimer += GetFrameTime();
        if (frameTimer >= frameDuration) {
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
}

void Mario::draw() {
    if (isInvincible && !isTransforming) {
        if ((int)(GetTime() * 15) % 2 == 0) return; 
    }

    float sourceX;
    float sourceY = 8.0f;
    float sourceHeight = 16.0f;
    float drawHeight = (float)TILE_SIZE;
    float drawY = posY;

    if (!isGrounded) {
        sourceX = 96.0f;
    } else if (velX > 0.1f || velX < -0.1f) {
        sourceX = walkFrames[currentFrame];
    } else {
        sourceX = 0.0f;
    }

    if (isTransforming) {
        bool toggle = (int)(transformationTimer * 15) % 2 == 0;
        
        if (toggle) {
            sourceY = 32.0f; 
            sourceHeight = 32.0f; 
            drawHeight = (float)TILE_SIZE * 2;
            drawY = posY - TILE_SIZE;
        } else {
            sourceY = 8.0f; 
            sourceHeight = 16.0f; 
            drawHeight = (float)TILE_SIZE;
            drawY = posY;
        }
    } else if (isBig) {
        sourceY = 32.0f; 
        sourceHeight = 32.0f; 
        drawHeight = (float)TILE_SIZE * 2;
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
    isTransforming = false;
    currentFrame = 0;
    frameTimer = 0.0f;
}

void Mario::drawDebug() {
    DrawRectangleLinesEx(returnRec(), 2.0f, GREEN);
    
    DrawCircle(posX, posY, 5, RED);
}

void Mario::startShrink() {
    if (!isTransforming && isBig) {
        isBig = false;
        posY += TILE_SIZE;

        isTransforming = true;
        transformationTimer = transformationDuration;
        
        isInvincible = true;
        invincibilityTimer = invincibilityDuration + transformationDuration; 
    }
}