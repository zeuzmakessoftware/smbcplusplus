#ifndef MARIO_H
#define MARIO_H

#include <raylib.h>
#include <vector>

#define TILE_SIZE 42 // Shared constant

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

        float frameTimer = 0.0f;
        int currentFrame = 0;
        const float walkFrames[3] = { 20.0f, 38.0f, 56.0f };
        const float frameDuration = 0.1f;

    public:
        Mario(int x, int y, Texture2D sprites);
        Rectangle returnRec();
        Vector2 getPos();
        void update(const std::vector<Rectangle>& statics, float cameraX);
        void draw();
        void reset(float x, float y);
        float getVelY() { return velY; }
};

#endif