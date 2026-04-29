#ifndef BLOCKS_H
#define BLOCKS_H

#include <raylib.h>
#include <string>
#include <vector>
#include <memory>
#include "mushroom.h"

#define TILE_SIZE 42

struct Particle {
    Vector2 pos;
    Vector2 vel;
    float rotation;
    bool active;
};

struct BlockDefinition {
    const char* displayName;
    const char* className;
    Rectangle source;
};

const std::vector<BlockDefinition>& GetBlockDefinitions();
const BlockDefinition* FindBlockDefinitionByClassName(const std::string& className);

class BlockRegistration {
public:
    BlockRegistration(const char* displayName, const char* className, Rectangle source);
};

#define REGISTER_LEVEL_EDITOR_BLOCK(BLOCK_CLASS, ...) \
    namespace { \
        BlockRegistration BLOCK_CLASS##_registration(#BLOCK_CLASS, #BLOCK_CLASS, __VA_ARGS__); \
    }

class Block {
protected:
    int rectXPos;
    int rectYPos;
    Texture2D spriteSheet;

public:
    Block(int x, int y, Texture2D sprites);
    virtual ~Block() {}

    virtual Rectangle returnRec();
    virtual void update(Rectangle marioRec, float marioVelY, bool isBig = false) = 0; 
    virtual void draw() = 0;
    virtual bool justBumped() { return false; }
    
    int getRectX() { return rectXPos; }
    int getRectY() { return rectYPos; }

    virtual void drawDebug() {}
};

class BrickBlock : public Block {
private:
    float offsetY = 0;
    float bumpTimer = 0;
    bool isBumping = false;
    bool destroyed = false; 
    bool wasHitThisFrame = false;

public:
    BrickBlock(int x, int y, Texture2D sprites);
    Rectangle getSensor();
    void update(Rectangle marioRec, float marioVelY, bool isBig) override; 
    void draw() override;
    bool justBumped() override;
    void drawDebug() override;
    bool isDestroyed() { return destroyed; }
    
    static void updateParticles(std::vector<Particle>& particles);
    static void drawParticles(std::vector<Particle>& particles, Texture2D spriteSheet);
    void SpawnBrickParticles(std::vector<Particle>& particles);
};

class EmptyBlock : public Block {
public:
    EmptyBlock(int x, int y, Texture2D sprites);
    void update(Rectangle marioRec, float marioVelY, bool isBig) override {} 
    void draw() override;
};

class PowerUpBlock : public Block {
private:
    float offsetY = 0;
    float bumpTimer = 0;
    bool isBumping = false;
    bool isSpent = false;
    bool wasHitThisFrame = false;
    float animTimer = 0;
    int frame = 0;

    std::string itemType;
    bool itemActive = false;
    float itemX, itemY;
    float spawnTimer = 0.0f;
    
    std::unique_ptr<Mushroom> releasedMushroom;
    Texture2D itemTexture;

public:
    PowerUpBlock(int x, int y, Texture2D sprites, Texture2D itemTex, std::string type = "coin");
    Rectangle getSensor();
    std::unique_ptr<Mushroom> takeMushroom(); 
    void update(Rectangle marioRec, float marioVelY, bool isBig) override; 
    bool justBumped() override;
    void draw() override;
    void drawDebug() override;
};

class PipeBlock : public Block {
private:
    int tilesWide;
    int tilesHigh;

public:
    PipeBlock(int x, int y, int width, int height, Texture2D sprites);
    
    Rectangle returnRec() override;
    
    void update(Rectangle marioRec, float marioVelY, bool isBig) override {} 
    
    void draw() override;
};

class ShinyBlock : public Block {
public:
    ShinyBlock(int x, int y, Texture2D sprites);
    void update(Rectangle marioRec, float marioVelY, bool isBig) override {} 
    void draw() override;
};

#endif
