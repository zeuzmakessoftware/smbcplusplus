#include "levelDataLoaders.h"

void LoadLevel14(
    std::vector<std::unique_ptr<Block>>& blocks,
    std::vector<std::unique_ptr<Goomba>>& goombas,
    std::vector<std::unique_ptr<Koopa>>& koopas,
    std::vector<std::unique_ptr<PiranhaPlant>>& piranhaPlants,
    std::vector<FireBar>& fireBars,
    std::vector<std::unique_ptr<BowserFire>>& bowserFires,
    std::vector<Lift>& lifts,
    std::vector<Coin>& coins,
    std::vector<BackgroundProp>& levelProps,
    std::unique_ptr<CastleFlagpole>& castleFlagpole,
    bool& followCamera,
    Texture2D& spriteSheet,
    Texture2D& mushroomSheet,
    Texture2D& marioSheet,
    Texture2D& enemiesSheet,
    int tileSize
) {
    const SceneType& scene = GetSceneType(SceneKind::Castle);
    (void)goombas;
    (void)koopas;
    (void)piranhaPlants;
    (void)levelProps;
    (void)enemiesSheet;
    (void)tileSize;
    followCamera = true;

    //castleFlagpole = std::make_unique<CastleFlagpole>(152.0f, 600.0f, spriteSheet, mushroomSheet, marioSheet); no castle just bow wow
    fireBars.emplace_back(1281, 495, 6, mushroomSheet, true, 0.0f);
    fireBars.emplace_back(2079, 327, 6, mushroomSheet, true, 0.0f);
    fireBars.emplace_back(2541, 327, 6, mushroomSheet, true, 90.0f);
    fireBars.emplace_back(2835, 327, 6, mushroomSheet, true, 180.0f);
    fireBars.emplace_back(3213, 453, 6, mushroomSheet, true, 0.0f);
    fireBars.emplace_back(3549, 453, 6, mushroomSheet, true, 90.0f);
    fireBars.emplace_back(3717, 243, 6, mushroomSheet, true, 180.0f);
    bowserFires.push_back(std::make_unique<BowserFire>((102 * TILE_SIZE), (9 * TILE_SIZE), enemiesSheet));
    bowserFires.push_back(std::make_unique<BowserFire>((115 * TILE_SIZE), (10 * TILE_SIZE), enemiesSheet));
    bowserFires.push_back(std::make_unique<BowserFire>((126 * TILE_SIZE), (9 * TILE_SIZE), enemiesSheet));

    lifts.push_back(Lift::HorizontalBounce((133 * TILE_SIZE), (7 * TILE_SIZE) + 12, 126.0f, mushroomSheet, (133 * TILE_SIZE), (135 * TILE_SIZE), 68.0f, true));

    blocks.push_back(std::make_unique<DrawCastleTiledRect>(
        0, 474, 546, 210, spriteSheet, GetSceneType(SceneKind::Castle)
    ));
    blocks.push_back(std::make_unique<castleBrickBlock>((0 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<castleBrickBlock>((0 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<castleBrickBlock>((0 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<castleBrickBlock>((1 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<castleBrickBlock>((1 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<castleBrickBlock>((1 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<castleBrickBlock>((2 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<castleBrickBlock>((2 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<castleBrickBlock>((2 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<castleBrickBlock>((3 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<castleBrickBlock>((3 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<castleBrickBlock>((4 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<DrawCastleTiledRect>(
        630, 474, 462, 210, spriteSheet, GetSceneType(SceneKind::Castle)
    ));
    blocks.push_back(std::make_unique<DrawCastleTiledRect>(
        210, 138, 798, 126, spriteSheet, GetSceneType(SceneKind::Castle)
    ));
    blocks.push_back(std::make_unique<castleBrickBlock>((23 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<EmptyBlock>((23 * TILE_SIZE), (7 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<DrawCastleTiledRect>(
        1218, 516, 126, 168, spriteSheet, GetSceneType(SceneKind::Castle)
    ));
    blocks.push_back(std::make_unique<PowerUpBlock>((30 * TILE_SIZE), (7 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "mushroom", GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<castleBrickBlock>((29 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<castleBrickBlock>((31 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<EmptyBlock>((30 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<DrawCastleTiledRect>(
        1470, 432, 1554, 252, spriteSheet, GetSceneType(SceneKind::Castle)
    ));
    blocks.push_back(std::make_unique<DrawCastleTiledRect>(
        1008, 138, 546, 42, spriteSheet, GetSceneType(SceneKind::Castle)
    ));
    blocks.push_back(std::make_unique<DrawCastleTiledRect>(
        1554, 138, 1470, 168, spriteSheet, GetSceneType(SceneKind::Castle)
    ));
    blocks.push_back(std::make_unique<EmptyBlock>((37 * TILE_SIZE), (7 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<EmptyBlock>((49 * TILE_SIZE), (7 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<EmptyBlock>((60 * TILE_SIZE), (7 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<EmptyBlock>((67 * TILE_SIZE), (7 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<DrawCastleTiledRect>(
        3024, 474, 1344, 210, spriteSheet, GetSceneType(SceneKind::Castle)
    ));
    blocks.push_back(std::make_unique<EmptyBlock>((76 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<EmptyBlock>((84 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<DrawCastleTiledRect>(
        0, 138, 210, 42, spriteSheet, GetSceneType(SceneKind::Castle)
    ));
    blocks.push_back(std::make_unique<castleBrickBlock>((4 * TILE_SIZE), (4 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<DrawCastleTiledRect>(
        3024, 138, 1050, 42, spriteSheet, GetSceneType(SceneKind::Castle)
    ));
    blocks.push_back(std::make_unique<castleBrickBlock>((80 * TILE_SIZE), (4 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<EmptyBlock>((80 * TILE_SIZE), (5 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<EmptyBlock>((92 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<castleBrickBlock>((88 * TILE_SIZE), (4 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<EmptyBlock>((88 * TILE_SIZE), (5 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<DrawCastleTiledRect>(
        4074, 138, 294, 126, spriteSheet, GetSceneType(SceneKind::Castle)
    ));
    blocks.push_back(std::make_unique<DrawCastleTiledRect>(
        4368, 600, 966, 84, spriteSheet, GetSceneType(SceneKind::Castle)
    ));
    blocks.push_back(std::make_unique<DrawCastleTiledRect>(
        4368, 138, 1554, 42, spriteSheet, GetSceneType(SceneKind::Castle)
    ));
    blocks.push_back(std::make_unique<DrawCastleTiledRect>(
        4872, 474, 168, 126, spriteSheet, GetSceneType(SceneKind::Castle)
    ));
    blocks.push_back(std::make_unique<DrawCastleTiledRect>(
        5124, 474, 210, 126, spriteSheet, GetSceneType(SceneKind::Castle)
    ));
    blocks.push_back(std::make_unique<DrawCastleTiledRect>(
        5124, 180, 210, 84, spriteSheet, GetSceneType(SceneKind::Castle)
    ));
    blocks.push_back(std::make_unique<DrawCastleTiledRect>(
        5880, 432, 126, 252, spriteSheet, GetSceneType(SceneKind::Castle)
    ));
    blocks.push_back(std::make_unique<DrawCastleTiledRect>(
        5922, 138, 84, 168, spriteSheet, GetSceneType(SceneKind::Castle)
    ));
    blocks.push_back(std::make_unique<DrawCastleTiledRect>(
        6006, 600, 1050, 84, spriteSheet, GetSceneType(SceneKind::Castle)
    ));
    blocks.push_back(std::make_unique<DrawCastleTiledRect>(
        6006, 138, 1050, 42, spriteSheet, GetSceneType(SceneKind::Castle)
    ));
    blocks.push_back(std::make_unique<lavaTopBlock>((13 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaTopBlock>((14 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaBackgroundBlock>((13 * TILE_SIZE), (14 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaBackgroundBlock>((14 * TILE_SIZE), (14 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaBackgroundBlock>((13 * TILE_SIZE), (15 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaBackgroundBlock>((14 * TILE_SIZE), (15 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaTopBlock>((26 * TILE_SIZE), (14 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaTopBlock>((27 * TILE_SIZE), (14 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaTopBlock>((28 * TILE_SIZE), (14 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaBackgroundBlock>((26 * TILE_SIZE), (15 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaBackgroundBlock>((27 * TILE_SIZE), (15 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaBackgroundBlock>((28 * TILE_SIZE), (15 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaTopBlock>((32 * TILE_SIZE), (14 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaTopBlock>((33 * TILE_SIZE), (14 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaTopBlock>((34 * TILE_SIZE), (14 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaBackgroundBlock>((32 * TILE_SIZE), (15 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaBackgroundBlock>((33 * TILE_SIZE), (15 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaBackgroundBlock>((34 * TILE_SIZE), (15 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaTopBlock>((127 * TILE_SIZE), (14 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaTopBlock>((128 * TILE_SIZE), (14 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaTopBlock>((129 * TILE_SIZE), (14 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaTopBlock>((130 * TILE_SIZE), (14 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaTopBlock>((131 * TILE_SIZE), (14 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaTopBlock>((132 * TILE_SIZE), (14 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaTopBlock>((133 * TILE_SIZE), (14 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaTopBlock>((134 * TILE_SIZE), (14 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaTopBlock>((135 * TILE_SIZE), (14 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaTopBlock>((136 * TILE_SIZE), (14 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaTopBlock>((137 * TILE_SIZE), (14 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaTopBlock>((138 * TILE_SIZE), (14 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaTopBlock>((139 * TILE_SIZE), (14 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaBackgroundBlock>((127 * TILE_SIZE), (15 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaBackgroundBlock>((128 * TILE_SIZE), (15 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaBackgroundBlock>((129 * TILE_SIZE), (15 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaBackgroundBlock>((130 * TILE_SIZE), (15 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaBackgroundBlock>((131 * TILE_SIZE), (15 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaBackgroundBlock>((132 * TILE_SIZE), (15 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaBackgroundBlock>((133 * TILE_SIZE), (15 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaBackgroundBlock>((134 * TILE_SIZE), (15 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaBackgroundBlock>((135 * TILE_SIZE), (15 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaBackgroundBlock>((136 * TILE_SIZE), (15 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaBackgroundBlock>((137 * TILE_SIZE), (15 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaBackgroundBlock>((138 * TILE_SIZE), (15 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<lavaBackgroundBlock>((139 * TILE_SIZE), (15 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<BridgeBlock>((127 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, 0, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<BridgeBlock>((128 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, 1, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<BridgeBlock>((129 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, 2, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<BridgeBlock>((130 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, 3, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<BridgeBlock>((131 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, 4, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<BridgeBlock>((132 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, 5, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<BridgeBlock>((133 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, 6, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<BridgeBlock>((134 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, 7, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<BridgeBlock>((135 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, 8, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<BridgeBlock>((136 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, 9, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<BridgeBlock>((137 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, 10, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<BridgeBlock>((138 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, 11, GetSceneType(SceneKind::Castle)));
    blocks.push_back(std::make_unique<BridgeBlock>((139 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, 12, GetSceneType(SceneKind::Castle)));
}
