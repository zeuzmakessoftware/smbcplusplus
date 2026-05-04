#ifndef BLOCKS_BASE_H
#define BLOCKS_BASE_H

#include <raylib.h>
#include <string>
#include <vector>
#include "sceneType.h"

#define TILE_SIZE 42

struct Particle {
    Vector2 pos;
    Vector2 vel;
    float rotation;
    bool active;
};

struct BlockDefinition {
    const char* displayName;
    const char* className;
    Rectangle source;
};

const std::vector<BlockDefinition>& GetBlockDefinitions();
const BlockDefinition* FindBlockDefinitionByClassName(const std::string& className);

class BlockRegistration {
public:
    BlockRegistration(const char* displayName, const char* className, Rectangle source);
};

#define REGISTER_LEVEL_EDITOR_BLOCK(BLOCK_CLASS, ...) \
    namespace { \
        BlockRegistration BLOCK_CLASS##_registration(#BLOCK_CLASS, #BLOCK_CLASS, __VA_ARGS__); \
    }

class Block {
protected:
    int rectXPos;
    int rectYPos;
    Texture2D spriteSheet;
    const SceneType* scene;

public:
    Block(int x, int y, Texture2D sprites, const SceneType& scene = GetSceneType(SceneKind::Overworld));
    virtual ~Block() {}

    virtual Rectangle returnRec();
    virtual void update(Rectangle marioRec, float& marioVelY, bool isBig = false) = 0;
    virtual void draw() = 0;
    virtual bool justBumped() { return false; }

    int getRectX() { return rectXPos; }
    int getRectY() { return rectYPos; }

    virtual void drawDebug() {}
};

#endif
