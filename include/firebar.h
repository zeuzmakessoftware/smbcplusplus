#ifndef FIREBAR_H
#define FIREBAR_H

#include <raylib.h>
#include <vector>
#include "mario.h"

class FireBar {
private:
    Vector2 pivot;
    int length;
    bool clockwise;
    float angle;
    float angularSpeed;
    float animTimer = 0.0f;
    int frame = 0;
    Texture2D sprites;

    static constexpr float FireballSize = 18.0f;
    static constexpr float FireballRadius = FireballSize * 0.5f;
    static constexpr float FireballSpacing = 21.0f;
    static constexpr float ActivationPadding = 96.0f;

    Vector2 ballCenter(int index) const;
    void hurtMario(Mario& marioObj, bool& marioIsDead, float& deathTimer);

public:
    FireBar(float pivotX, float pivotY, int length, Texture2D sprites, bool clockwise = true, float startAngle = 0.0f);

    void update(Mario& marioObj, bool& marioIsDead, float& deathTimer, float cameraX);
    void draw() const;
};

#endif
