#include "blocks/lavaBlock.h"

namespace {
const Rectangle lavaTopSource = {541.0f, 16.0f, 16.0f, 16.0f };
const Rectangle lavaBackgroundSource = {541.0f, 33.0f, 16.0f, 16.0f};
}

lavaBlock::lavaBlock(int x, int y, Texture2D sprites, Rectangle source, bool collidable,
                         const SceneType& scene)
    : Block(x, y, sprites, scene), source(source), collidable(collidable) {}

void lavaBlock::draw() {
    DrawTexturePro(
        spriteSheet,
        source,
        (Rectangle){(float)rectXPos, (float)rectYPos, (float)TILE_SIZE, (float)TILE_SIZE},
        (Vector2){0, 0},
        0.0f,
        WHITE
    );
}

bool lavaBlock::hasCollision() const {
    return collidable;
}

lavaTopBlock::lavaTopBlock(int x, int y, Texture2D sprites, const SceneType& scene)
    : lavaBlock(x, y, sprites, lavaTopSource, false, scene) {}

lavaBackgroundBlock::lavaBackgroundBlock(int x, int y, Texture2D sprites, const SceneType& scene)
    : lavaBlock(x, y, sprites, lavaBackgroundSource, false, scene) {}

REGISTER_LEVEL_EDITOR_BLOCK(lavaTopBlock, lavaTopSource);
REGISTER_LEVEL_EDITOR_BLOCK(lavaBackgroundBlock, lavaBackgroundSource);
