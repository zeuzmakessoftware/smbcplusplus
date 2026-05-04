#ifndef BLOCKS_SHINY_BLOCK_H
#define BLOCKS_SHINY_BLOCK_H

#include "blocks/base.h"

class ShinyBlock : public Block {
public:
    ShinyBlock(int x, int y, Texture2D sprites, const SceneType& scene = GetSceneType(SceneKind::Overworld));
    void update(Rectangle marioRec, float& marioVelY, bool isBig) override {}
    void draw() override;
};

#endif
