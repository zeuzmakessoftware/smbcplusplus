#include "mushroom.h"
#include <vector>

void Mushroom::update(const std::vector<Rectangle>& statics) {
    velY += 0.97f;
    pos.y += velY;
    
    for (const auto& rect : statics) {
        if (CheckCollisionRecs(returnRec(), rect)) {
            if (velY > 0) { 
                pos.y = rect.y - 42; 
                velY = 0; 
            }
            else if (velY < 0) {
                pos.y = rect.y + rect.height;
                velY = 0;
            }
        }
    }

    pos.x += velX;
    for (const auto& rect : statics) {
        if (CheckCollisionRecs(returnRec(), rect)) {
            velX *= -1.0f; 
            
            if (velX > 0) {
                pos.x = rect.x + rect.width;
            } else {
                pos.x = rect.x - 42;
            }
        }
    }
}

void Mushroom::draw() {
    DrawTexturePro(sprites, source,
        (Rectangle){ pos.x, pos.y, 42, 42 }, {0,0}, 0.0f, WHITE);
}
