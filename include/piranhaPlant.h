#ifndef PIRANHA_PLANT_H
#define PIRANHA_PLANT_H

#include <raylib.h>
#include "mario.h"

class PiranhaPlant {
private:
    enum class State {
        Hidden,
        Emerging,
        Exposed,
        Retreating
    };

    Vector2 pos;
    Rectangle pipeRec;
    Texture2D sprites;
    State state = State::Hidden;
    bool isAlive = true;
    bool isActivated = false;
    bool defeatedThisFrame = false;
    float stateTimer = 0.0f;
    float frameTimer = 0.0f;
    int currentFrame = 0;

    static constexpr float Width = 42.0f;
    static constexpr float Height = 63.0f;
    static constexpr float MoveSpeed = 67.0f;
    static constexpr float HiddenDelay = 1.0f;
    static constexpr float ExposedDelay = 1.25f;

    float hiddenY() const;
    float exposedY() const;
    bool marioBlocksEmergence(Rectangle marioRec) const;
    void hurtMario(Mario& marioObj, bool& marioIsDead, float& deathTimer);

public:
    PiranhaPlant(float pipeX, float pipeY, float pipeWidth, Texture2D sprites);

    void update(Mario& marioObj, bool& marioIsDead, float& deathTimer, float cameraX);
    void draw();
    void drawDebug();

    Rectangle returnRec() const;
    Vector2 getPos() const { return pos; }
    bool shouldRemove() const { return !isAlive; }
    void defeat();
    bool justDefeated();
};

#endif
