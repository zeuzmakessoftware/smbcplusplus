#ifndef KOOPA_H
#define KOOPA_H

#include <raylib.h>
#include <vector>
#include "mario.h"
#include "sceneType.h"

class Koopa {
private:
    enum class State {
        Walking,
        ShellStill,
        ShellMoving,
        Flipped
    };

    Vector2 pos;
    float velX = -1.35f;
    float velY = 0.0f;
    bool isAlive = true;
    bool isActivated = false;
    Texture2D sprites;
    const SceneType* scene;
    State state = State::Walking;
    float frameTimer = 0.0f;
    int currentFrame = 0;
    float rotation = 0.0f;
    bool defeatedThisFrame = false;
    bool facingRight = false;
    bool ignoreMarioUntilSeparated = false;

    static constexpr float Width = 42.0f;
    static constexpr float WalkHeight = 63.0f;
    static constexpr float ShellHeight = 42.0f;
    static constexpr float Gravity = 0.97f;
    static constexpr float ShellSpeed = 7.0f;

    float height() const;
    void updatePhysics(const std::vector<Rectangle>& statics);
    void hurtMario(Mario& marioObj, bool& marioIsDead, float& deathTimer);
    void becomeShell();
    void kickShell(float marioCenterX);

public:
    Koopa(float x, float y, Texture2D s, const SceneType& scene = GetSceneType(SceneKind::Overworld));
    void update(const std::vector<Rectangle>& statics, Mario& marioObj, bool& marioIsDead, float& deathTimer, float cameraX);
    void draw();
    void drawDebug();
    bool shouldRemove() const { return !isAlive; }
    Rectangle returnRec() const;
    Vector2 getPos() const { return pos; }
    bool isMovingShell() const { return state == State::ShellMoving; }
    bool isFlippedOrDead() const { return state == State::Flipped || !isAlive; }
    void flip();
    void hitByShell();
    bool justDefeated();
};

#endif
