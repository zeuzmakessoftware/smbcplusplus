#include "blocks/islandBlock.h"

namespace {
const Rectangle IslandSolidTopLeftSource = {-0.0f, 196.0f, 16.0f, 16.0f};
const Rectangle IslandSolidMiddleSource = {17.0f, 196.0f, 16.0f, 16.0f};
const Rectangle IslandSolidTopRightSource = {34.0f, 196.0f, 16.0f, 16.0f};
const Rectangle IslandBackgroundSource = {17.0f, 33.0f, 16.0f, 16.0f};
}

IslandBlock::IslandBlock(int x, int y, Texture2D sprites, Rectangle source, bool collidable,
                         const SceneType& scene)
    : Block(x, y, sprites, scene), source(source), collidable(collidable) {}

void IslandBlock::draw() {
    DrawTexturePro(
        spriteSheet,
        source,
        (Rectangle){(float)rectXPos, (float)rectYPos, (float)TILE_SIZE, (float)TILE_SIZE},
        (Vector2){0, 0},
        0.0f,
        WHITE
    );
}

bool IslandBlock::hasCollision() const {
    return collidable;
}

IslandSolidTopLeftBlock::IslandSolidTopLeftBlock(int x, int y, Texture2D sprites, const SceneType& scene)
    : IslandBlock(x, y, sprites, IslandSolidTopLeftSource, true, scene) {}

IslandSolidMiddleBlock::IslandSolidMiddleBlock(int x, int y, Texture2D sprites, const SceneType& scene)
    : IslandBlock(x, y, sprites, IslandSolidMiddleSource, true, scene) {}

IslandSolidTopRightBlock::IslandSolidTopRightBlock(int x, int y, Texture2D sprites, const SceneType& scene)
    : IslandBlock(x, y, sprites, IslandSolidTopRightSource, true, scene) {}

IslandBackgroundBlock::IslandBackgroundBlock(int x, int y, Texture2D sprites, const SceneType& scene)
    : IslandBlock(x, y, sprites, IslandBackgroundSource, false, scene) {}

REGISTER_LEVEL_EDITOR_BLOCK(IslandSolidTopLeftBlock, IslandSolidTopLeftSource);
REGISTER_LEVEL_EDITOR_BLOCK(IslandSolidMiddleBlock, IslandSolidMiddleSource);
REGISTER_LEVEL_EDITOR_BLOCK(IslandSolidTopRightBlock, IslandSolidTopRightSource);
REGISTER_LEVEL_EDITOR_BLOCK(IslandBackgroundBlock, IslandBackgroundSource);
