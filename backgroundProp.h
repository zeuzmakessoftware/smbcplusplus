#ifndef BACKGROUND_PROP_H
#define BACKGROUND_PROP_H

#include <raylib.h>
#include <vector>

#define TILE_SIZE 42

struct SpritePart {
    Rectangle source;
    Vector2 offset;
};

extern std::vector<SpritePart> HILL_LAYOUT;
extern std::vector<SpritePart> SMALL_HILL_LAYOUT;
extern std::vector<SpritePart> GRASS_LAYOUT;
extern std::vector<SpritePart> CLOUD_LAYOUT;

class BackgroundProp {
private:
    float posX, posY;
    Texture2D texture;
    const std::vector<SpritePart>* blueprint;

public:
    BackgroundProp(float x, float y, Texture2D tex, const std::vector<SpritePart>& parts);
    void draw();
};

#endif