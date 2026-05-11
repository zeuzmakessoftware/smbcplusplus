#ifndef CASTLE_BLOCK_H
#define CASTLE_BLOCK_H

#include "blocks/base.h"

extern const Rectangle castleBrickBlockSource;

class castleBlock : public Block {
protected:
    Rectangle source;
    bool collidable;

public:
    castleBlock(int x, int y, Texture2D sprites, Rectangle source, bool collidable,
                const SceneType& scene = GetSceneType(SceneKind::Overworld));
    void update(Rectangle marioRec, float& marioVelY, bool isBig) override {}
    void draw() override;
    bool hasCollision() const override;
};

class castleBrickBlock : public castleBlock {
public:
    castleBrickBlock(int x, int y, Texture2D sprites,
                            const SceneType& scene = GetSceneType(SceneKind::Overworld));
};

#endif
