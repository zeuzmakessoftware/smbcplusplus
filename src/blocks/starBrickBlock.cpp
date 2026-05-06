#include "blocks/starBrickBlock.h"

namespace {
constexpr float STAR_SPAWN_TIME = 1.0f;
constexpr float STAR_FRAME_TIME = 0.08f;

Rectangle StarPreviewSource(int frame) {
    return {106.0f + (frame * 18.0f), 8.0f, 16.0f, 16.0f};
}
}

StarBrickBlock::StarBrickBlock(int x, int y, Texture2D sprites, Texture2D itemTex, const SceneType& scene)
    : Block(x, y, sprites, scene), itemTexture(itemTex) {
    itemX = (float)x;
    itemY = (float)y;
}

Rectangle StarBrickBlock::getSensor() {
    return {(float)rectXPos + 12.0f, (float)rectYPos + TILE_SIZE - 2.0f, (float)TILE_SIZE - 24.0f, 10.0f};
}

std::unique_ptr<Star> StarBrickBlock::takeStar() {
    return std::move(releasedStar);
}

void StarBrickBlock::update(Rectangle marioRec, float& marioVelY, bool isBig) {
    (void)isBig;

    Rectangle sensor = getSensor();
    bool headReachedUnderside = marioRec.y <= sensor.y + 3.0f;
    bool hitFromBelow = CheckCollisionRecs(marioRec, sensor) && (marioVelY < 0.0f || headReachedUnderside);
    if (!isSpent && !isBumping && hitFromBelow) {
        wasHitThisFrame = true;
        marioVelY = 0.0f;

        isBumping = true;
        bumpTimer = 0.1f;
        isSpent = true;
        itemActive = true;
        spawnTimer = STAR_SPAWN_TIME;
        itemX = (float)rectXPos;
        itemY = (float)rectYPos;
        itemAnimTimer = 0.0f;
        itemFrame = 0;
    }

    if (isBumping) {
        bumpTimer -= GetFrameTime();
        if (bumpTimer > 0.05f) {
            offsetY = -16.0f;
        } else if (bumpTimer > 0.0f) {
            offsetY = -8.0f;
        } else {
            offsetY = 0.0f;
            isBumping = false;
        }
    }

    if (itemActive && spawnTimer > 0.0f) {
        float dt = GetFrameTime();
        spawnTimer -= dt;
        itemY -= (TILE_SIZE * dt);

        itemAnimTimer += dt;
        if (itemAnimTimer >= STAR_FRAME_TIME) {
            itemAnimTimer = 0.0f;
            itemFrame = (itemFrame + 1) % 4;
        }

        if (spawnTimer <= 0.0f) {
            releasedStar = std::make_unique<Star>(itemX, itemY, itemTexture);
            itemActive = false;
        }
    }
}

void StarBrickBlock::draw() {
    if (itemActive) {
        DrawTexturePro(
            itemTexture,
            StarPreviewSource(itemFrame),
            (Rectangle){ itemX, itemY, (float)TILE_SIZE, (float)TILE_SIZE },
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

REGISTER_LEVEL_EDITOR_BLOCK(StarBrickBlock, (Rectangle){ 17.0f, 16.0f, 16.0f, 16.0f });

bool StarBrickBlock::justBumped() {
    if (wasHitThisFrame) {
        wasHitThisFrame = false;
        return true;
    }
    return false;
}

void StarBrickBlock::drawDebug() {
    DrawRectangleLinesEx(returnRec(), 1.0f, BLUE);
    DrawRectangleLinesEx(getSensor(), 1.0f, RED);
}
