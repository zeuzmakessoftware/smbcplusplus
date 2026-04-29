#include "blocks.h"
#include <iostream>

static std::vector<BlockDefinition>& MutableBlockDefinitions() {
    static std::vector<BlockDefinition> blocks;
    return blocks;
}

BlockRegistration::BlockRegistration(const char* displayName, const char* className, Rectangle source) {
    MutableBlockDefinitions().push_back({displayName, className, source});
}

const std::vector<BlockDefinition>& GetBlockDefinitions() {
    return MutableBlockDefinitions();
}

const BlockDefinition* FindBlockDefinitionByClassName(const std::string& className) {
    for (const BlockDefinition& block : GetBlockDefinitions()) {
        if (className == block.className) {
            return &block;
        }
    }
    return nullptr;
}

Block::Block(int x, int y, Texture2D sprites) : rectXPos(x), rectYPos(y), spriteSheet(sprites) {}

Rectangle Block::returnRec() {
    return {(float)rectXPos + 4, (float)rectYPos, (float)TILE_SIZE - 8, (float)TILE_SIZE};
}

BrickBlock::BrickBlock(int x, int y, Texture2D sprites) : Block(x, y, sprites) {}

Rectangle BrickBlock::getSensor() {
    return {(float)rectXPos + 12, (float)rectYPos + TILE_SIZE - 2, (float)TILE_SIZE - 24, 10.0f};
}

void BrickBlock::update(Rectangle marioRec, float marioVelY, bool isBig) {
    if (!isBumping && CheckCollisionRecs(marioRec, getSensor())) {
        wasHitThisFrame = true;
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
        (Rectangle){ 17.0f, 16.0f, 16.0f, 16.0f }, 
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

void BrickBlock::drawParticles(std::vector<Particle>& particles, Texture2D spriteSheet) {
    for (auto& p : particles) {
        DrawTexturePro(spriteSheet, 
            (Rectangle){ 17.0f, 16.0f, 8.0f, 8.0f },
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

EmptyBlock::EmptyBlock(int x, int y, Texture2D sprites) : Block(x, y, sprites) {}

void EmptyBlock::draw() {
    DrawTexturePro(spriteSheet, 
        (Rectangle){ 349.0f, 78.0f, 16.0f, 16.0f }, 
        (Rectangle){ (float)rectXPos, (float)rectYPos, (float)TILE_SIZE, (float)TILE_SIZE }, 
        (Vector2){ 0, 0 }, 0.0f, WHITE);
}

REGISTER_LEVEL_EDITOR_BLOCK(EmptyBlock, (Rectangle){ 349.0f, 78.0f, 16.0f, 16.0f });

PowerUpBlock::PowerUpBlock(int x, int y, Texture2D sprites, Texture2D itemTex, std::string type) 
    : Block(x, y, sprites), itemTexture(itemTex), itemType(type) {
    itemX = (float)x;
    itemY = (float)y;
}

Rectangle PowerUpBlock::getSensor() {
    return {(float)rectXPos + 12, (float)rectYPos + TILE_SIZE - 2, (float)TILE_SIZE - 24, 10.0f};
}

std::unique_ptr<Mushroom> PowerUpBlock::takeMushroom() {
    return std::move(releasedMushroom);
}

std::unique_ptr<FireFlower> PowerUpBlock::takeFireFlower() {
    return std::move(releasedFireFlower);
}

void PowerUpBlock::update(Rectangle marioRec, float marioVelY, bool isBig) {
    if (!isSpent) {
        animTimer += GetFrameTime();
        if (animTimer > 0.20f) {
            frame = (frame + 1) % 3;
            animTimer = 0;
        }
    }

    if (!isSpent && !isBumping && CheckCollisionRecs(marioRec, getSensor())) {
        wasHitThisFrame = true;
        isBumping = true;
        bumpTimer = 0.1f;
        isSpent = true;
        itemActive = true;
        
        if (itemType == "coin") {
            spawnTimer = 0.1f; 
        } else if (itemType == "mushroom" || itemType == "fireflower") {
            spawnTimer = 1.0f;
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

    if (itemActive) {
        if (itemType == "coin") {
            spawnTimer -= GetFrameTime();
            itemY -= 15.0f;
            if (spawnTimer <= 0) {
                itemActive = false;
            }
        } 
        else if (itemType == "mushroom" || itemType == "fireflower") {
            if (spawnTimer > 0) {
                spawnTimer -= GetFrameTime();
                itemY -= (TILE_SIZE * GetFrameTime());
                if (spawnTimer <= 0) {
                    if (itemType == "mushroom") {
                        releasedMushroom = std::make_unique<Mushroom>(itemX, itemY, itemTexture);
                    } else {
                        releasedFireFlower = std::make_unique<FireFlower>(itemX, itemY, itemTexture);
                    }
                    itemActive = false; 
                }
            }
        }
    }
}

void PowerUpBlock::draw() {
    if (itemActive) {
        Rectangle src;
        if (itemType == "coin") src = { 298.0f, 95.0f, 16.0f, 16.0f };
        else if (itemType == "mushroom") src = { 0.0f, 8.0f, 16.0f, 16.0f };
        else if (itemType == "fireflower") src = { 32.0f, 44.0f, 16.0f, 16.0f };

        DrawTexturePro(itemTexture, src,
            (Rectangle){ itemX, itemY, (float)TILE_SIZE, (float)TILE_SIZE },
            {0,0}, 0.0f, WHITE);
    }

    Rectangle blockSrc = isSpent ? (Rectangle){ 349.0f, 78.0f, 16.0f, 16.0f } 
                                 : (Rectangle){ 298.0f + (frame * 17.0f), 78.0f, 16.0f, 16.0f };
    
    DrawTexturePro(spriteSheet, blockSrc, 
        (Rectangle){ (float)rectXPos, (float)rectYPos + offsetY, (float)TILE_SIZE, (float)TILE_SIZE }, 
        {0,0}, 0.0f, WHITE);
}

void PowerUpBlock::drawDebug() {
    DrawRectangleLinesEx(returnRec(), 1.0f, BLUE);
    DrawRectangleLinesEx(getSensor(), 1.0f, RED);
}

bool PowerUpBlock::justBumped() {
    if (wasHitThisFrame) {
        wasHitThisFrame = false;
        return true;
    }
    return false;
}

PipeBlock::PipeBlock(int x, int y, int width, int height, Texture2D sprites) 
    : Block(x, y, sprites), tilesWide(width), tilesHigh(height) {}

Rectangle PipeBlock::returnRec() {
    return { (float)rectXPos, (float)rectYPos, (float)tilesWide * TILE_SIZE, (float)tilesHigh * TILE_SIZE };
}

void PipeBlock::draw() {
    for (int i = 0; i < tilesWide; i++) {
        for (int j = 0; j < tilesHigh; j++) {
            Rectangle src;

            if (j == 0) { 
                src = (i == 0) ? (Rectangle){ 119.0f, 196.0f, 16.0f, 16.0f }
                               : (Rectangle){ 136.0f, 196.0f, 16.0f, 16.0f };
            } else { 
                src = (i == 0) ? (Rectangle){ 119.0f, 213.0f, 16.0f, 16.0f }
                               : (Rectangle){ 136.0f, 213.0f, 16.0f, 16.0f };
            }

            DrawTexturePro(spriteSheet, src,
                (Rectangle){ 
                    (float)rectXPos + (i * TILE_SIZE), 
                    (float)rectYPos + (j * TILE_SIZE), 
                    (float)TILE_SIZE, 
                    (float)TILE_SIZE 
                },
                {0, 0}, 0.0f, WHITE);
        }
    }
}

ShinyBlock::ShinyBlock(int x, int y, Texture2D sprites) : Block(x, y, sprites) {}

void ShinyBlock::draw() {
    DrawTexturePro(spriteSheet, 
        (Rectangle){ 0.0f, 33.0f, 16.0f, 16.0f }, 
        (Rectangle){ (float)rectXPos, (float)rectYPos, (float)TILE_SIZE, (float)TILE_SIZE }, 
        (Vector2){ 0, 0 }, 0.0f, WHITE);
}

REGISTER_LEVEL_EDITOR_BLOCK(ShinyBlock, (Rectangle){ 0.0f, 33.0f, 16.0f, 16.0f });
