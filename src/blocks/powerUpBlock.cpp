#include "blocks/powerUpBlock.h"

#include <cmath>

PowerUpBlock::PowerUpBlock(int x, int y, Texture2D sprites, Texture2D itemTex, std::string type, const SceneType& scene)
    : Block(x, y, sprites, scene), itemTexture(itemTex), itemType(type) {
    itemX = (float)x;
    itemY = (float)y;
}

Rectangle PowerUpBlock::getSensor() {
    return {(float)rectXPos + 12, (float)rectYPos + TILE_SIZE - 2, (float)TILE_SIZE - 24, 10.0f};
}

std::unique_ptr<Mushroom> PowerUpBlock::takeMushroom() {
    return std::move(releasedMushroom);
}

std::unique_ptr<FireFlower> PowerUpBlock::takeFireFlower() {
    return std::move(releasedFireFlower);
}

void PowerUpBlock::update(Rectangle marioRec, float& marioVelY, bool isBig) {
    if (!isSpent) {
        animTimer += GetFrameTime();
        if (animTimer > 0.20f) {
            frame = (frame + 1) % 3;
            animTimer = 0;
        }
    }

    if (!isSpent && !isBumping && CheckCollisionRecs(marioRec, getSensor())) {
        wasHitThisFrame = true;
        isBumping = true;
        bumpTimer = 0.1f;
        isSpent = true;
        itemActive = true;

        if (itemType == "coin") {
            spawnTimer = 0.3f;
        } else if (itemType == "mushroom" || itemType == "fireflower") {
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

            float progress = (0.3f - spawnTimer) / 0.3f;
            float arc = sinf(progress * PI);
            itemY = (float)rectYPos - (arc * 100.0f);

            coinTimer += GetFrameTime();
            if (coinTimer > 0.05f) {
                coinFrame = (coinFrame + 1) % 3;
                coinTimer = 0;
            }

            if (spawnTimer <= 0) {
                itemActive = false;
            }
        }
        else if (itemType == "mushroom" || itemType == "fireflower") {
            if (spawnTimer > 0) {
                spawnTimer -= GetFrameTime();
                itemY -= (TILE_SIZE * GetFrameTime());
                if (spawnTimer <= 0) {
                    if (itemType == "mushroom") {
                        releasedMushroom = std::make_unique<Mushroom>(itemX, itemY, itemTexture);
                    } else {
                        releasedFireFlower = std::make_unique<FireFlower>(itemX, itemY, itemTexture);
                    }
                    itemActive = false;
                }
            }
        }
    }
}

void PowerUpBlock::draw() {
    if (itemActive) {
        Rectangle src;
        if (itemType == "coin") {
            src = scene->coinFrames[coinFrame];

            DrawTexturePro(spriteSheet, src,
                (Rectangle){ itemX, itemY, (float)TILE_SIZE, (float)TILE_SIZE },
                {0,0}, 0.0f, WHITE);
        }
        else if (itemType == "mushroom") {
            src = { 0.0f, 8.0f, 16.0f, 16.0f };
            DrawTexturePro(itemTexture, src,
                (Rectangle){ itemX, itemY, (float)TILE_SIZE, (float)TILE_SIZE },
                {0,0}, 0.0f, WHITE);
        }
        else if (itemType == "fireflower") {
            src = { 32.0f, 44.0f, 16.0f, 16.0f };
            DrawTexturePro(itemTexture, src,
                (Rectangle){ itemX, itemY, (float)TILE_SIZE, (float)TILE_SIZE },
                {0,0}, 0.0f, WHITE);
        }
    }

    Rectangle blockSrc = isSpent ? scene->emptyBlock : scene->questionBlockFrames[frame];

    DrawTexturePro(spriteSheet, blockSrc,
        (Rectangle){ (float)rectXPos, (float)rectYPos + offsetY, (float)TILE_SIZE, (float)TILE_SIZE },
        {0,0}, 0.0f, WHITE);
}

void PowerUpBlock::drawDebug() {
    DrawRectangleLinesEx(returnRec(), 1.0f, BLUE);
    DrawRectangleLinesEx(getSensor(), 1.0f, RED);
}

bool PowerUpBlock::justBumped() {
    if (wasHitThisFrame) {
        wasHitThisFrame = false;
        return true;
    }
    return false;
}
