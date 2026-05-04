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
#include "castleFlagpole.h"
#include "sceneType.h"

const SceneType& GetLevel1Scene();

void LoadLevel1(
    std::vector<std::unique_ptr<Block>>& blocks,
    std::vector<std::unique_ptr<Goomba>>& goombas,
    std::vector<Coin>& coins,
    std::vector<BackgroundProp>& levelProps,
    std::unique_ptr<CastleFlagpole>& castleFlagpole,
    bool& followCamera,
    Texture2D& spriteSheet,
    Texture2D& mushroomSheet,
    Texture2D& marioSheet,
    Texture2D& enemiesSheet,
    int tileSize
);

void LoadLevel1Subarea(
    std::vector<std::unique_ptr<Block>>& blocks,
    std::vector<std::unique_ptr<Goomba>>& goombas,
    std::vector<Coin>& coins,
    std::vector<BackgroundProp>& levelProps,
    std::unique_ptr<CastleFlagpole>& castleFlagpole,
    bool& followCamera,
    Texture2D& spriteSheet,
    Texture2D& mushroomSheet,
    Texture2D& marioSheet,
    Texture2D& enemiesSheet,
    int tileSize
);

#endif
