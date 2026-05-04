#include "blocks/powerUpBlock.h"

namespace {
constexpr float BLOCK_COIN_ARC_HEIGHT = 100.0f;
constexpr float BLOCK_COIN_FRAME_TIME = 0.05f;
constexpr float BLOCK_COIN_LIFETIME = 0.3f;
constexpr float BLOCK_COIN_WIDTH = 22.0f;

Rectangle BlockCoinSource(int frame) {
    return {180.0f + (frame * 10.0f), 36.0f, 8.0f, 16.0f};
}

float BlockCoinOffsetY(float progress) {
    if (progress < 0.5f) {
        return progress * 2.0f * BLOCK_COIN_ARC_HEIGHT;
    }

    return (1.0f - progress) * 2.0f * BLOCK_COIN_ARC_HEIGHT;
}
}

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

Rectangle PowerUpBlock::returnRec() {
    if (!hasCollision()) {
        return { (float)rectXPos, (float)rectYPos, 0.0f, 0.0f };
    }

    return Block::returnRec();
}

void PowerUpBlock::update(Rectangle marioRec, float& marioVelY, bool isBig) {
    coinAnimationFinishedThisFrame = false;

    if (!isSpent) {
        animTimer += GetFrameTime();
        if (animTimer > 0.20f) {
            frame = (frame + 1) % 3;
            animTimer = 0;
        }
    }

    bool hitFromBelow = CheckCollisionRecs(marioRec, getSensor()) && (!isHiddenBlock() || marioVelY < 0.0f);
    if (!isSpent && !isBumping && hitFromBelow) {
        wasHitThisFrame = true;
        if (marioVelY < 0.0f) {
            marioVelY = 0.0f;
        }
        isBumping = true;
        bumpTimer = 0.1f;
        isSpent = true;
        itemActive = true;

        if (itemType == "coin") {
            spawnTimer = BLOCK_COIN_LIFETIME;
            coinTimer = 0.0f;
            coinFrame = 0;
        } else if (itemType == "mushroom" || itemType == "fireflower" || itemType == "1up") {
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

            float progress = (BLOCK_COIN_LIFETIME - spawnTimer) / BLOCK_COIN_LIFETIME;
            if (progress < 0.0f) progress = 0.0f;
            if (progress > 1.0f) progress = 1.0f;
            itemY = (float)rectYPos - BlockCoinOffsetY(progress);

            coinTimer += GetFrameTime();
            if (coinTimer > BLOCK_COIN_FRAME_TIME) {
                coinFrame = (coinFrame + 1) % 3;
                coinTimer = 0;
            }

            if (spawnTimer <= 0) {
                itemActive = false;
                coinAnimationFinishedThisFrame = true;
            }
        }
        else if (itemType == "mushroom" || itemType == "fireflower" || itemType == "1up") {
            if (spawnTimer > 0) {
                spawnTimer -= GetFrameTime();
                itemY -= (TILE_SIZE * GetFrameTime());
                if (spawnTimer <= 0) {
                    if (itemType == "mushroom") {
                        releasedMushroom = std::make_unique<Mushroom>(itemX, itemY, itemTexture);
                    } else if (itemType == "1up") {
                        releasedMushroom = std::make_unique<Mushroom>(
                            itemX,
                            itemY,
                            itemTexture,
                            (Rectangle){ 0.0f, 26.0f, 16.0f, 16.0f },
                            true
                        );
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
            src = BlockCoinSource(coinFrame);

            DrawTexturePro(itemTexture, src,
                (Rectangle){ itemX + ((TILE_SIZE - BLOCK_COIN_WIDTH) / 2.0f), itemY, BLOCK_COIN_WIDTH, (float)TILE_SIZE },
                {0,0}, 0.0f, WHITE);
        }
        else if (itemType == "mushroom" || itemType == "1up") {
            src = itemType == "1up" ? (Rectangle){ 0.0f, 26.0f, 16.0f, 16.0f } : (Rectangle){ 0.0f, 8.0f, 16.0f, 16.0f };
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

    if (!isHiddenBlock() || isSpent) {
        DrawTexturePro(spriteSheet, blockSrc,
            (Rectangle){ (float)rectXPos, (float)rectYPos + offsetY, (float)TILE_SIZE, (float)TILE_SIZE },
            {0,0}, 0.0f, WHITE);
    }
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

bool PowerUpBlock::justFinishedCoinAnimation() {
    if (coinAnimationFinishedThisFrame) {
        coinAnimationFinishedThisFrame = false;
        return true;
    }
    return false;
}
