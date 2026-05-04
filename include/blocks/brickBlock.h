#ifndef BLOCKS_BRICK_BLOCK_H
#define BLOCKS_BRICK_BLOCK_H

#include "blocks/base.h"

class BrickBlock : public Block {
private:
    float offsetY = 0;
    float bumpTimer = 0;
    bool isBumping = false;
    bool destroyed = false;
    bool wasHitThisFrame = false;

public:
    BrickBlock(int x, int y, Texture2D sprites, const SceneType& scene = GetSceneType(SceneKind::Overworld));
    Rectangle getSensor();
    void update(Rectangle marioRec, float& marioVelY, bool isBig) override;
    void draw() override;
    bool justBumped() override;
    void drawDebug() override;
    bool isDestroyed() { return destroyed; }

    static void updateParticles(std::vector<Particle>& particles);
    static void drawParticles(std::vector<Particle>& particles, Texture2D spriteSheet, const SceneType& scene = GetSceneType(SceneKind::Overworld));
    void SpawnBrickParticles(std::vector<Particle>& particles);
};

#endif
