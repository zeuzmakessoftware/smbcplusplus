#include "blocks/bridgeBlock.h"

namespace {
constexpr Rectangle CastleBridgeSource = {184.0f, 600.0f, 208.0f, 16.0f};
}

BridgeBlock::BridgeBlock(int x, int y, Texture2D sprites, int segmentIndex, const SceneType& scene)
    : Block(x, y, sprites, scene), segmentIndex(segmentIndex) {}

Rectangle BridgeBlock::returnRec() {
    return {(float)rectXPos, (float)rectYPos, (float)TILE_SIZE, (float)TILE_SIZE};
}

void BridgeBlock::draw() {
    Rectangle source = {
        CastleBridgeSource.x + (float)segmentIndex * 16.0f,
        CastleBridgeSource.y,
        16.0f,
        CastleBridgeSource.height
    };

    DrawTexturePro(
        spriteSheet,
        source,
        {(float)rectXPos, (float)rectYPos, (float)TILE_SIZE, (float)TILE_SIZE},
        {0.0f, 0.0f},
        0.0f,
        WHITE
    );
}
