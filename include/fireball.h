#ifndef FIREBALL_H
#define FIREBALL_H

#include <raylib.h>
#include <vector>

class Fireball {
private:
    Vector2 pos;
    float velX;
    float velY = 0.0f;
    bool alive = true;
    float animTimer = 0.0f;
    int frame = 0;
    Texture2D sprites;

public:
    Fireball(float x, float y, bool facingRight, Texture2D s);
    
    void update(const std::vector<Rectangle>& statics, float cameraX);
    void draw();
    
    Rectangle returnRec() const { return {pos.x, pos.y, 18.0f, 18.0f}; }
    bool shouldRemove() const { return !alive; }
    void destroy() { alive = false; }
};

#endif