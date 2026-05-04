#ifndef BLOCKS_EMPTY_BLOCK_H
#define BLOCKS_EMPTY_BLOCK_H

#include "blocks/base.h"

class EmptyBlock : public Block {
public:
    EmptyBlock(int x, int y, Texture2D sprites, const SceneType& scene = GetSceneType(SceneKind::Overworld));
    void update(Rectangle marioRec, float& marioVelY, bool isBig) override {}
    void draw() override;
};

#endif
