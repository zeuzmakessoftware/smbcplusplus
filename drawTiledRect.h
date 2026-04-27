#ifndef DRAWTILEDRECT_H
#define DRAWTILEDRECT_H

#include <raylib.h>

#define TILE_SIZE 42 // Shared constant

class DrawTiledRect {
    private:
        int rectXPos;
        int rectYPos;
        int rectWidth;
        int rectHeight;
        int tileWidth;
        int tileHeight;
        Texture2D spriteSheet;
        Rectangle textureLocation;
    public:
        DrawTiledRect(int rectX, int rectY, int rectW, int rectH, Texture2D sprites, 
            Rectangle textureLoc = {0, 0, 0, 0}, int tileW = TILE_SIZE, int tileH = TILE_SIZE);

        Rectangle returnRec();

        void draw();
};

#endif