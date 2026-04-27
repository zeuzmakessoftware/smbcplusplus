#ifndef BLOCKS_H
#define BLOCKS_H

#include <raylib.h>

#define TILE_SIZE 42

class Block {
protected:
    int rectXPos;
    int rectYPos;
    Texture2D spriteSheet;

public:
    Block(int x, int y, Texture2D sprites);
    virtual ~Block() {}

    virtual Rectangle returnRec();
    virtual void update(Rectangle marioRec, float marioVelY) = 0;
    virtual void draw() = 0;
};

class BrickBlock : public Block {
private:
    float offsetY = 0;
    float bumpTimer = 0;
    bool isBumping = false;

public:
    BrickBlock(int x, int y, Texture2D sprites);
    Rectangle getSensor();
    void update(Rectangle marioRec, float marioVelY) override;
    void draw() override;
};

class EmptyBlock : public Block {
public:
    EmptyBlock(int x, int y, Texture2D sprites);
    void update(Rectangle marioRec, float marioVelY) override {} // Does nothing
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

public:
    PowerUpBlock(int x, int y, Texture2D sprites);
    Rectangle getSensor();
    bool getIsSpent() const { return isSpent; }
    void update(Rectangle marioRec, float marioVelY) override;
    void draw() override;
};

#endif