#include "blocks/coin.h"

Coin::Coin(float x, float y, Texture2D sprites, const SceneType& scene)
    : posX(x), posY(y), spriteSheet(sprites), scene(&scene) {}

Rectangle Coin::returnRec() const {
    return {posX + 8.0f, posY + 2.0f, (float)TILE_SIZE - 16.0f, (float)TILE_SIZE - 4.0f};
}

bool Coin::update(Rectangle marioRec) {
    animTimer += GetFrameTime();
    
    if (animTimer >= 0.30f) {
        animTimer = 0.0f;
        
        frame += frameDirection;

        if (frame >= 2 || frame <= 0) {
            frameDirection *= -1;
        }
    }

    if (!collected && CheckCollisionRecs(marioRec, returnRec())) {
        collected = true;
        return true;
    }

    return false;
}

void Coin::draw() {
    if (collected) return;

    DrawTexturePro(
        spriteSheet,
        scene->coinFrames[frame],
        (Rectangle){ posX, posY, TILE_SIZE, TILE_SIZE },
        (Vector2){ 0, 0 },
        0.0f,
        WHITE
    );
}
