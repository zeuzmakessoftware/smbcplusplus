#ifndef LIFT_H
#define LIFT_H

#include <raylib.h>
#include "mario.h"

enum class LiftMovement {
    VerticalWrap,
    VerticalBounce,
    HorizontalBounce
};

class Lift {
private:
    Vector2 pos;
    Vector2 previousPos;
    Texture2D sprites;
    float width;
    float height = 21.0f;
    float speed;
    float minTravel;
    float maxTravel;
    int direction;
    LiftMovement movement;

public:
    Lift(
        float x,
        float y,
        float platformWidth,
        Texture2D sprites,
        LiftMovement movement,
        float minTravel,
        float maxTravel,
        float speed,
        int direction = 1
    );

    static Lift VerticalWrap(float x, float y, float width, Texture2D sprites, float topY, float bottomY, float speed, bool movesDown);
    static Lift VerticalBounce(float x, float y, float width, Texture2D sprites, float topY, float bottomY, float speed, bool startsDown);
    static Lift HorizontalBounce(float x, float y, float width, Texture2D sprites, float leftX, float rightX, float speed, bool startsRight);

    void update(Mario& mario, const std::vector<Rectangle>& solids, float cameraX);
    void draw() const;
    Rectangle returnRec() const;
    Vector2 delta() const;
};

#endif
