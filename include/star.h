#ifndef STAR_H
#define STAR_H

#include <raylib.h>
#include <vector>

class Star {
private:
    Vector2 pos;
    float velX = 3.0f;
    float velY = 0.0f;
    Texture2D sprites;
    float animTimer = 0.0f;
    int frame = 0;

public:
    Star(float x, float y, Texture2D s) : pos({x, y}), sprites(s) {}
    void update(const std::vector<Rectangle>& statics);
    void draw();
    Rectangle returnRec() const { return {pos.x, pos.y, 42.0f, 42.0f}; }
};

#endif
