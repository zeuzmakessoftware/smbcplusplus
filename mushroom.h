#ifndef MUSHROOM_H
#define MUSHROOM_H
#include <raylib.h>
#include <vector>

class Mushroom {
private:
    Vector2 pos;
    float velX = 3.0f;
    float velY = 0;
    Texture2D sprites;
public:
    Mushroom(float x, float y, Texture2D s) : pos({x, y}), sprites(s) {}
    void update(const std::vector<Rectangle>& statics);
    void draw();
    Rectangle returnRec() { return {pos.x, pos.y, 42, 42}; }
};
#endif