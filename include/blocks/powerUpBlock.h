#ifndef BLOCKS_POWER_UP_BLOCK_H
#define BLOCKS_POWER_UP_BLOCK_H

#include <memory>
#include <string>
#include "blocks/base.h"
#include "fireflower.h"
#include "mushroom.h"

class PowerUpBlock : public Block {
private:
    float offsetY = 0;
    float bumpTimer = 0;
    bool isBumping = false;
    bool isSpent = false;
    bool wasHitThisFrame = false;
    bool coinAnimationFinishedThisFrame = false;
    float animTimer = 0;
    int frame = 0;

    std::string itemType;
    std::string resolvedItemType;
    bool itemActive = false;
    float itemX, itemY;
    float spawnTimer = 0.0f;

    float coinTimer = 0.0f;
    int coinFrame = 0;
    float itemAnimTimer = 0.0f;
    int itemFrame = 0;

    std::unique_ptr<Mushroom> releasedMushroom;
    std::unique_ptr<FireFlower> releasedFireFlower;
    Texture2D itemTexture;
    const std::string& activeItemType() const;

public:
    PowerUpBlock(int x, int y, Texture2D sprites, Texture2D itemTex, std::string type = "coin", const SceneType& scene = GetSceneType(SceneKind::Overworld));
    Rectangle getSensor();
    std::unique_ptr<Mushroom> takeMushroom();
    std::unique_ptr<FireFlower> takeFireFlower();
    const std::string& getItemType() const { return itemType; }
    bool isHiddenBlock() const { return itemType == "1up"; }
    bool hasCollision() const { return !isHiddenBlock() || isSpent; }
    void update(Rectangle marioRec, float& marioVelY, bool isBig) override;
    Rectangle returnRec() override;
    bool justBumped() override;
    bool justFinishedCoinAnimation();
    void draw() override;
    void drawDebug() override;
};

#endif
