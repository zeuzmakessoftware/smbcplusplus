#include "blocks/shinyBlock.h"

ShinyBlock::ShinyBlock(int x, int y, Texture2D sprites, const SceneType& scene) : Block(x, y, sprites, scene) {}

void ShinyBlock::draw() {
    DrawTexturePro(spriteSheet,
        scene->solidBlock,
        (Rectangle){ (float)rectXPos, (float)rectYPos, (float)TILE_SIZE, (float)TILE_SIZE },
        (Vector2){ 0, 0 }, 0.0f, WHITE);
}

REGISTER_LEVEL_EDITOR_BLOCK(ShinyBlock, (Rectangle){ 0.0f, 33.0f, 16.0f, 16.0f });
