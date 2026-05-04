#include "blocks/emptyBlock.h"

EmptyBlock::EmptyBlock(int x, int y, Texture2D sprites, const SceneType& scene) : Block(x, y, sprites, scene) {}

void EmptyBlock::draw() {
    DrawTexturePro(spriteSheet,
        scene->emptyBlock,
        (Rectangle){ (float)rectXPos, (float)rectYPos, (float)TILE_SIZE, (float)TILE_SIZE },
        (Vector2){ 0, 0 }, 0.0f, WHITE);
}

REGISTER_LEVEL_EDITOR_BLOCK(EmptyBlock, (Rectangle){ 349.0f, 78.0f, 16.0f, 16.0f });
