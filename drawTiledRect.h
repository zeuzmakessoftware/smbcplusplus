#ifndef DRAWTILEDRECT_H
#define DRAWTILEDRECT_H

#include <raylib.h>
#include "blocks.h"

class DrawTiledRect : public Block {
    private:
        int rectWidth;
        int rectHeight;
        int tileWidth;
        int tileHeight;
        Rectangle textureLocation;
    public:
        DrawTiledRect(int rectX, int rectY, int rectW, int rectH, Texture2D sprites, 
            Rectangle textureLoc = {0, 0, 0, 0}, int tileW = TILE_SIZE, int tileH = TILE_SIZE);

        Rectangle returnRec() override;
        void update(Rectangle marioRec, float& marioVelY, bool isBig) override {}
        void draw() override;
};

#endif
