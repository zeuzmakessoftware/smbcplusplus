#include "levelDataLoaders.h"

void LoadLevel12EntranceCutscene(
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
    const SceneType& scene = GetSceneType(SceneKind::Overworld);
    (void)goombas;
    (void)koopas;
    (void)piranhaPlants;
    (void)coins;
    (void)enemiesSheet;
    (void)tileSize;
    followCamera = false;

    castleFlagpole = std::make_unique<CastleFlagpole>(5000.0f, 600.0f, spriteSheet, mushroomSheet, marioSheet);

    levelProps.push_back(BackgroundProp(168, 180, spriteSheet, MEDIUM_CLOUD_LAYOUT));
    levelProps.push_back(BackgroundProp(378, 348, spriteSheet, CLOUD_LAYOUT));
    levelProps.push_back(BackgroundProp(798, 138, spriteSheet, MEDIUM_CLOUD_LAYOUT));

    blocks.push_back(std::make_unique<DrawTiledRect>(
        0, 600, 992, 80, spriteSheet, scene.groundBlock, TILE_SIZE, TILE_SIZE, scene
    ));
    blocks.push_back(std::make_unique<WarpPipeBlock>(
        (10 * TILE_SIZE), (12 * TILE_SIZE) + 12, 2, 2, spriteSheet,
        LevelAreaIds::Level12Underground, (Vector2){ (2.0f * TILE_SIZE) + 4.0f, (2.0f * TILE_SIZE) + 4.0f },
        scene, PipeOrientation::HorizontalRight
    ));
    blocks.push_back(std::make_unique<PipeBlock>((12 * TILE_SIZE), (10 * TILE_SIZE) + 12, 2, 4, spriteSheet, scene));
    blocks.push_back(std::make_unique<PipeWallBlock>((12 * TILE_SIZE), (12 * TILE_SIZE) + 12, 2, spriteSheet, scene));
}

void LoadLevel12UndergroundStart(
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
    const SceneType& scene = GetSceneType(SceneKind::Underground);
    (void)koopas;
    (void)coins;
    (void)levelProps;
    (void)tileSize;
    followCamera = true;

    castleFlagpole = std::make_unique<CastleFlagpole>(5000.0f, 600.0f, spriteSheet, mushroomSheet, marioSheet);

    lifts.push_back(Lift::VerticalWrap(139.0f * TILE_SIZE, 650.0f, 132.0f, mushroomSheet, TILE_SIZE, 680.0f, 72.0f, true));
    lifts.push_back(Lift::VerticalWrap(139.0f * TILE_SIZE, 650.0f - (TILE_SIZE * 7), 132.0f, mushroomSheet, TILE_SIZE, 680.0f, 72.0f, true));
    lifts.push_back(Lift::VerticalWrap(155.0f * TILE_SIZE, 650.0f, 132.0f, mushroomSheet, TILE_SIZE, 680.0f, 72.0f, false));
    lifts.push_back(Lift::VerticalWrap(155.0f * TILE_SIZE, 650.0f - (TILE_SIZE * 7), 132.0f, mushroomSheet, TILE_SIZE, 680.0f, 72.0f, false));

    goombas.push_back(std::make_unique<Goomba>((16 * TILE_SIZE), (13 * TILE_SIZE), enemiesSheet, GetSceneType(SceneKind::Underground)));
    goombas.push_back(std::make_unique<Goomba>((17 * TILE_SIZE), (12 * TILE_SIZE), enemiesSheet, GetSceneType(SceneKind::Underground)));
    goombas.push_back(std::make_unique<Goomba>((29 * TILE_SIZE), (13 * TILE_SIZE), enemiesSheet, GetSceneType(SceneKind::Underground)));
    coins.emplace_back((float)(40 * TILE_SIZE), (float)(9 * TILE_SIZE) + 12, spriteSheet), GetSceneType(SceneKind::Underground);
    coins.emplace_back((float)(45 * TILE_SIZE), (float)(9 * TILE_SIZE) + 12, spriteSheet), GetSceneType(SceneKind::Underground);
    coins.emplace_back((float)(41 * TILE_SIZE), (float)(6 * TILE_SIZE) + 12, spriteSheet), GetSceneType(SceneKind::Underground);
    coins.emplace_back((float)(42 * TILE_SIZE), (float)(6 * TILE_SIZE) + 12, spriteSheet), GetSceneType(SceneKind::Underground);
    coins.emplace_back((float)(43 * TILE_SIZE), (float)(6 * TILE_SIZE) + 12, spriteSheet), GetSceneType(SceneKind::Underground);
    coins.emplace_back((float)(44 * TILE_SIZE), (float)(6 * TILE_SIZE) + 12, spriteSheet), GetSceneType(SceneKind::Underground);
    koopas.push_back(std::make_unique<Koopa>((44 * TILE_SIZE), 537, enemiesSheet, GetSceneType(SceneKind::Underground)));
    koopas.push_back(std::make_unique<Koopa>((46 * TILE_SIZE), 537, enemiesSheet, GetSceneType(SceneKind::Underground)));
    coins.emplace_back((float)(58 * TILE_SIZE), (float)(9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground));
    coins.emplace_back((float)(59 * TILE_SIZE), (float)(9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground));
    coins.emplace_back((float)(60 * TILE_SIZE), (float)(9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground));
    coins.emplace_back((float)(61 * TILE_SIZE), (float)(9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground));
    coins.emplace_back((float)(68 * TILE_SIZE), (float)(9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground));
    coins.emplace_back((float)(83 * TILE_SIZE), (float)(6 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground));
    coins.emplace_back((float)(84 * TILE_SIZE), (float)(6 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground));
    coins.emplace_back((float)(85 * TILE_SIZE), (float)(6 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground));
    coins.emplace_back((float)(86 * TILE_SIZE), (float)(6 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground));
    coins.emplace_back((float)(87 * TILE_SIZE), (float)(6 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground));
    coins.emplace_back((float)(88 * TILE_SIZE), (float)(6 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground));
    goombas.push_back(std::make_unique<Goomba>((101 * TILE_SIZE), (14 * TILE_SIZE), enemiesSheet, GetSceneType(SceneKind::Underground)));
    goombas.push_back(std::make_unique<Goomba>((99 * TILE_SIZE), (14 * TILE_SIZE), enemiesSheet, GetSceneType(SceneKind::Underground)));
    goombas.push_back(std::make_unique<Goomba>((97 * TILE_SIZE), (14 * TILE_SIZE), enemiesSheet, GetSceneType(SceneKind::Underground)));
    goombas.push_back(std::make_unique<Goomba>((112 * TILE_SIZE), (14 * TILE_SIZE), enemiesSheet, GetSceneType(SceneKind::Underground)));
    koopas.push_back(std::make_unique<Koopa>((146 * TILE_SIZE), 537, enemiesSheet, GetSceneType(SceneKind::Underground)));
    goombas.push_back(std::make_unique<Goomba>((134 * TILE_SIZE), (10 * TILE_SIZE), enemiesSheet, GetSceneType(SceneKind::Underground)));
    goombas.push_back(std::make_unique<Goomba>((135 * TILE_SIZE), (9 * TILE_SIZE), enemiesSheet, GetSceneType(SceneKind::Underground)));
    koopas.push_back(std::make_unique<Koopa>((59 * TILE_SIZE), 537, enemiesSheet, GetSceneType(SceneKind::Underground)));
    goombas.push_back(std::make_unique<Goomba>((62 * TILE_SIZE), (14 * TILE_SIZE), enemiesSheet, GetSceneType(SceneKind::Underground)));
    goombas.push_back(std::make_unique<Goomba>((64 * TILE_SIZE), (14 * TILE_SIZE), enemiesSheet, GetSceneType(SceneKind::Underground)));
    goombas.push_back(std::make_unique<Goomba>((73 * TILE_SIZE), (6 * TILE_SIZE), enemiesSheet, GetSceneType(SceneKind::Underground)));
    goombas.push_back(std::make_unique<Goomba>((76 * TILE_SIZE), (10 * TILE_SIZE), enemiesSheet, GetSceneType(SceneKind::Underground)));
    goombas.push_back(std::make_unique<Goomba>((78 * TILE_SIZE), (10 * TILE_SIZE), enemiesSheet, GetSceneType(SceneKind::Underground)));

    blocks.push_back(std::make_unique<DrawTiledRect>(
        0, 600, 3344, 80, spriteSheet, GetSceneType(SceneKind::Underground).groundBlock, TILE_SIZE, TILE_SIZE, GetSceneType(SceneKind::Underground)
    ));
    blocks.push_back(std::make_unique<PowerUpBlock>((10 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "mushroom", GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<PowerUpBlock>((11 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "coin", GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<PowerUpBlock>((12 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "coin", GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<PowerUpBlock>((13 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "coin", GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<PowerUpBlock>((14 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "coin", GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((17 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((19 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((19 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((21 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((21 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((21 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((23 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((23 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((23 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((23 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((25 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((25 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((25 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((25 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((27 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((27 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((27 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((29 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((0 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((0 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((0 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((0 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((0 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((0 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((0 * TILE_SIZE), (7 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((0 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((31 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((31 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((31 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((33 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((33 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((39 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((39 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((39 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((40 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((41 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((41 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((41 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((42 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((43 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((44 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((44 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((44 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((45 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((46 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((46 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((46 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((0 * TILE_SIZE), (5 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((0 * TILE_SIZE), (4 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((0 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((6 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((7 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((8 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((9 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((10 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((11 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((12 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((13 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((14 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((15 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((16 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((17 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((18 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((19 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((20 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((21 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((22 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((23 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((24 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((25 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((26 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((27 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((28 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((30 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((29 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((31 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((32 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((33 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((34 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((35 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((36 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((37 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((38 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((39 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((40 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((41 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((42 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((43 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((44 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((45 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((46 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((47 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((52 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((52 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((52 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((52 * TILE_SIZE), (7 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((52 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((53 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((53 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((53 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((53 * TILE_SIZE), (7 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((53 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((54 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((54 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((54 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((54 * TILE_SIZE), (5 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((54 * TILE_SIZE), (4 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((48 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((49 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((50 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((51 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((52 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((53 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((54 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((55 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((55 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((55 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((55 * TILE_SIZE), (5 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((55 * TILE_SIZE), (4 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((55 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((58 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((59 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((61 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((60 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((57 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((56 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((58 * TILE_SIZE), (5 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((58 * TILE_SIZE), (4 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((58 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((59 * TILE_SIZE), (5 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((59 * TILE_SIZE), (4 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((59 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((60 * TILE_SIZE), (5 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((60 * TILE_SIZE), (4 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((60 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((61 * TILE_SIZE), (5 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((61 * TILE_SIZE), (4 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((61 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((62 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((62 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((62 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((62 * TILE_SIZE), (7 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((62 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((62 * TILE_SIZE), (5 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((62 * TILE_SIZE), (4 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((62 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((63 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((63 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((63 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((63 * TILE_SIZE), (7 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((63 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((63 * TILE_SIZE), (5 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((63 * TILE_SIZE), (4 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((63 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((66 * TILE_SIZE), (5 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((66 * TILE_SIZE), (4 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((66 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((65 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((64 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((67 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((67 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((67 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((67 * TILE_SIZE), (7 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((67 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((67 * TILE_SIZE), (5 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((67 * TILE_SIZE), (4 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((67 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((68 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((68 * TILE_SIZE), (5 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((68 * TILE_SIZE), (4 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((68 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((69 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((69 * TILE_SIZE), (5 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((69 * TILE_SIZE), (4 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((69 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((69 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((72 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((72 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((72 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((72 * TILE_SIZE), (7 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((72 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((70 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((71 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((72 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((73 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((73 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((73 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((73 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((73 * TILE_SIZE), (7 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((73 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((74 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((75 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((76 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((76 * TILE_SIZE), (5 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((76 * TILE_SIZE), (4 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((76 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((77 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((77 * TILE_SIZE), (5 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((77 * TILE_SIZE), (4 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((77 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((78 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((78 * TILE_SIZE), (5 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((78 * TILE_SIZE), (4 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((78 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((79 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((79 * TILE_SIZE), (5 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((79 * TILE_SIZE), (4 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((79 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<DrawTiledRect>(
        3444, 600, 1554, 84, spriteSheet, GetSceneType(SceneKind::Underground).groundBlock, TILE_SIZE, TILE_SIZE, GetSceneType(SceneKind::Underground)
    ));
    blocks.push_back(std::make_unique<BrickBlock>((83 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((83 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((84 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((84 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((85 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((85 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((86 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((86 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((87 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((87 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((88 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((88 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((80 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((81 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((82 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((83 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((84 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((85 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((86 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((87 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<PowerUpBlock>((88 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "1up", GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((89 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((90 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((91 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((92 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((93 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((94 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((95 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((96 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((97 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((98 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((99 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((100 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<WarpPipeBlock>(
        (102 * TILE_SIZE), (11 * TILE_SIZE) + 12, 2, 3, spriteSheet,
        LevelAreaIds::Level12Subarea, (Vector2){ (2.0f * TILE_SIZE) + 4.0f, (2.0f * TILE_SIZE) + 4.0f },
        GetSceneType(SceneKind::Underground)
    ));
    piranhaPlants.push_back(std::make_unique<PiranhaPlant>((102 * TILE_SIZE), (11 * TILE_SIZE) + 12, 2 * TILE_SIZE, enemiesSheet));
    piranhaPlants.push_back(std::make_unique<PiranhaPlant>((108 * TILE_SIZE), (10 * TILE_SIZE) + 12, 2 * TILE_SIZE, enemiesSheet));
    piranhaPlants.push_back(std::make_unique<PiranhaPlant>((114 * TILE_SIZE), (12 * TILE_SIZE) + 12, 2 * TILE_SIZE, enemiesSheet));
    blocks.push_back(std::make_unique<PipeBlock>((108 * TILE_SIZE), (10 * TILE_SIZE) + 12, 2, 4, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<PipeBlock>((114 * TILE_SIZE), (12 * TILE_SIZE) + 12, 2, 2, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<DrawTiledRect>(
        5082, 600, 84, 84, spriteSheet, GetSceneType(SceneKind::Underground).groundBlock, TILE_SIZE, TILE_SIZE, GetSceneType(SceneKind::Underground)
    ));
    blocks.push_back(std::make_unique<DrawTiledRect>(
        5250, 600, 504, 84, spriteSheet, GetSceneType(SceneKind::Underground).groundBlock, TILE_SIZE, TILE_SIZE, GetSceneType(SceneKind::Underground)
    ));
    blocks.push_back(std::make_unique<BrickBlock>((121 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((121 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((121 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((122 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((122 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((122 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((132 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((133 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((133 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((134 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((134 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((134 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((135 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((135 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((135 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((135 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((136 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((136 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((136 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<ShinyBlock>((136 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((101 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((102 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((103 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((104 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((105 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((106 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((107 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((108 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((109 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((110 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((111 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((112 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((113 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((114 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((115 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((116 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((117 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((118 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((119 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((120 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((121 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((122 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((123 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((124 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((125 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((126 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((127 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((128 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((129 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((130 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((131 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((132 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((133 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((134 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((135 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((136 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<DrawTiledRect>(
        6090, 600, 336, 84, spriteSheet, GetSceneType(SceneKind::Underground).groundBlock, TILE_SIZE, TILE_SIZE, GetSceneType(SceneKind::Underground)
    ));
    blocks.push_back(std::make_unique<BrickBlock>((145 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((146 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((147 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((148 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((149 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((150 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<DrawTiledRect>(
        6762, 600, 378, 84, spriteSheet, GetSceneType(SceneKind::Underground).groundBlock, TILE_SIZE, TILE_SIZE, GetSceneType(SceneKind::Underground)
    ));
    blocks.push_back(std::make_unique<BrickBlock>((161 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((161 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((161 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((162 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((162 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((162 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((163 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((163 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((163 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((164 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((164 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((164 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((165 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((165 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((165 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((166 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((166 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((166 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((167 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((167 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((167 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((168 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((168 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((168 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<WarpPipeBlock>(
        (167 * TILE_SIZE), (9 * TILE_SIZE) + 12, 2, 2, spriteSheet,
        LevelAreaIds::Level12Final, (Vector2){ (2.0f * TILE_SIZE) + 4.0f, (2.0f * TILE_SIZE) + 4.0f },
        GetSceneType(SceneKind::Underground), PipeOrientation::HorizontalRight
    ));
    blocks.push_back(std::make_unique<BrickBlock>((162 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((163 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((164 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((165 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((166 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((167 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((168 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<PipeWallBlock>((169 * TILE_SIZE), (3 * TILE_SIZE) + 12, 8, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((169 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((169 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((169 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
}

void LoadLevel12Subarea(
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
    const SceneType& scene = GetSceneType(SceneKind::Underground);
    (void)goombas;
    (void)koopas;
    (void)piranhaPlants;
    (void)levelProps;
    (void)enemiesSheet;
    (void)tileSize;
    followCamera = false;
    
    castleFlagpole = std::make_unique<CastleFlagpole>(5000.0f, 600.0f, spriteSheet, mushroomSheet, marioSheet);

    coins.emplace_back((float)(3 * TILE_SIZE), (float)(13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground));
    coins.emplace_back((float)(4 * TILE_SIZE), (float)(13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground));
    coins.emplace_back((float)(5 * TILE_SIZE), (float)(13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground));
    coins.emplace_back((float)(6 * TILE_SIZE), (float)(13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground));
    coins.emplace_back((float)(7 * TILE_SIZE), (float)(13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground));
    coins.emplace_back((float)(8 * TILE_SIZE), (float)(13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground));
    coins.emplace_back((float)(9 * TILE_SIZE), (float)(13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground));
    coins.emplace_back((float)(10 * TILE_SIZE), (float)(13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground));
    coins.emplace_back((float)(11 * TILE_SIZE), (float)(13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground));
    coins.emplace_back((float)(4 * TILE_SIZE), (float)(9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground));
    coins.emplace_back((float)(5 * TILE_SIZE), (float)(9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground));
    coins.emplace_back((float)(6 * TILE_SIZE), (float)(9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground));
    coins.emplace_back((float)(7 * TILE_SIZE), (float)(9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground));
    coins.emplace_back((float)(8 * TILE_SIZE), (float)(9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground));
    coins.emplace_back((float)(9 * TILE_SIZE), (float)(9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground));
    coins.emplace_back((float)(10 * TILE_SIZE), (float)(9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground));
    coins.emplace_back((float)(11 * TILE_SIZE), (float)(9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground));

    blocks.push_back(std::make_unique<DrawTiledRect>(
        0, 600, 672, 84, spriteSheet, GetSceneType(SceneKind::Underground).groundBlock, TILE_SIZE, TILE_SIZE, GetSceneType(SceneKind::Underground)
    ));
    blocks.push_back(std::make_unique<BrickBlock>((0 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((0 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((0 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((0 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((0 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((0 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((0 * TILE_SIZE), (7 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((0 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((0 * TILE_SIZE), (5 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((0 * TILE_SIZE), (4 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((0 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<WarpPipeBlock>(
        (13 * TILE_SIZE), (12 * TILE_SIZE) + 12, 4, 2, spriteSheet,
        LevelAreaIds::Level12Underground, (Vector2){ (114.0f * TILE_SIZE) + 4.0f, (11.0f * TILE_SIZE) + 4.0f },
        GetSceneType(SceneKind::Underground), PipeOrientation::HorizontalRight
    ));
    blocks.push_back(std::make_unique<PipeWallBlock>((15 * TILE_SIZE), (3 * TILE_SIZE) + 12, 11, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((3 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((4 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((5 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((6 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((7 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((8 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((9 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((10 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((11 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<CoinBrickBlock>((12 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((13 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((14 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((13 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((14 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((13 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((14 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((13 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((14 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((13 * TILE_SIZE), (7 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((14 * TILE_SIZE), (7 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((3 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((4 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((5 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((6 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((7 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((8 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((9 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((10 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((11 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((12 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((13 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((14 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((3 * TILE_SIZE), (5 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((4 * TILE_SIZE), (5 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((5 * TILE_SIZE), (5 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((6 * TILE_SIZE), (5 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((7 * TILE_SIZE), (5 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((8 * TILE_SIZE), (5 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((9 * TILE_SIZE), (5 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((10 * TILE_SIZE), (5 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((11 * TILE_SIZE), (5 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((12 * TILE_SIZE), (5 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((13 * TILE_SIZE), (5 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((14 * TILE_SIZE), (5 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((3 * TILE_SIZE), (4 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((4 * TILE_SIZE), (4 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((5 * TILE_SIZE), (4 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((6 * TILE_SIZE), (4 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((7 * TILE_SIZE), (4 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((8 * TILE_SIZE), (4 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((9 * TILE_SIZE), (4 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((10 * TILE_SIZE), (4 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((11 * TILE_SIZE), (4 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((12 * TILE_SIZE), (4 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((13 * TILE_SIZE), (4 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((14 * TILE_SIZE), (4 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((3 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((4 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((5 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((6 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((7 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((8 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((9 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((10 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((11 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((12 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((13 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((14 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
}

void LoadLevel12Final(
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
    const SceneType& scene = GetSceneType(SceneKind::Underground);
    (void)goombas;
    (void)koopas;
    (void)piranhaPlants;
    (void)levelProps;
    (void)enemiesSheet;
    (void)tileSize;
    followCamera = true;

    castleFlagpole = std::make_unique<CastleFlagpole>(22.0f, 600.0f, spriteSheet, mushroomSheet, marioSheet);

    levelProps.push_back(BackgroundProp(672, 474, spriteSheet, HILL_LAYOUT));
    levelProps.push_back(BackgroundProp(1218, 558, spriteSheet, TINY_GRASS_LAYOUT));
    levelProps.push_back(BackgroundProp(1344, 516, spriteSheet, SMALL_HILL_LAYOUT));
    levelProps.push_back(BackgroundProp(1638, 558, spriteSheet, TINY_GRASS_LAYOUT));
    levelProps.push_back(BackgroundProp(168, 96, spriteSheet, MEDIUM_CLOUD_LAYOUT));
    levelProps.push_back(BackgroundProp(1008, 138, spriteSheet, CLOUD_LAYOUT));
    levelProps.push_back(BackgroundProp(1470, 96, spriteSheet, CLOUD_LAYOUT));


    blocks.push_back(std::make_unique<DrawTiledRect>(
        0, 600, 2000, 80, spriteSheet, GetSceneType(SceneKind::Overworld).groundBlock, TILE_SIZE, TILE_SIZE, GetSceneType(SceneKind::Overworld)
    ));
    blocks.push_back(std::make_unique<PipeBlock>((3 * TILE_SIZE), (12 * TILE_SIZE) + 12, 2, 2, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((5 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((6 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((6 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((7 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((7 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((7 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((8 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((8 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((8 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((8 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((9 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((9 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((9 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((9 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((9 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((10 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((10 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((10 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((10 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((10 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((10 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((11 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((11 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((11 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((11 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((11 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((11 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((11 * TILE_SIZE), (7 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((12 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((12 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((12 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((12 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((12 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((12 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((12 * TILE_SIZE), (7 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((12 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((13 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((13 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((13 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((13 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((13 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((13 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((13 * TILE_SIZE), (7 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
    blocks.push_back(std::make_unique<ShinyBlock>((13 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Overworld)));
}

