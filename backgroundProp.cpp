#include "backgroundProp.h"

std::vector<SpritePart> HILL_LAYOUT = {
    {{0.0f, 247.0f, 16.0f, 16.0f}, {0, 2}},
    {{17.0f, 247.0f, 16.0f, 16.0f}, {1, 2}},
    {{0.0f, 247.0f, 16.0f, 16.0f}, {1, 1}},
    {{34.0f, 247.0f, 16.0f, 16.0f}, {2, 2}},
    {{17.0f, 247.0f, 16.0f, 16.0f}, {2, 1}},
    {{34.0f, 230.0f, 16.0f, 16.0f}, {2, 0}},
    {{51.0f, 247.0f, 16.0f, 16.0f}, {3, 2}},
    {{68.0f, 247.0f, 16.0f, 16.0f}, {3, 1}},
    {{68.0f, 247.0f, 16.0f, 16.0f}, {4, 2}}
};

std::vector<SpritePart> SMALL_HILL_LAYOUT = {
    {{0.0f, 247.0f, 16.0f, 16.0f}, {0, 1}},
    {{17.0f, 247.0f, 16.0f, 16.0f}, {1, 1}},
    {{34.0f, 230.0f, 16.0f, 16.0f}, {1, 0}},
    {{68.0f, 247.0f, 16.0f, 16.0f}, {2, 1}}
};

std::vector<SpritePart> GRASS_LAYOUT = {
    {{0.0f, 213.0f, 16.0f, 16.0f}, {0, 0}},
    {{17.0f, 213.0f, 16.0f, 16.0f}, {1, 0}},
    {{17.0f, 213.0f, 16.0f, 16.0f}, {2, 0}},
    {{17.0f, 213.0f, 16.0f, 16.0f}, {3, 0}},
    {{34.0f, 213.0f, 16.0f, 16.0f}, {4, 0}}
};

std::vector<SpritePart> CLOUD_LAYOUT = {
    {{298.0f, 33.0f, 16.0f, 16.0f}, {0, 1}},
    {{298.0f, 16.0f, 16.0f, 16.0f}, {0, 0}},
    {{315.0f, 33.0f, 16.0f, 16.0f}, {1, 1}},
    {{315.0f, 16.0f, 16.0f, 16.0f}, {1, 0}},
    {{332.0f, 33.0f, 16.0f, 16.0f}, {2, 1}},
    {{332.0f, 16.0f, 16.0f, 16.0f}, {2, 0}}
};

BackgroundProp::BackgroundProp(float x, float y, Texture2D tex, const std::vector<SpritePart>& parts) 
    : posX(x), posY(y), texture(tex), blueprint(&parts) {}

void BackgroundProp::draw() {
    for (const auto& part : *blueprint) {
        Rectangle dest = { 
            posX + (part.offset.x * TILE_SIZE), 
            posY + (part.offset.y * TILE_SIZE), 
            (float)TILE_SIZE, 
            (float)TILE_SIZE 
        };
        DrawTexturePro(texture, part.source, dest, {0, 0}, 0.0f, WHITE);
    }
}