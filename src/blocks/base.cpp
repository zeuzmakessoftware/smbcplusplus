#include "blocks/base.h"

static std::vector<BlockDefinition>& MutableBlockDefinitions() {
    static std::vector<BlockDefinition> blocks;
    return blocks;
}

BlockRegistration::BlockRegistration(const char* displayName, const char* className, Rectangle source) {
    MutableBlockDefinitions().push_back({displayName, className, source});
}

const std::vector<BlockDefinition>& GetBlockDefinitions() {
    return MutableBlockDefinitions();
}

const BlockDefinition* FindBlockDefinitionByClassName(const std::string& className) {
    for (const BlockDefinition& block : GetBlockDefinitions()) {
        if (className == block.className) {
            return &block;
        }
    }
    return nullptr;
}

Block::Block(int x, int y, Texture2D sprites, const SceneType& scene)
    : rectXPos(x), rectYPos(y), spriteSheet(sprites), scene(&scene) {}

Rectangle Block::returnRec() {
    return {(float)rectXPos + 4, (float)rectYPos, (float)TILE_SIZE - 8, (float)TILE_SIZE};
}
