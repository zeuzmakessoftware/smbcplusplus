#ifndef BLOCKS_LAVA_BLOCK_H
#define BLOCKS_LAVA_BLOCK_H

#include "blocks/base.h"

class lavaBlock : public Block {
protected:
    Rectangle source;
    bool collidable;

public:
    lavaBlock(int x, int y, Texture2D sprites, Rectangle source, bool collidable,
                const SceneType& scene = GetSceneType(SceneKind::Overworld));
    void update(Rectangle marioRec, float& marioVelY, bool isBig) override {}
    void draw() override;
    bool hasCollision() const override;
};

class lavaTopBlock : public lavaBlock {
public:
    lavaTopBlock(int x, int y, Texture2D sprites,
                            const SceneType& scene = GetSceneType(SceneKind::Overworld));
};

class lavaBackgroundBlock : public lavaBlock {
public:
    lavaBackgroundBlock(int x, int y, Texture2D sprites,
                           const SceneType& scene = GetSceneType(SceneKind::Overworld));
};

#endif
