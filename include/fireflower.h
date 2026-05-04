#ifndef FIREFLOWER_H
#define FIREFLOWER_H

#include <raylib.h>

class FireFlower {
private:
    Vector2 pos;
    Texture2D sprites;
    float animTimer = 0.0f;
    int frame = 0;

public:
    FireFlower(float x, float y, Texture2D s) : pos({x, y}), sprites(s) {}
    void update();
    void draw();
    Rectangle returnRec() const { return {pos.x, pos.y, 42, 42}; }
};

#endif
