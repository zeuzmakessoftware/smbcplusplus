#include "levelDataLoaders.h"

namespace {
constexpr SceneKind LEVEL1_SCENE_KIND = SceneKind::Overworld;
}

const SceneType& GetLevel1Scene() {
    return GetSceneType(LEVEL1_SCENE_KIND);
}

const std::vector<LevelAreaConfig>& GetLevelAreaConfigs() {
    // Register new areas here after adding the loader function above.
    // Pipes can warp to the registered id directly.
    static const std::vector<LevelAreaConfig> configs = {
        {
            LevelAreaIds::Level11,
            LoadLevel1,
            {100.0f, 0.0f},
            1,
            1,
            false,
            true,
            false,
            LevelAreaIds::Level12Animation,
            -1.0f
        },
        {
            LevelAreaIds::Level11Subarea,
            LoadLevel1Subarea,
            {(2.0f * TILE_SIZE) + 4.0f, (2.0f * TILE_SIZE) + 4.0f},
            1,
            1,
            true,
            false,
            false,
            "",
            32.0f * TILE_SIZE
        },
        {
            LevelAreaIds::Level12Animation,
            LoadLevel12EntranceCutscene,
            {126.0f, (13.0f * TILE_SIZE) + 12.0f},
            1,
            2,
            false,
            false,
            true,
            "",
            -1.0f
        },
        {
            LevelAreaIds::Level12Underground,
            LoadLevel12UndergroundStart,
            {(2.0f * TILE_SIZE) + 4.0f, (2.0f * TILE_SIZE) + 4.0f},
            1,
            2,
            true,
            false,
            false,
            "",
            7140.0f
        },
        {
            LevelAreaIds::Level12Subarea,
            LoadLevel12Subarea,
            {(2.0f * TILE_SIZE) + 4.0f, (2.0f * TILE_SIZE) + 4.0f},
            1,
            2,
            true,
            false,
            false,
            "",
            32.0f * TILE_SIZE
        },
        {
            LevelAreaIds::Level12Final,
            LoadLevel12Final,
            {(2.0f * TILE_SIZE) + 4.0f, (2.0f * TILE_SIZE) + 4.0f},
            1,
            2,
            false,
            true,
            false,
            LevelAreaIds::Level13,
            32.0f * TILE_SIZE
        },
        {
            LevelAreaIds::Level13,
            LoadLevel13,
            {(2.0f * TILE_SIZE) + 4.0f, (2.0f * TILE_SIZE) + 4.0f},
            1,
            3,
            false,
            true,
            false,
            LevelAreaIds::Level14,
            302.0f * TILE_SIZE
        },
        {
            LevelAreaIds::Level14,
            LoadLevel14,
            {(2.0f * TILE_SIZE) + 4.0f, (6.0f * TILE_SIZE) + 4.0f},
            1,
            4,
            true,
            false,
            false,
            LevelAreaIds::Level11,
            302.0f * TILE_SIZE
        }
    };

    return configs;
}
