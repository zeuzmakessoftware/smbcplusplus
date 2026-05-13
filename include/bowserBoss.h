#ifndef BOWSER_BOSS_H
#define BOWSER_BOSS_H

#include <memory>
#include <vector>
#include <raylib.h>
#include "fireball.h"
#include "mario.h"

class BowserBoss {
private:
    struct Flame {
        Vector2 pos;
        float animTimer = 0.0f;
        int frame = 0;
    };

    Vector2 pos;
    Texture2D sprites;
    std::vector<Flame> flames;
    bool active = false;
    bool alive = true;
    bool falling = false;
    bool grounded = false;
    bool defeatedThisFrame = false;
    int hp = 5;
    float velX = -54.0f;
    float velY = 0.0f;
    float frameTimer = 0.0f;
    int frame = 0;
    float jumpTimer = 1.4f;
    float flameTimer = 0.9f;
    float firePoseTimer = 0.0f;
    float leftBound;
    float rightBound;

    static constexpr float Width = 84.0f;
    static constexpr float Height = 84.0f;
    static constexpr float FlameWidth = 63.0f;
    static constexpr float FlameHeight = 21.0f;
    static constexpr float Gravity = 900.0f;

    void hurtMario(Mario& marioObj, bool& marioIsDead, float& deathTimer);
    void updateFlames(Mario& marioObj, bool& marioIsDead, float& deathTimer, float cameraX);
    void spawnFlame();

public:
    BowserBoss(float x, float y, float leftBound, float rightBound, Texture2D sprites);

    void update(
        const std::vector<Rectangle>& statics,
        Mario& marioObj,
        bool& marioIsDead,
        float& deathTimer,
        float cameraX,
        std::vector<std::unique_ptr<Fireball>>& fireballs
    );
    void updateFalling(Mario& marioObj, bool& marioIsDead, float& deathTimer, float cameraX);
    void draw() const;
    void dropFromBridge();
    Rectangle returnRec() const;
    bool isAlive() const { return alive; }
    bool justDefeated();
};

#endif
