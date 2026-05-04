#include "fireflower.h"

void FireFlower::update() {
    animTimer += GetFrameTime();
    if (animTimer >= 0.18f) {
        animTimer = 0.0f;
        frame = (frame + 1) % 4;
    }
}

void FireFlower::draw() {
    DrawTexturePro(
        sprites,
        (Rectangle){ (float)32 + (frame * 18), 44.0f, 16.0f, 16.0f },
        (Rectangle){ pos.x, pos.y, 42.0f, 42.0f },
        (Vector2){ 0, 0 },
        0.0f,
        WHITE
    );
}
