#include "mario.h"

Mario::Mario(int x, int y, Texture2D sprites) : posX((float)x), posY((float)y), sprites(sprites) {}

Rectangle Mario::returnRec() {
    return {(float)posX, (float)posY, (float)TILE_SIZE, (float)TILE_SIZE};
}

Vector2 Mario::getPos() {
    return (Vector2){ (float)posX, (float)posY };
}

void Mario::update(const std::vector<Rectangle>& statics, float cameraX) {
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
            if (velY > 0) {
                posY = rect.y - TILE_SIZE;
                velY = 0;
                isGrounded = true;
            } else if (velY < 0) {
                posY = rect.y + rect.height;
                velY = 0;
            }
        }
    }

    bool isMovingHorizontally = (velX > 0.1f || velX < -0.1f);
    if (isGrounded && isMovingHorizontally) {
        frameTimer += GetFrameTime();
        if (frameTimer >= frameDuration) {
            frameTimer = 0.0f;
            currentFrame++;
            if (currentFrame >= 3) currentFrame = 0;
        }
    } else {
        currentFrame = 0;
        frameTimer = 0.0f;
    }

    if (posX < cameraX) {
        posX = cameraX;
        if (velX < 0) velX = 0;
    }
}

void Mario::draw() {
    float sourceX;

    if (!isGrounded) {
        sourceX = 96.0f;
    } else if (velX > 0.1f || velX < -0.1f) {
        sourceX = walkFrames[currentFrame];
    } else {
        sourceX = 0.0f;
    }

    Rectangle sourceRec = { sourceX, 8.0f, 16.0f, 16.0f };

    if (!facingRight) {
        sourceRec.width = -16.0f; 
    }

    DrawTexturePro(
        sprites, 
        sourceRec,
        (Rectangle){ posX, posY, (float)TILE_SIZE, (float)TILE_SIZE }, 
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
    currentFrame = 0;
    frameTimer = 0.0f;
}