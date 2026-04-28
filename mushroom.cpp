#include "mushroom.h"
#include <vector>

void Mushroom::update(const std::vector<Rectangle>& statics) {
    velY += 0.97f;
    pos.y += velY;
    
    for (const auto& rect : statics) {
        if (CheckCollisionRecs(returnRec(), rect)) {
            if (velY > 0) { pos.y = rect.y - 42; velY = 0; }
        }
    }

    pos.x += velX;
    for (const auto& rect : statics) {
        if (CheckCollisionRecs(returnRec(), rect)) {
            velX *= -0.2;
            pos.x += velX;
        }
    }
}

void Mushroom::draw() {
    DrawTexturePro(sprites, (Rectangle){ 0.0f, 8.0f, 16.0f, 16.0f },
        (Rectangle){ pos.x, pos.y, 42, 42 }, {0,0}, 0.0f, WHITE);
}