#ifndef GOOMBA_H
#define GOOMBA_H

#include <raylib.h>
#include <vector>
#include "mario.h"
#include "sceneType.h"

class Goomba {
private:
    Vector2 pos;
    float velX = -2.0f;
    float velY = 0.0f;
    bool isSquashed = false;
    bool isAlive = true;
    bool isActivated = false;
    float squashTimer = 1.0f;
    
    Texture2D sprites;
    const SceneType* scene;
    float frameTimer = 0.0f;
    int currentFrame = 0;

    bool isFlipped = false;
    float rotation = 0.0f;
    bool defeatedThisFrame = false;

public:
    Goomba(float x, float y, Texture2D s, const SceneType& scene = GetSceneType(SceneKind::Overworld));
    void update(const std::vector<Rectangle>& statics, Rectangle marioRec, bool& marioIsDead, bool& marioIsBig, float& marioVelY, float& deathTimer);
    void draw();
    bool shouldRemove() const { return !isAlive; }
    void update(const std::vector<Rectangle>& statics, Mario& marioObj, bool& marioIsDead, float& deathTimer, float cameraX);
    void updatePhysics(const std::vector<Rectangle>& statics);
    void drawDebug();
    void flip() {
        if (!isFlipped && !isSquashed) {
            isFlipped = true;
            defeatedThisFrame = true;
            velY = -15.0f;
            velX = 2.0f;
        }
    }
    Vector2 getPos() const { return pos; }
    bool justDefeated();
};

#endif
