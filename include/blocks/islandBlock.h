#ifndef BLOCKS_ISLAND_BLOCK_H
#define BLOCKS_ISLAND_BLOCK_H

#include "blocks/base.h"

class IslandBlock : public Block {
protected:
    Rectangle source;
    bool collidable;

public:
    IslandBlock(int x, int y, Texture2D sprites, Rectangle source, bool collidable,
                const SceneType& scene = GetSceneType(SceneKind::Overworld));
    void update(Rectangle marioRec, float& marioVelY, bool isBig) override {}
    void draw() override;
    bool hasCollision() const override;
};

class IslandSolidTopLeftBlock : public IslandBlock {
public:
    IslandSolidTopLeftBlock(int x, int y, Texture2D sprites,
                            const SceneType& scene = GetSceneType(SceneKind::Overworld));
};

class IslandSolidMiddleBlock : public IslandBlock {
public:
    IslandSolidMiddleBlock(int x, int y, Texture2D sprites,
                           const SceneType& scene = GetSceneType(SceneKind::Overworld));
};

class IslandSolidTopRightBlock : public IslandBlock {
public:
    IslandSolidTopRightBlock(int x, int y, Texture2D sprites,
                             const SceneType& scene = GetSceneType(SceneKind::Overworld));
};

class IslandBackgroundBlock : public IslandBlock {
public:
    IslandBackgroundBlock(int x, int y, Texture2D sprites,
                          const SceneType& scene = GetSceneType(SceneKind::Overworld));
};

#endif
