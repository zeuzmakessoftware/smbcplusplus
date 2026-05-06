#ifndef BLOCKS_COIN_BRICK_BLOCK_H
#define BLOCKS_COIN_BRICK_BLOCK_H

#include "blocks/base.h"

class CoinBrickBlock : public Block {
private:
    static constexpr int maxCoinHits = 8;

    float offsetY = 0.0f;
    float bumpTimer = 0.0f;
    bool isBumping = false;
    bool isSpent = false;
    bool wasHitThisFrame = false;
    bool coinAnimationFinishedThisFrame = false;

    Texture2D itemTexture;
    float coinX = 0.0f;
    float coinY = 0.0f;
    float coinSpawnTimer = 0.0f;
    float coinAnimTimer = 0.0f;
    int coinFrame = 0;
    int coinsUsed = 0;

public:
    CoinBrickBlock(int x, int y, Texture2D sprites, Texture2D itemTex, const SceneType& scene = GetSceneType(SceneKind::Overworld));
    Rectangle getSensor();
    void update(Rectangle marioRec, float& marioVelY, bool isBig = false) override;
    void draw() override;
    bool justBumped() override;
    bool justFinishedCoinAnimation();
    void drawDebug() override;
};

#endif
