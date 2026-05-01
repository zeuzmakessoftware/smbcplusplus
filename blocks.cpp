#include "blocks.h"
#include <cmath>
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

Block::Block(int x, int y, Texture2D sprites, const SceneType& scene)
    : rectXPos(x), rectYPos(y), spriteSheet(sprites), scene(&scene) {}

Rectangle Block::returnRec() {
    return {(float)rectXPos + 4, (float)rectYPos, (float)TILE_SIZE - 8, (float)TILE_SIZE};
}

Coin::Coin(float x, float y, Texture2D sprites)
    : posX(x), posY(y), spriteSheet(sprites) {}

Rectangle Coin::returnRec() const {
    return {posX + 8.0f, posY + 2.0f, (float)TILE_SIZE - 16.0f, (float)TILE_SIZE - 4.0f};
}

bool Coin::update(Rectangle marioRec) {
    animTimer += GetFrameTime();
    if (animTimer >= 0.08f) {
        animTimer = 0.0f;
        frame = (frame + 1) % 4;
    }

    if (!collected && CheckCollisionRecs(marioRec, returnRec())) {
        collected = true;
        return true;
    }

    return false;
}

void Coin::draw() {
    if (collected) return;

    float sourceX = 180.0f + (frame * 10.0f);
    DrawTexturePro(
        spriteSheet,
        (Rectangle){ sourceX, 36.0f, 8.0f, 16.0f },
        (Rectangle){ posX + 10.0f, posY, 22.0f, (float)TILE_SIZE },
        (Vector2){ 0, 0 },
        0.0f,
        WHITE
    );
}

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

EmptyBlock::EmptyBlock(int x, int y, Texture2D sprites, const SceneType& scene) : Block(x, y, sprites, scene) {}

void EmptyBlock::draw() {
    DrawTexturePro(spriteSheet, 
        scene->emptyBlock, 
        (Rectangle){ (float)rectXPos, (float)rectYPos, (float)TILE_SIZE, (float)TILE_SIZE }, 
        (Vector2){ 0, 0 }, 0.0f, WHITE);
}

REGISTER_LEVEL_EDITOR_BLOCK(EmptyBlock, (Rectangle){ 349.0f, 78.0f, 16.0f, 16.0f });

PowerUpBlock::PowerUpBlock(int x, int y, Texture2D sprites, Texture2D itemTex, std::string type, const SceneType& scene) 
    : Block(x, y, sprites, scene), itemTexture(itemTex), itemType(type) {
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

void PowerUpBlock::update(Rectangle marioRec, float& marioVelY, bool isBig) {
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
            spawnTimer = 0.3f;
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

            float progress = (0.3f - spawnTimer) / 0.3f; 
            float arc = sinf(progress * PI); 
            itemY = (float)rectYPos - (arc * 100.0f);

            coinTimer += GetFrameTime();
            if (coinTimer > 0.05f) {
                coinFrame = (coinFrame + 1) % 4;
                coinTimer = 0;
            }

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
        if (itemType == "coin") {
            float frameX = 180.0f + (coinFrame * 10.0f); 
            src = (Rectangle){ frameX, 36.0f, 8.0f, 16.0f };
            
            DrawTexturePro(itemTexture, src,
                (Rectangle){ (float)itemX + TILE_SIZE / 4, itemY, (float)TILE_SIZE / 2, (float)TILE_SIZE },
                {0,0}, 0.0f, WHITE);
        }
        else if (itemType == "mushroom") {
            src = { 0.0f, 8.0f, 16.0f, 16.0f };
            DrawTexturePro(itemTexture, src,
                (Rectangle){ itemX, itemY, (float)TILE_SIZE, (float)TILE_SIZE },
                {0,0}, 0.0f, WHITE);
        }
        else if (itemType == "fireflower") {
            src = { 32.0f, 44.0f, 16.0f, 16.0f };
            DrawTexturePro(itemTexture, src,
                (Rectangle){ itemX, itemY, (float)TILE_SIZE, (float)TILE_SIZE },
                {0,0}, 0.0f, WHITE);
        }
    }

    Rectangle blockSrc = isSpent ? scene->emptyBlock : scene->questionBlockFrames[frame];
    
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

PipeBlock::PipeBlock(int x, int y, int width, int height, Texture2D sprites, const SceneType& scene, PipeOrientation orientation) 
    : Block(x, y, sprites, scene), tilesWide(width), tilesHigh(height), orientation(orientation) {}

Rectangle PipeBlock::returnRec() {
    return { (float)rectXPos, (float)rectYPos, (float)tilesWide * TILE_SIZE, (float)tilesHigh * TILE_SIZE };
}

void PipeBlock::draw() {
    if (orientation != PipeOrientation::Vertical) {
        for (int i = 0; i < tilesWide; i++) {
            for (int j = 0; j < tilesHigh; j++) {
                bool useLeftSide = i == 0;
                Rectangle src;
                if (useLeftSide) {
                    src = (j == 0) ? (Rectangle){164.0f + 85.0f, 230.0f, 16.0f, 16.0f}
                                   : (Rectangle){164.0f + 85.0f, 247.0f, 16.0f, 16.0f};
                } else {
                    src = (j == 0) ? (Rectangle){164.0f + 102.0f, 230.0f, 16.0f, 16.0f}
                                   : (Rectangle){164.0f + 102.0f, 247.0f, 16.0f, 16.0f};
                }
                float destX = (float)rectXPos + (i * TILE_SIZE);
                if (orientation == PipeOrientation::HorizontalLeft) {
                    src.width = -src.width;
                    destX = (float)rectXPos + ((tilesWide - 1 - i) * TILE_SIZE);
                }

                DrawTexturePro(spriteSheet, src,
                    (Rectangle){
                        destX,
                        (float)rectYPos + (j * TILE_SIZE),
                        (float)TILE_SIZE,
                        (float)TILE_SIZE
                    },
                    {0, 0}, 0.0f, WHITE);
            }
        }
        return;
    }

    for (int i = 0; i < tilesWide; i++) {
        for (int j = 0; j < tilesHigh; j++) {
            Rectangle src;

            if (j == 0) { 
                src = (i == 0) ? scene->pipeTopLeft : scene->pipeTopRight;
            } else { 
                src = (i == 0) ? scene->pipeBodyLeft : scene->pipeBodyRight;
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

WarpPipeBlock::WarpPipeBlock(
    int x,
    int y,
    int width,
    int height,
    Texture2D sprites,
    WarpDestination destination,
    Vector2 exitPosition,
    const SceneType& scene,
    PipeOrientation orientation
) : PipeBlock(x, y, width, height, sprites, scene, orientation),
    destination(destination),
    exitPosition(exitPosition) {}

bool WarpPipeBlock::canEnter(Rectangle marioRec, bool downPressed, bool rightPressed, bool leftPressed) const {
    Rectangle pipeRec = const_cast<WarpPipeBlock*>(this)->returnRec();
    PipeOrientation orientation = getOrientation();

    if (orientation == PipeOrientation::Vertical) {
        float marioCenter = marioRec.x + marioRec.width * 0.5f;
        bool centered = marioCenter >= pipeRec.x + 10.0f && marioCenter <= pipeRec.x + pipeRec.width - 10.0f;
        bool standingOnPipe = fabsf((marioRec.y + marioRec.height) - pipeRec.y) <= 3.0f;
        return downPressed && centered && standingOnPipe;
    }

    if (orientation == PipeOrientation::HorizontalRight) {
        float marioMidY = marioRec.y + marioRec.height * 0.5f;
        bool alignedY = marioMidY >= pipeRec.y && marioMidY <= pipeRec.y + pipeRec.height;
        bool atMouth = fabsf((marioRec.x + marioRec.width) - pipeRec.x) <= 6.0f;
        return rightPressed && alignedY && atMouth;
    }

    float marioMidY = marioRec.y + marioRec.height * 0.5f;
    bool alignedY = marioMidY >= pipeRec.y && marioMidY <= pipeRec.y + pipeRec.height;
    bool atMouth = fabsf(marioRec.x - (pipeRec.x + pipeRec.width)) <= 6.0f;
    return leftPressed && alignedY && atMouth;
}

ShinyBlock::ShinyBlock(int x, int y, Texture2D sprites, const SceneType& scene) : Block(x, y, sprites, scene) {}

void ShinyBlock::draw() {
    DrawTexturePro(spriteSheet, 
        scene->solidBlock, 
        (Rectangle){ (float)rectXPos, (float)rectYPos, (float)TILE_SIZE, (float)TILE_SIZE }, 
        (Vector2){ 0, 0 }, 0.0f, WHITE);
}

REGISTER_LEVEL_EDITOR_BLOCK(ShinyBlock, (Rectangle){ 0.0f, 33.0f, 16.0f, 16.0f });
