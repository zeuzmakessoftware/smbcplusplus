#ifndef LEVEL_DATA_H
#define LEVEL_DATA_H

#include <vector>
#include <memory>
#include <raylib.h>
#include "backgroundProp.h"
#include "blocks.h"
#include "goomba.h"
#include "mushroom.h"
#include "drawTiledRect.h"

void LoadLevel1(
    std::vector<std::unique_ptr<Block>>& blocks,
    std::vector<std::unique_ptr<Goomba>>& goombas,
    std::vector<BackgroundProp>& levelProps,
    Texture2D& spriteSheet,
    Texture2D& mushroomSheet,
    Texture2D& enemiesSheet,
    int tileSize
);

#endif