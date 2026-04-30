#ifndef CASTLE_FLAGPOLE_H
#define CASTLE_FLAGPOLE_H

#include <raylib.h>
#include "mario.h"
#include "scoreboard.h"

#define TILE_SIZE 42

class CastleFlagpole {
private:
    enum class State {
        Waiting,
        Sliding,
        DroppingFlag,
        FacingRight,
        WalkingToCastle,
        ScoringTime,
        Complete
    };

    float tileX;
    float groundY;
    Texture2D spriteSheet;
    Texture2D mushroomSheet;
    Texture2D marioSheet;
    State state = State::Waiting;
    float marioX = 0.0f;
    float marioY = 0.0f;
    float flagY = 0.0f;
    float stateTimer = 0.0f;
    float timePayoutTimer = 0.0f;
    bool bigMario = false;
    bool fireMario = false;
    bool marioVisible = true;
    bool levelFinished = false;
    int poleBonusAwarded = 0;

    float poleX() const;
    float poleTopY() const;
    float poleBottomY() const;
    float castleDoorX() const;
    Rectangle triggerRec() const;
    Rectangle marioDest() const;
    Rectangle invisibleCollisionRec() const;
    int poleBonusForCatchY(float catchY) const;
    void drawMarioPlaceholder(Rectangle dest) const;

public:
    CastleFlagpole(float tileX, float groundY, Texture2D spriteSheet, Texture2D mushroomSheet, Texture2D marioSheet);

    void reset();
    void update(Mario& mario, Scoreboard& scoreboard, bool& isDead);
    void draw() const;
    Rectangle returnCollisionRec() const;
    bool isActive() const;
    bool isComplete() const;
};

#endif
