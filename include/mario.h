#ifndef MARIO_H
#define MARIO_H

#include <raylib.h>
#include <vector>
#include <memory>
#include "mushroom.h"
#include "fireflower.h"
#include "fireball.h"

#define TILE_SIZE 42 

class Mario {
    private:
        float posX, posY;
        float velX = 0.0f;
        float velY = 0.0f;

        const float walkAcceleration = 0.10f;
        const float runAcceleration = 0.25f;
        const float friction = 0.25f;
        
        const float walkMaxSpeed = 4.0f;
        const float runMaxSpeed = 7.6f;
        
        const float gravity = 0.67f;
        const float jumpForce = -15.5f;
        const float terminalVelocity = 12.0f;

        bool isGrounded = false;
        bool facingRight = true;
        Texture2D sprites;

        bool isBig = false;
        bool isFire = false;
        bool isTransforming = false;
        float transformationTimer = 0.0f;
        const float transformationDuration = 1.0f;
        
        bool isFireTransforming = false;
        float fireTransformTimer = 0.0f;
        const float fireTransformDuration = 0.8f;

        float frameTimer = 0.0f;
        int currentFrame = 0;
        const float walkFrames[3] = { 20.0f, 38.0f, 56.0f };
        const float bigWalkFrames[3] = { 20.0f, 38.0f, 56.0f };
        const float frameDuration = 0.1f;

        bool isInvincible = false;
        float invincibilityTimer = 0.0f;
        const float invincibilityDuration = 2.0f;
        int collectedOneUps = 0;

    public:
        Mario(int x, int y, Texture2D sprites);
        Rectangle returnRec();
        Vector2 getPos();
        void update(
            const std::vector<Rectangle>& statics,
            float cameraX,
            std::vector<std::unique_ptr<Mushroom>>& mushrooms,
            std::vector<std::unique_ptr<FireFlower>>& fireFlowers,
            std::vector<std::unique_ptr<Fireball>>& fireballs,
            Texture2D fireballSheet
        );
        void draw();
        void reset(float x, float y);
        float getVelY() { return velY; }
        void drawDebug();
        bool getIsBig() { return isBig; }
        void setIsBig(bool b) { isBig = b; }
        bool getIsFire() const { return isFire; }
        void setVelY(float y) { velY = y; }
        void setScriptedPose(float x, float y, bool faceRight);
        bool getIsTransforming() const { return isTransforming; }
        bool getIsFireTransforming() const { return isFireTransforming; }
        void startShrink();
        bool getIsInvincible() const { return isInvincible; }
        int takeCollectedOneUps();
};

#endif
