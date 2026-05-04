#ifndef BLOCKS_COIN_H
#define BLOCKS_COIN_H

#include "blocks/base.h"

class Coin {
private:
    float posX;
    float posY;
    Texture2D spriteSheet;
    const SceneType* scene;
    float animTimer = 0.0f;
    int frame = 0;
    bool collected = false;

public:
    Coin(float x, float y, Texture2D sprites, const SceneType& scene = GetSceneType(SceneKind::Overworld));
    Rectangle returnRec() const;
    bool update(Rectangle marioRec);
    void draw();
    bool isCollected() const { return collected; }
};

#endif
