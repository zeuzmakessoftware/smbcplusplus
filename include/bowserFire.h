#ifndef BOWSER_FIRE_H
#define BOWSER_FIRE_H

#include <raylib.h>
#include "mario.h"

class BowserFire {
private:
    Vector2 trigger;
    Vector2 pos;
    Texture2D sprites;
    bool active = false;
    bool spent = false;
    float animTimer = 0.0f;
    int frame = 0;

    static constexpr float Width = 63.0f;
    static constexpr float Height = 21.0f;
    static constexpr float Speed = 200.0f;
    static constexpr float ActivationPadding = 16.0f;
    static constexpr float SpawnPadding = 8.0f;

    void hurtMario(Mario& marioObj, bool& marioIsDead, float& deathTimer);

public:
    BowserFire(float triggerX, float y, Texture2D sprites);

    void update(Mario& marioObj, bool& marioIsDead, float& deathTimer, float cameraX, float screenWidth);
    void draw() const;
    bool shouldRemove() const { return spent; }
    Rectangle returnRec() const;
};

#endif
