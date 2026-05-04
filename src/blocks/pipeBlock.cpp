#include "blocks/pipeBlock.h"

#include <cmath>

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

PipeWallBlock::PipeWallBlock(int x, int y, int height, Texture2D sprites, const SceneType& scene)
    : Block(x, y, sprites, scene), tilesHigh(height) {}

Rectangle PipeWallBlock::returnRec() {
    return { (float)rectXPos, (float)rectYPos, (float)TILE_SIZE, (float)tilesHigh * TILE_SIZE };
}

void PipeWallBlock::draw() {
    for (int j = 0; j < tilesHigh; j++) {
        Rectangle src = (Rectangle){ 119.0f, 213.0f, 16.0f, 16.0f };

        if (j == tilesHigh - 2) {
            src = (Rectangle){ 119.0f, 230.0f, 16.0f, 16.0f };
        } else if (j == tilesHigh - 1) {
            src = (Rectangle){ 119.0f, 247.0f, 16.0f, 16.0f };
        }

        DrawTexturePro(
            spriteSheet,
            src,
            (Rectangle){
                (float)rectXPos,
                (float)rectYPos + (j * TILE_SIZE),
                (float)TILE_SIZE,
                (float)TILE_SIZE
            },
            (Vector2){ 0, 0 },
            0.0f,
            WHITE
        );
    }
}
