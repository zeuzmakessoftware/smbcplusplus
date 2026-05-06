#include "blocks/coinBrickBlock.h"

namespace {
constexpr float COIN_ARC_HEIGHT = 100.0f;
constexpr float COIN_FRAME_TIME = 0.05f;
constexpr float COIN_LIFETIME = 0.3f;
constexpr float COIN_WIDTH = 22.0f;

Rectangle CoinSource(int frame) {
    return {180.0f + (frame * 10.0f), 36.0f, 8.0f, 16.0f};
}

float CoinOffsetY(float progress) {
    if (progress < 0.5f) {
        return progress * 2.0f * COIN_ARC_HEIGHT;
    }

    return (1.0f - progress) * 2.0f * COIN_ARC_HEIGHT;
}
}

CoinBrickBlock::CoinBrickBlock(int x, int y, Texture2D sprites, Texture2D itemTex, const SceneType& scene)
    : Block(x, y, sprites, scene), itemTexture(itemTex) {
    coinX = (float)x;
    coinY = (float)y;
}

Rectangle CoinBrickBlock::getSensor() {
    return {(float)rectXPos + 12.0f, (float)rectYPos + TILE_SIZE - 2.0f, (float)TILE_SIZE - 24.0f, 10.0f};
}

void CoinBrickBlock::update(Rectangle marioRec, float& marioVelY, bool isBig) {
    (void)isBig;
    coinAnimationFinishedThisFrame = false;

    Rectangle sensor = getSensor();
    bool headReachedUnderside = marioRec.y <= sensor.y + 3.0f;
    bool hitFromBelow = CheckCollisionRecs(marioRec, sensor) && (marioVelY < 0.0f || headReachedUnderside);
    if (!isSpent && !isBumping && hitFromBelow) {
        wasHitThisFrame = true;
        coinsUsed++;

        marioVelY = 0.0f;

        isBumping = true;
        bumpTimer = 0.1f;
        coinX = (float)rectXPos;
        coinY = (float)rectYPos;
        coinSpawnTimer = COIN_LIFETIME;
        coinAnimTimer = 0.0f;
        coinFrame = 0;

        if (coinsUsed >= maxCoinHits) {
            isSpent = true;
        }
    }

    if (isBumping) {
        bumpTimer -= GetFrameTime();
        if (bumpTimer > 0.05f) {
            offsetY = -10.0f;
        } else if (bumpTimer > 0.0f) {
            offsetY = -5.0f;
        } else {
            offsetY = 0.0f;
            isBumping = false;
        }
    }

    if (coinSpawnTimer > 0.0f) {
        coinSpawnTimer -= GetFrameTime();

        float progress = (COIN_LIFETIME - coinSpawnTimer) / COIN_LIFETIME;
        if (progress < 0.0f) progress = 0.0f;
        if (progress > 1.0f) progress = 1.0f;
        coinY = (float)rectYPos - CoinOffsetY(progress);

        coinAnimTimer += GetFrameTime();
        if (coinAnimTimer > COIN_FRAME_TIME) {
            coinFrame = (coinFrame + 1) % 3;
            coinAnimTimer = 0.0f;
        }

        if (coinSpawnTimer <= 0.0f) {
            coinAnimationFinishedThisFrame = true;
        }
    }
}

void CoinBrickBlock::draw() {
    if (coinSpawnTimer > 0.0f) {
        DrawTexturePro(
            itemTexture,
            CoinSource(coinFrame),
            (Rectangle){ coinX + ((TILE_SIZE - COIN_WIDTH) / 2.0f), coinY, COIN_WIDTH, (float)TILE_SIZE },
            (Vector2){ 0.0f, 0.0f },
            0.0f,
            WHITE
        );
    }

    DrawTexturePro(
        spriteSheet,
        isSpent ? scene->emptyBlock : scene->brickBlock,
        (Rectangle){ (float)rectXPos, (float)rectYPos + offsetY, (float)TILE_SIZE, (float)TILE_SIZE },
        (Vector2){ 0.0f, 0.0f },
        0.0f,
        WHITE
    );
}

REGISTER_LEVEL_EDITOR_BLOCK(CoinBrickBlock, (Rectangle){ 17.0f, 16.0f, 16.0f, 16.0f });

bool CoinBrickBlock::justBumped() {
    if (wasHitThisFrame) {
        wasHitThisFrame = false;
        return true;
    }
    return false;
}

bool CoinBrickBlock::justFinishedCoinAnimation() {
    if (coinAnimationFinishedThisFrame) {
        coinAnimationFinishedThisFrame = false;
        return true;
    }
    return false;
}

void CoinBrickBlock::drawDebug() {
    DrawRectangleLinesEx(returnRec(), 1.0f, BLUE);
    DrawRectangleLinesEx(getSensor(), 1.0f, RED);
}
