#ifndef BRIDGE_BLOCK_H
#define BRIDGE_BLOCK_H

#include "blocks/base.h"

class BridgeBlock : public Block {
private:
    int segmentIndex;

public:
    BridgeBlock(int x, int y, Texture2D sprites, int segmentIndex,
                const SceneType& scene = GetSceneType(SceneKind::Castle));

    Rectangle returnRec() override;
    void update(Rectangle marioRec, float& marioVelY, bool isBig) override {}
    void draw() override;
    int getSegmentIndex() const { return segmentIndex; }
};

#endif
