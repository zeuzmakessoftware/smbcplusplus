#ifndef BLOCKS_STAR_BRICK_BLOCK_H
#define BLOCKS_STAR_BRICK_BLOCK_H

#include <memory>
#include "blocks/base.h"
#include "star.h"

class StarBrickBlock : public Block {
private:
    float offsetY = 0.0f;
    float bumpTimer = 0.0f;
    bool isBumping = false;
    bool isSpent = false;
    bool wasHitThisFrame = false;
    bool itemActive = false;
    float itemX = 0.0f;
    float itemY = 0.0f;
    float spawnTimer = 0.0f;

    Texture2D itemTexture;
    std::unique_ptr<Star> releasedStar;

public:
    StarBrickBlock(int x, int y, Texture2D sprites, Texture2D itemTex, const SceneType& scene = GetSceneType(SceneKind::Overworld));
    Rectangle getSensor();
    std::unique_ptr<Star> takeStar();
    void update(Rectangle marioRec, float& marioVelY, bool isBig = false) override;
    void draw() override;
    bool justBumped() override;
    void drawDebug() override;
};

#endif
