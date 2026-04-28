#include "drawTiledRect.h"

DrawTiledRect::DrawTiledRect(int rectX, int rectY, int rectW, int rectH, Texture2D sprites, 
    Rectangle textureLoc, int tileW, int tileH) 
    : Block(rectX, rectY, sprites),
      rectWidth(rectW), rectHeight(rectH), 
      textureLocation(textureLoc), tileWidth(tileW), tileHeight(tileH)
    {}

Rectangle DrawTiledRect::returnRec() {
    return {(float)rectXPos, (float)rectYPos, (float)rectWidth, (float)rectHeight};
}

void DrawTiledRect::draw() {
    if (textureLocation.width == 0) {
        for (int i = rectYPos; i < rectYPos + rectHeight; i += tileHeight) {
            for (int j = rectXPos; j < rectXPos + rectWidth; j += tileWidth) {
                DrawRectangleGradientV(j, i, tileWidth, tileHeight, RED, GOLD);
            }
        }
    }
    else {
        for (float i = (float)rectYPos; i < (float)rectYPos + rectHeight; i += tileHeight) {
            for (float j = (float)rectXPos; j < (float)rectXPos + rectWidth; j += tileWidth) {
                Rectangle destRec = { j, i, (float)tileWidth, (float)tileHeight };
                DrawTexturePro(spriteSheet, textureLocation, destRec, {0, 0}, 0.0f, WHITE);
            }
        }
    }
}