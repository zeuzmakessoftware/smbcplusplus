#include "blocks.h"

// Base Block
Block::Block(int x, int y, Texture2D sprites) : rectXPos(x), rectYPos(y), spriteSheet(sprites) {}

Rectangle Block::returnRec() {
    return {(float)rectXPos + 4, (float)rectYPos, (float)TILE_SIZE - 8, (float)TILE_SIZE};
}

// Brick Block
BrickBlock::BrickBlock(int x, int y, Texture2D sprites) : Block(x, y, sprites) {}

Rectangle BrickBlock::getSensor() {
    return {(float)rectXPos + 12, (float)rectYPos + TILE_SIZE - 2, (float)TILE_SIZE - 24, 10.0f};
}

void BrickBlock::update(Rectangle marioRec, float marioVelY) {
    if (!isBumping && marioVelY < 0 && CheckCollisionRecs(marioRec, getSensor())) {
        isBumping = true;
        bumpTimer = 0.1f;
    }

    if (isBumping) {
        bumpTimer -= GetFrameTime();
        if (bumpTimer > 0.05f) offsetY = -10.0f;
        else if (bumpTimer > 0) offsetY = -5.0f;
        else {
            offsetY = 0;
            isBumping = false;
        }
    }
}

void BrickBlock::draw() {
    DrawTexturePro(spriteSheet, 
        (Rectangle){ 17.0f, 16.0f, 16.0f, 16.0f }, 
        (Rectangle){ (float)rectXPos, (float)rectYPos + offsetY, (float)TILE_SIZE, (float)TILE_SIZE }, 
        (Vector2){ 0, 0 }, 0.0f, WHITE);
}

// Empty Block
EmptyBlock::EmptyBlock(int x, int y, Texture2D sprites) : Block(x, y, sprites) {}

void EmptyBlock::draw() {
    DrawTexturePro(spriteSheet, 
        (Rectangle){ 349.0f, 78.0f, 16.0f, 16.0f }, 
        (Rectangle){ (float)rectXPos, (float)rectYPos, (float)TILE_SIZE, (float)TILE_SIZE }, 
        (Vector2){ 0, 0 }, 0.0f, WHITE);
}

// PowerUp Block
PowerUpBlock::PowerUpBlock(int x, int y, Texture2D sprites) : Block(x, y, sprites) {}

Rectangle PowerUpBlock::getSensor() {
    return {(float)rectXPos + 12, (float)rectYPos + TILE_SIZE - 2, (float)TILE_SIZE - 24, 10.0f};
}

void PowerUpBlock::update(Rectangle marioRec, float marioVelY) {
    if (isSpent) return;

    animTimer += GetFrameTime();
    if (animTimer > 0.15f) {
        frame = (frame + 1) % 3;
        animTimer = 0;
    }

    if (!isBumping && marioVelY < 0 && CheckCollisionRecs(marioRec, getSensor())) {
        isBumping = true;
        bumpTimer = 0.1f;
    }

    if (isBumping) {
        bumpTimer -= GetFrameTime();
        if (bumpTimer > 0.05f) offsetY = -10.0f;
        else if (bumpTimer > 0) offsetY = -5.0f;
        else {
            offsetY = 0;
            isBumping = false;
            isSpent = true;
        }
    }
}

void PowerUpBlock::draw() {
    if (isSpent) {
        DrawTexturePro(spriteSheet, (Rectangle){ 349.0f, 78.0f, 16.0f, 16.0f }, 
            (Rectangle){ (float)rectXPos, (float)rectYPos, (float)TILE_SIZE, (float)TILE_SIZE }, 
            {0,0}, 0.0f, WHITE);
    } else {
        float srcX = 298.0f + (frame * 17.0f); 
        DrawTexturePro(spriteSheet, 
            (Rectangle){ srcX, 78.0f, 16.0f, 16.0f }, 
            (Rectangle){ (float)rectXPos, (float)rectYPos + offsetY, (float)TILE_SIZE, (float)TILE_SIZE }, 
            (Vector2){ 0, 0 }, 0.0f, WHITE);
    }
}