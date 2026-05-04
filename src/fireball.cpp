#include "fireball.h"

Fireball::Fireball(float x, float y, bool facingRight, Texture2D s) 
    : pos({x, y}), sprites(s) {
    velX = facingRight ? 8.0f : -8.0f;
}

void Fireball::update(const std::vector<Rectangle>& statics, float cameraX) {
    velY += 0.55f;
    if (velY > 9.0f) velY = 9.0f;

    pos.x += velX;
    for (const auto& rect : statics) {
        if (CheckCollisionRecs(returnRec(), rect)) {
            alive = false;
            return;
        }
    }

    pos.y += velY;
    for (const auto& rect : statics) {
        if (CheckCollisionRecs(returnRec(), rect)) {
            if (velY > 0.0f) {
                pos.y = rect.y - 18.0f;
                velY = -7.0f;
            } else {
                alive = false;
                return;
            }
        }
    }

    animTimer += GetFrameTime();
    if (animTimer >= 0.08f) {
        animTimer = 0.0f;
        frame = (frame + 1) % 4;
    }

    if (pos.x < cameraX - 64.0f || pos.x > cameraX + 760.0f || pos.y > 760.0f) {
        alive = false;
    }
}

void Fireball::draw() {
    float sourceX = 180.0f + (frame * 10.0f);

    DrawTexturePro(
        sprites, 
        (Rectangle){ sourceX, 54.0f, 8.0f, 8.0f }, 
        (Rectangle){ pos.x, pos.y, 18.0f, 18.0f }, 
        (Vector2){ 0, 0 }, 
        0.0f, 
        WHITE
    );
}