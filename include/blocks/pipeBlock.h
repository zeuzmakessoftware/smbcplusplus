#ifndef BLOCKS_PIPE_BLOCK_H
#define BLOCKS_PIPE_BLOCK_H

#include "blocks/base.h"

enum class PipeOrientation {
    Vertical,
    HorizontalRight,
    HorizontalLeft
};

enum class WarpDestination {
    None,
    Level1Subarea,
    Level1Overworld,
    Level12Underground,
    Level12Subarea
};

class PipeBlock : public Block {
private:
    int tilesWide;
    int tilesHigh;
    PipeOrientation orientation;

public:
    PipeBlock(
        int x,
        int y,
        int width,
        int height,
        Texture2D sprites,
        const SceneType& scene = GetSceneType(SceneKind::Overworld),
        PipeOrientation orientation = PipeOrientation::Vertical
    );

    Rectangle returnRec() override;

    void update(Rectangle marioRec, float& marioVelY, bool isBig) override {}

    void draw() override;
    PipeOrientation getOrientation() const { return orientation; }
};

class WarpPipeBlock : public PipeBlock {
private:
    WarpDestination destination;
    Vector2 exitPosition;

public:
    WarpPipeBlock(
        int x,
        int y,
        int width,
        int height,
        Texture2D sprites,
        WarpDestination destination,
        Vector2 exitPosition,
        const SceneType& scene = GetSceneType(SceneKind::Overworld),
        PipeOrientation orientation = PipeOrientation::Vertical
    );

    WarpDestination getDestination() const { return destination; }
    Vector2 getExitPosition() const { return exitPosition; }
    bool canEnter(Rectangle marioRec, bool downPressed, bool rightPressed, bool leftPressed) const;
};

class PipeWallBlock : public Block {
private:
    int tilesHigh;

public:
    PipeWallBlock(int x, int y, int height, Texture2D sprites, const SceneType& scene = GetSceneType(SceneKind::Underground));
    Rectangle returnRec() override;
    void update(Rectangle marioRec, float& marioVelY, bool isBig) override {}
    void draw() override;
};

#endif
