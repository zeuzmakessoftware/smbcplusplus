#ifndef GOOMBA_H
#define GOOMBA_H

#include <raylib.h>
#include <vector>

class Goomba {
private:
    Vector2 pos;
    float velX = -2.0f;
    float velY = 0.0f;
    bool isSquashed = false;
    bool isAlive = true;
    float squashTimer = 1.0f;
    
    Texture2D sprites;
    float frameTimer = 0.0f;
    int currentFrame = 0;

public:
    Goomba(float x, float y, Texture2D s);
    void update(const std::vector<Rectangle>& statics, Rectangle marioRec, bool& marioIsDead, bool& marioIsBig, float& marioVelY, float& deathTimer);
    void draw();
    bool shouldRemove() const { return !isAlive; }
};

#endif