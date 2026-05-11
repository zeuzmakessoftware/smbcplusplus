#include "blocks/castleBlock.h"

extern const Rectangle castleBrickBlockSource = {0.0f, 151.0f, 16.0f, 16.0f};

castleBlock::castleBlock(int x, int y, Texture2D sprites, Rectangle source, bool collidable,
                         const SceneType& scene)
    : Block(x, y, sprites, scene), source(source), collidable(collidable) {}

void castleBlock::draw() {
    DrawTexturePro(
        spriteSheet,
        source,
        (Rectangle){(float)rectXPos, (float)rectYPos, (float)TILE_SIZE, (float)TILE_SIZE},
        (Vector2){0, 0},
        0.0f,
        WHITE
    );
}

bool castleBlock::hasCollision() const {
    return collidable;
}

castleBrickBlock::castleBrickBlock(int x, int y, Texture2D sprites, const SceneType& scene)
    : castleBlock(x, y, sprites, castleBrickBlockSource, true, scene) {}

REGISTER_LEVEL_EDITOR_BLOCK(castleBrickBlock, castleBrickBlockSource);
