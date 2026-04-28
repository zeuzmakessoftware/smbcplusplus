#ifndef MARIO_H
#define MARIO_H

#include <raylib.h>
#include <vector>
#include <memory>
#include "mushroom.h"

#define TILE_SIZE 42 

class Mario {
    private:
        float posX, posY;
        float velX = 0.0f;
        float velY = 0.0f;

        const float acceleration = 0.3f;
        const float friction = 0.25f;
        const float maxSpeed = 6.0f;
        const float gravity = 0.97f;
        const float jumpForce = -20.5f;
        const float terminalVelocity = 12.0f;

        bool isGrounded = false;
        bool facingRight = true;
        Texture2D sprites;

        bool isBig = false;
        bool isTransforming = false;
        float transformationTimer = 0.0f;
        const float transformationDuration = 1.0f;

        float frameTimer = 0.0f;
        int currentFrame = 0;
        const float walkFrames[3] = { 20.0f, 38.0f, 56.0f };
        const float bigWalkFrames[3] = { 20.0f, 38.0f, 56.0f };
        const float frameDuration = 0.1f;

        bool isInvincible = false;
        float invincibilityTimer = 0.0f;
        const float invincibilityDuration = 2.0f;

    public:
        Mario(int x, int y, Texture2D sprites);
        Rectangle returnRec();
        Vector2 getPos();
        void update(const std::vector<Rectangle>& statics, float cameraX, std::vector<std::unique_ptr<Mushroom>>& mushrooms);
        void draw();
        void reset(float x, float y);
        float getVelY() { return velY; }
        void drawDebug();
        bool getIsBig() { return isBig; }
        void setIsBig(bool b) { isBig = b; }
        void setVelY(float y) { velY = y; }
        bool getIsTransforming() const { return isTransforming; }
        void startShrink();
        bool getIsInvincible() const { return isInvincible; }
};

#endif