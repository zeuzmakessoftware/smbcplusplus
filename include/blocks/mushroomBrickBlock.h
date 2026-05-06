#ifndef BLOCKS_MUSHROOM_BRICK_BLOCK_H
#define BLOCKS_MUSHROOM_BRICK_BLOCK_H

#include <memory>
#include "blocks/base.h"
#include "fireflower.h"
#include "mushroom.h"

class MushroomBrickBlock : public Block {
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
    float itemAnimTimer = 0.0f;
    int itemFrame = 0;
    bool releasingFireFlower = false;

    Texture2D itemTexture;
    std::unique_ptr<Mushroom> releasedMushroom;
    std::unique_ptr<FireFlower> releasedFireFlower;

public:
    MushroomBrickBlock(int x, int y, Texture2D sprites, Texture2D itemTex, const SceneType& scene = GetSceneType(SceneKind::Overworld));
    Rectangle getSensor();
    std::unique_ptr<Mushroom> takeMushroom();
    std::unique_ptr<FireFlower> takeFireFlower();
    void update(Rectangle marioRec, float& marioVelY, bool isBig = false) override;
    void draw() override;
    bool justBumped() override;
    void drawDebug() override;
};

#endif
