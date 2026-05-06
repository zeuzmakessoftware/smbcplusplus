#ifndef LEVEL_DATA_H
#define LEVEL_DATA_H

#include <memory>
#include <string>
#include <vector>
#include <raylib.h>
#include "backgroundProp.h"
#include "blocks.h"
#include "castleFlagpole.h"
#include "drawTiledRect.h"
#include "goomba.h"
#include "koopa.h"
#include "mushroom.h"
#include "sceneType.h"

using LevelAreaId = std::string;

namespace LevelAreaIds {
    static const char* const Level11 = "level_1_1";
    static const char* const Level11Subarea = "level_1_1_subarea";
    static const char* const Level12Animation = "level_1_2_animation";
    static const char* const Level12Underground = "level_1_2_underground";
    static const char* const Level12Subarea = "level_1_2_subarea";
}

using LevelLoadFunction = void (*)(
    std::vector<std::unique_ptr<Block>>& blocks,
    std::vector<std::unique_ptr<Goomba>>& goombas,
    std::vector<std::unique_ptr<Koopa>>& koopas,
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

struct LevelAreaConfig {
    LevelAreaId id;
    LevelLoadFunction load;
    Vector2 defaultMarioStart;
    int scoreboardWorld;
    int scoreboardLevel;
    bool underground;
    bool level11;
    bool level12EntranceCutscene;
    float levelWidth;
};

const SceneType& GetLevel1Scene();
const std::vector<LevelAreaConfig>& GetLevelAreaConfigs();

#endif
