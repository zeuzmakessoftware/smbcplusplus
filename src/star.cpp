#include "star.h"

namespace {
constexpr float STAR_GRAVITY = 0.97f;
constexpr float STAR_BOUNCE_VELOCITY = -12.0f;
constexpr float STAR_FRAME_TIME = 0.08f;

Rectangle StarSource(int frame) {
    return {106.0f + (frame * 18.0f), 8.0f, 16.0f, 16.0f};
}
}

void Star::update(const std::vector<Rectangle>& statics) {
    animTimer += GetFrameTime();
    if (animTimer >= STAR_FRAME_TIME) {
        animTimer = 0.0f;
        frame = (frame + 1) % 4;
    }

    velY += STAR_GRAVITY;
    pos.y += velY;

    for (const auto& rect : statics) {
        if (CheckCollisionRecs(returnRec(), rect)) {
            if (velY > 0.0f) {
                pos.y = rect.y - 42.0f;
                velY = STAR_BOUNCE_VELOCITY;
            } else if (velY < 0.0f) {
                pos.y = rect.y + rect.height;
                velY = 0.0f;
            }
        }
    }

    pos.x += velX;
    for (const auto& rect : statics) {
        if (CheckCollisionRecs(returnRec(), rect)) {
            velX *= -1.0f;

            if (velX > 0.0f) {
                pos.x = rect.x + rect.width;
            } else {
                pos.x = rect.x - 42.0f;
            }
        }
    }
}

void Star::draw() {
    DrawTexturePro(
        sprites,
        StarSource(frame),
        (Rectangle){ pos.x, pos.y, 42.0f, 42.0f },
        (Vector2){ 0.0f, 0.0f },
        0.0f,
        WHITE
    );
}
