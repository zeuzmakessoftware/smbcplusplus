#include "blocks/mushroomBrickBlock.h"

namespace {
constexpr float MUSHROOM_SPAWN_TIME = 1.0f;
constexpr float FIRE_FLOWER_FRAME_TIME = 0.18f;

Rectangle MushroomPreviewSource() {
    return {0.0f, 8.0f, 16.0f, 16.0f};
}

Rectangle FireFlowerPreviewSource(int frame) {
    return {32.0f + (frame * 18.0f), 44.0f, 16.0f, 16.0f};
}
}

MushroomBrickBlock::MushroomBrickBlock(int x, int y, Texture2D sprites, Texture2D itemTex, const SceneType& scene)
    : Block(x, y, sprites, scene), itemTexture(itemTex) {
    itemX = (float)x;
    itemY = (float)y;
}

Rectangle MushroomBrickBlock::getSensor() {
    return {(float)rectXPos + 12.0f, (float)rectYPos + TILE_SIZE - 2.0f, (float)TILE_SIZE - 24.0f, 10.0f};
}

std::unique_ptr<Mushroom> MushroomBrickBlock::takeMushroom() {
    return std::move(releasedMushroom);
}

std::unique_ptr<FireFlower> MushroomBrickBlock::takeFireFlower() {
    return std::move(releasedFireFlower);
}

void MushroomBrickBlock::update(Rectangle marioRec, float& marioVelY, bool isBig) {
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
        spawnTimer = MUSHROOM_SPAWN_TIME;
        itemX = (float)rectXPos;
        itemY = (float)rectYPos;
        itemAnimTimer = 0.0f;
        itemFrame = 0;
        releasingFireFlower = isBig;
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

        if (releasingFireFlower) {
            itemAnimTimer += dt;
            if (itemAnimTimer >= FIRE_FLOWER_FRAME_TIME) {
                itemAnimTimer = 0.0f;
                itemFrame = (itemFrame + 1) % 4;
            }
        }

        if (spawnTimer <= 0.0f) {
            if (releasingFireFlower) {
                releasedFireFlower = std::make_unique<FireFlower>(itemX, itemY, itemTexture);
            } else {
                releasedMushroom = std::make_unique<Mushroom>(itemX, itemY, itemTexture);
            }
            itemActive = false;
        }
    }
}

void MushroomBrickBlock::draw() {
    if (itemActive) {
        DrawTexturePro(
            itemTexture,
            releasingFireFlower ? FireFlowerPreviewSource(itemFrame) : MushroomPreviewSource(),
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

REGISTER_LEVEL_EDITOR_BLOCK(MushroomBrickBlock, (Rectangle){ 17.0f, 16.0f, 16.0f, 16.0f });

bool MushroomBrickBlock::justBumped() {
    if (wasHitThisFrame) {
        wasHitThisFrame = false;
        return true;
    }
    return false;
}

void MushroomBrickBlock::drawDebug() {
    DrawRectangleLinesEx(returnRec(), 1.0f, BLUE);
    DrawRectangleLinesEx(getSensor(), 1.0f, RED);
}
