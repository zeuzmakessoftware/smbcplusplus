#include "blocks.h"
#include <iostream>

Block::Block(int x, int y, Texture2D sprites) : rectXPos(x), rectYPos(y), spriteSheet(sprites) {}

Rectangle Block::returnRec() {
    return {(float)rectXPos + 4, (float)rectYPos, (float)TILE_SIZE - 8, (float)TILE_SIZE};
}

BrickBlock::BrickBlock(int x, int y, Texture2D sprites) : Block(x, y, sprites) {}

Rectangle BrickBlock::getSensor() {
    return {(float)rectXPos + 12, (float)rectYPos + TILE_SIZE - 2, (float)TILE_SIZE - 24, 10.0f};
}

void BrickBlock::update(Rectangle marioRec, float marioVelY, bool isBig) {
    if (!isBumping && CheckCollisionRecs(marioRec, getSensor())) {
        if (isBig) {
            destroyed = true; 
        } else {
            isBumping = true;
            bumpTimer = 0.1f;
        }
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

void BrickBlock::drawDebug() {
    DrawRectangleLinesEx(returnRec(), 1.0f, BLUE);
    DrawRectangleLinesEx(getSensor(), 1.0f, RED);
}

EmptyBlock::EmptyBlock(int x, int y, Texture2D sprites) : Block(x, y, sprites) {}

void EmptyBlock::draw() {
    DrawTexturePro(spriteSheet, 
        (Rectangle){ 349.0f, 78.0f, 16.0f, 16.0f }, 
        (Rectangle){ (float)rectXPos, (float)rectYPos, (float)TILE_SIZE, (float)TILE_SIZE }, 
        (Vector2){ 0, 0 }, 0.0f, WHITE);
}

PowerUpBlock::PowerUpBlock(int x, int y, Texture2D sprites, Texture2D itemTex, std::string type) 
    : Block(x, y, sprites), itemTexture(itemTex), itemType(type) {
    itemX = (float)x;
    itemY = (float)y;
}

Rectangle PowerUpBlock::getSensor() {
    return {(float)rectXPos + 12, (float)rectYPos + TILE_SIZE - 2, (float)TILE_SIZE - 24, 10.0f};
}

std::unique_ptr<Mushroom> PowerUpBlock::takeMushroom() {
    return std::move(releasedMushroom);
}

void PowerUpBlock::update(Rectangle marioRec, float marioVelY, bool isBig) {
    if (!isSpent) {
        animTimer += GetFrameTime();
        if (animTimer > 0.20f) {
            frame = (frame + 1) % 3;
            animTimer = 0;
        }
    }

    if (!isSpent && !isBumping && CheckCollisionRecs(marioRec, getSensor())) {
        isBumping = true;
        bumpTimer = 0.1f;
        isSpent = true;
        itemActive = true;
        
        if (itemType == "coin") {
            spawnTimer = 0.1f; 
        } else if (itemType == "mushroom") {
            spawnTimer = 1.0f;
        }
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

    if (itemActive) {
        if (itemType == "coin") {
            spawnTimer -= GetFrameTime();
            itemY -= 15.0f;
            if (spawnTimer <= 0) {
                itemActive = false;
            }
        } 
        else if (itemType == "mushroom") {
            if (spawnTimer > 0) {
                spawnTimer -= GetFrameTime();
                itemY -= (TILE_SIZE * GetFrameTime());
                if (spawnTimer <= 0) {
                    releasedMushroom = std::make_unique<Mushroom>(itemX, itemY, itemTexture);
                    itemActive = false; 
                }
            }
        }
    }
}

void PowerUpBlock::draw() {
    if (itemActive) {
        Rectangle src;
        if (itemType == "coin") src = { 298.0f, 95.0f, 16.0f, 16.0f };
        else if (itemType == "mushroom") src = { 0.0f, 8.0f, 16.0f, 16.0f };

        DrawTexturePro(itemTexture, src,
            (Rectangle){ itemX, itemY, (float)TILE_SIZE, (float)TILE_SIZE },
            {0,0}, 0.0f, WHITE);
    }

    Rectangle blockSrc = isSpent ? (Rectangle){ 349.0f, 78.0f, 16.0f, 16.0f } 
                                 : (Rectangle){ 298.0f + (frame * 17.0f), 78.0f, 16.0f, 16.0f };
    
    DrawTexturePro(spriteSheet, blockSrc, 
        (Rectangle){ (float)rectXPos, (float)rectYPos + offsetY, (float)TILE_SIZE, (float)TILE_SIZE }, 
        {0,0}, 0.0f, WHITE);
}

void PowerUpBlock::drawDebug() {
    DrawRectangleLinesEx(returnRec(), 1.0f, BLUE);
    DrawRectangleLinesEx(getSensor(), 1.0f, RED);
}