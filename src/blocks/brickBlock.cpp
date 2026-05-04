#include "blocks/brickBlock.h"

BrickBlock::BrickBlock(int x, int y, Texture2D sprites, const SceneType& scene) : Block(x, y, sprites, scene) {}

Rectangle BrickBlock::getSensor() {
    return {(float)rectXPos + 12, (float)rectYPos + TILE_SIZE - 2, (float)TILE_SIZE - 24, 10.0f};
}

void BrickBlock::update(Rectangle marioRec, float& marioVelY, bool isBig) {
    if (!isBumping && CheckCollisionRecs(marioRec, getSensor())) {
        wasHitThisFrame = true;
        if (marioVelY < 0.0f) {
            marioVelY = 0.0f;
        }
        if (isBig) {
            destroyed = true;
        } else {
            isBumping = true;
            bumpTimer = 0.1f;
        }
    }

    if (isBumping) {
        bumpTimer -= GetFrameTime();
        if (bumpTimer > 0.05f) offsetY = -10.0f;
        else if (bumpTimer > 0) offsetY = -5.0f;
        else {
            offsetY = 0;
            isBumping = false;
        }
    }
}

void BrickBlock::draw() {
    DrawTexturePro(spriteSheet,
        scene->brickBlock,
        (Rectangle){ (float)rectXPos, (float)rectYPos + offsetY, (float)TILE_SIZE, (float)TILE_SIZE },
        (Vector2){ 0, 0 }, 0.0f, WHITE);
}

REGISTER_LEVEL_EDITOR_BLOCK(BrickBlock, (Rectangle){ 17.0f, 16.0f, 16.0f, 16.0f });

void BrickBlock::drawDebug() {
    DrawRectangleLinesEx(returnRec(), 1.0f, BLUE);
    DrawRectangleLinesEx(getSensor(), 1.0f, RED);
}

void BrickBlock::SpawnBrickParticles(std::vector<Particle>& particles) {
    float speeds[2] = { -4.0f, 4.0f };
    float jumps[2] = { -8.0f, -12.0f };

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            particles.push_back({
                { (float)rectXPos + (i * 20), (float)rectYPos + (j * 20) },
                { speeds[i], jumps[j] },
                0.0f, true
            });
        }
    }
}

void BrickBlock::updateParticles(std::vector<Particle>& particles) {
    for (int i = 0; i < particles.size(); i++) {
        particles[i].pos.x += particles[i].vel.x;
        particles[i].pos.y += particles[i].vel.y;
        particles[i].vel.y += 0.5f;
        particles[i].rotation += 12.0f;

        if (particles[i].pos.y > 800) {
            particles.erase(particles.begin() + i);
            i--;
        }
    }
}

void BrickBlock::drawParticles(std::vector<Particle>& particles, Texture2D spriteSheet, const SceneType& scene) {
    for (auto& p : particles) {
        DrawTexturePro(spriteSheet,
            (Rectangle){ scene.brickBlock.x, scene.brickBlock.y, 8.0f, 8.0f },
            (Rectangle){ p.pos.x, p.pos.y, 20.0f, 20.0f },
            (Vector2){ 10, 10 }, p.rotation, WHITE);
    }
}

bool BrickBlock::justBumped() {
    if (wasHitThisFrame) {
        wasHitThisFrame = false;
        return true;
    }
    return false;
}
