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

public:
    BrickBlock(int x, int y, Texture2D sprites);
    Rectangle getSensor();
    void update(Rectangle marioRec, float marioVelY, bool isBig) override; 
    void draw() override;
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
    void draw() override;
    void drawDebug() override;
};

#endif