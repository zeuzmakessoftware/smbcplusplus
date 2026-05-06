#include "levelData.h"

namespace {
constexpr SceneKind LEVEL1_SCENE_KIND = SceneKind::Overworld;

void AddCoinRow(std::vector<Coin>& coins, Texture2D& spriteSheet, const SceneType& scene, int startTileX, int tileY, int count) {
    for (int i = 0; i < count; i++) {
        coins.emplace_back((float)((startTileX + i) * TILE_SIZE), (float)(tileY * TILE_SIZE + 12), spriteSheet, scene);
    }
}
}

const SceneType& GetLevel1Scene() {
    return GetSceneType(LEVEL1_SCENE_KIND);
}

void LoadLevel1(
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
) {
    const SceneType& scene = GetLevel1Scene();
    (void)coins;
    followCamera = true;

    castleFlagpole = std::make_unique<CastleFlagpole>(198.0f, 600.0f, spriteSheet, mushroomSheet, marioSheet);

    levelProps.push_back(BackgroundProp(0, 474, spriteSheet, HILL_LAYOUT));
    levelProps.push_back(BackgroundProp(460, 558, spriteSheet, GRASS_LAYOUT));
    levelProps.push_back(BackgroundProp(320, 220, spriteSheet, CLOUD_LAYOUT));
    levelProps.push_back(BackgroundProp(670, 516, spriteSheet, HILL_LAYOUT));
    levelProps.push_back(BackgroundProp(798, 138, spriteSheet, CLOUD_LAYOUT));
    levelProps.push_back(BackgroundProp(1722, 558, spriteSheet, MEDIUM_GRASS_LAYOUT));
    levelProps.push_back(BackgroundProp(2016, 474, spriteSheet, HILL_LAYOUT));
    levelProps.push_back(BackgroundProp(2478, 558, spriteSheet, GRASS_LAYOUT));
    levelProps.push_back(BackgroundProp(2688, 516, spriteSheet, SMALL_HILL_LAYOUT));
    levelProps.push_back(BackgroundProp(2982, 558, spriteSheet, TINY_GRASS_LAYOUT));
    levelProps.push_back(BackgroundProp(3738, 558, spriteSheet, MEDIUM_GRASS_LAYOUT));
    levelProps.push_back(BackgroundProp(4032, 474, spriteSheet, HILL_LAYOUT));
    levelProps.push_back(BackgroundProp(4494, 558, spriteSheet, GRASS_LAYOUT));
    levelProps.push_back(BackgroundProp(4704, 516, spriteSheet, SMALL_HILL_LAYOUT));
    levelProps.push_back(BackgroundProp(5040, 558, spriteSheet, TINY_GRASS_LAYOUT));
    levelProps.push_back(BackgroundProp(5754, 558, spriteSheet, MEDIUM_GRASS_LAYOUT));
    levelProps.push_back(BackgroundProp(5544, 138, spriteSheet, MEDIUM_CLOUD_LAYOUT));
    levelProps.push_back(BackgroundProp(5166, 180, spriteSheet, LARGE_CLOUD_LAYOUT));
    levelProps.push_back(BackgroundProp(4830, 138, spriteSheet, CLOUD_LAYOUT));
    levelProps.push_back(BackgroundProp(4368, 180, spriteSheet, CLOUD_LAYOUT));
    levelProps.push_back(BackgroundProp(3528, 138, spriteSheet, MEDIUM_CLOUD_LAYOUT));
    levelProps.push_back(BackgroundProp(3150, 180, spriteSheet, LARGE_CLOUD_LAYOUT));
    levelProps.push_back(BackgroundProp(2814, 138, spriteSheet, CLOUD_LAYOUT));
    levelProps.push_back(BackgroundProp(2352, 180, spriteSheet, CLOUD_LAYOUT));
    levelProps.push_back(BackgroundProp(1134, 180, spriteSheet, LARGE_CLOUD_LAYOUT));
    levelProps.push_back(BackgroundProp(1512, 96, spriteSheet, MEDIUM_CLOUD_LAYOUT));
    levelProps.push_back(BackgroundProp(6048, 474, spriteSheet, HILL_LAYOUT));
    levelProps.push_back(BackgroundProp(6594, 558, spriteSheet, TINY_GRASS_LAYOUT));
    levelProps.push_back(BackgroundProp(6720, 516, spriteSheet, SMALL_HILL_LAYOUT));
    levelProps.push_back(BackgroundProp(7014, 558, spriteSheet, TINY_GRASS_LAYOUT));
    levelProps.push_back(BackgroundProp(6846, 96, spriteSheet, CLOUD_LAYOUT));
    levelProps.push_back(BackgroundProp(7182, 138, spriteSheet, LARGE_CLOUD_LAYOUT));

    goombas.push_back(std::make_unique<Goomba>((22 * TILE_SIZE), (14 * TILE_SIZE), enemiesSheet, scene));
    goombas.push_back(std::make_unique<Goomba>((40 * TILE_SIZE), (14 * TILE_SIZE), enemiesSheet, scene));
    goombas.push_back(std::make_unique<Goomba>((51 * TILE_SIZE), (14 * TILE_SIZE), enemiesSheet, scene));
    goombas.push_back(std::make_unique<Goomba>((53 * TILE_SIZE), (14 * TILE_SIZE), enemiesSheet, scene));
    goombas.push_back(std::make_unique<Goomba>((80 * TILE_SIZE), (6 * TILE_SIZE), enemiesSheet, scene));
    goombas.push_back(std::make_unique<Goomba>((82 * TILE_SIZE), (6 * TILE_SIZE), enemiesSheet, scene));
    goombas.push_back(std::make_unique<Goomba>((114 * TILE_SIZE), (14 * TILE_SIZE), enemiesSheet, scene));
    goombas.push_back(std::make_unique<Goomba>((116 * TILE_SIZE), (14 * TILE_SIZE), enemiesSheet, scene));
    goombas.push_back(std::make_unique<Goomba>((124 * TILE_SIZE), (14 * TILE_SIZE), enemiesSheet, scene));
    goombas.push_back(std::make_unique<Goomba>((126 * TILE_SIZE), (14 * TILE_SIZE), enemiesSheet, scene));
    goombas.push_back(std::make_unique<Goomba>((128 * TILE_SIZE), (14 * TILE_SIZE), enemiesSheet, scene));
    goombas.push_back(std::make_unique<Goomba>((130 * TILE_SIZE), (14 * TILE_SIZE), enemiesSheet, scene));
    goombas.push_back(std::make_unique<Goomba>((174 * TILE_SIZE), (14 * TILE_SIZE), enemiesSheet, scene));
    goombas.push_back(std::make_unique<Goomba>((176 * TILE_SIZE), (14 * TILE_SIZE), enemiesSheet, scene));

    koopas.push_back(std::make_unique<Koopa>((106 * TILE_SIZE), 537.0f, enemiesSheet, scene));

    blocks.push_back(std::make_unique<DrawTiledRect>(
        0, 600, 2882, 80, spriteSheet, scene.groundBlock, TILE_SIZE, TILE_SIZE, scene
    ));
    blocks.push_back(std::make_unique<PowerUpBlock>((16 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "coin", scene));
    blocks.push_back(std::make_unique<BrickBlock>((20 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<PowerUpBlock>((21 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "mushroom", scene));
    blocks.push_back(std::make_unique<PowerUpBlock>((22 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "coin", scene));
    blocks.push_back(std::make_unique<BrickBlock>((22 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<PowerUpBlock>((23 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "coin", scene));
    blocks.push_back(std::make_unique<BrickBlock>((24 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<PipeBlock>((28 * TILE_SIZE), (12 * TILE_SIZE) + 12, 2, 2, spriteSheet, scene));
    blocks.push_back(std::make_unique<PipeBlock>((38 * TILE_SIZE), (11 * TILE_SIZE) + 12, 2, 3, spriteSheet, scene));
    blocks.push_back(std::make_unique<PipeBlock>((46 * TILE_SIZE), (10 * TILE_SIZE) + 12, 2, 4, spriteSheet, scene));
    blocks.push_back(std::make_unique<WarpPipeBlock>(
        (57 * TILE_SIZE), (10 * TILE_SIZE) + 12, 2, 4, spriteSheet,
        LevelAreaIds::Level11Subarea, (Vector2){ (2.0f * TILE_SIZE) + 4.0f, (2.0f * TILE_SIZE) + 4.0f },
        scene
    ));
    blocks.push_back(std::make_unique<PowerUpBlock>((64 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "1up", scene));
    blocks.push_back(std::make_unique<DrawTiledRect>(
        2982, 600, 630, 84, spriteSheet, scene.groundBlock, TILE_SIZE, TILE_SIZE, scene
    ));
    blocks.push_back(std::make_unique<PowerUpBlock>((78 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "fireflower", scene));
    blocks.push_back(std::make_unique<BrickBlock>((77 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<BrickBlock>((79 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<BrickBlock>((80 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<BrickBlock>((81 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<BrickBlock>((82 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<BrickBlock>((83 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<BrickBlock>((85 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<BrickBlock>((84 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<BrickBlock>((86 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<BrickBlock>((87 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<DrawTiledRect>(
        3738, 600, 2688, 84, spriteSheet, scene.groundBlock, TILE_SIZE, TILE_SIZE, scene
    ));
    blocks.push_back(std::make_unique<BrickBlock>((91 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<BrickBlock>((92 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<BrickBlock>((93 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<PowerUpBlock>((94 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "coin", scene));
    blocks.push_back(std::make_unique<CoinBrickBlock>((94 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, scene));
    blocks.push_back(std::make_unique<StarBrickBlock>((100 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, scene));
    blocks.push_back(std::make_unique<PowerUpBlock>((106 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "coin", scene));
    blocks.push_back(std::make_unique<PowerUpBlock>((109 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "coin", scene));
    blocks.push_back(std::make_unique<PowerUpBlock>((112 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "coin", scene));
    blocks.push_back(std::make_unique<PowerUpBlock>((109 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "fireflower", scene));
    blocks.push_back(std::make_unique<BrickBlock>((118 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<BrickBlock>((121 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<BrickBlock>((122 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<BrickBlock>((123 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<BrickBlock>((129 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<BrickBlock>((130 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<BrickBlock>((128 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<PowerUpBlock>((129 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "coin", scene));
    blocks.push_back(std::make_unique<PowerUpBlock>((130 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "coin", scene));
    blocks.push_back(std::make_unique<BrickBlock>((131 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((134 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((135 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((136 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((136 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((137 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((137 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((137 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((136 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((135 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((140 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((140 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((140 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((141 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((141 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((141 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((142 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((142 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((143 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((148 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((149 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((149 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((137 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((140 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((150 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((150 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((150 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((150 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((151 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((151 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((151 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((151 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((152 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((152 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((152 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((152 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<DrawTiledRect>(
        6510, 600, 2470, 84, spriteSheet, scene.groundBlock, TILE_SIZE, TILE_SIZE, scene
    ));
    blocks.push_back(std::make_unique<ShinyBlock>((155 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((155 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((155 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((155 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((156 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((156 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((156 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((157 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((157 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((158 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<PipeBlock>((163 * TILE_SIZE), (12 * TILE_SIZE) + 12, 2, 2, spriteSheet, scene));
    blocks.push_back(std::make_unique<BrickBlock>((168 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<BrickBlock>((169 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<BrickBlock>((171 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<PowerUpBlock>((170 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "coin", scene));
    blocks.push_back(std::make_unique<PipeBlock>((179 * TILE_SIZE), (12 * TILE_SIZE) + 12, 2, 2, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((181 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((182 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((182 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((183 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((183 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((183 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((184 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((184 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((184 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((184 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((185 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((185 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((185 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((185 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((185 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((186 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((186 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((186 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((186 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((186 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((186 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((187 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((187 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((187 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((187 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((187 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((187 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((187 * TILE_SIZE), (7 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((188 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((188 * TILE_SIZE), (7 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((188 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((188 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((188 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((188 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((188 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((188 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((189 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((189 * TILE_SIZE), (7 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((189 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((189 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((189 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((189 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((189 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, scene));
    blocks.push_back(std::make_unique<ShinyBlock>((189 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, scene));
}

void LoadLevel1Subarea(
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
) {
    const SceneType& scene = GetSceneType(SceneKind::Underground);
    (void)goombas;
    (void)koopas;
    (void)levelProps;
    (void)enemiesSheet;
    (void)tileSize;
    followCamera = false;

    castleFlagpole = std::make_unique<CastleFlagpole>(5000.0f, 600.0f, spriteSheet, mushroomSheet, marioSheet);

    coins.emplace_back((float)(4 * TILE_SIZE), (float)(10 * TILE_SIZE) + 12, spriteSheet, scene);
    coins.emplace_back((float)(5 * TILE_SIZE), (float)(10 * TILE_SIZE) + 12, spriteSheet, scene);
    coins.emplace_back((float)(6 * TILE_SIZE), (float)(10 * TILE_SIZE) + 12, spriteSheet, scene);
    coins.emplace_back((float)(7 * TILE_SIZE), (float)(10 * TILE_SIZE) + 12, spriteSheet, scene);
    coins.emplace_back((float)(8 * TILE_SIZE), (float)(10 * TILE_SIZE) + 12, spriteSheet, scene);
    coins.emplace_back((float)(9 * TILE_SIZE), (float)(10 * TILE_SIZE) + 12, spriteSheet, scene);
    coins.emplace_back((float)(10 * TILE_SIZE), (float)(10 * TILE_SIZE) + 12, spriteSheet, scene);
    coins.emplace_back((float)(10 * TILE_SIZE), (float)(8 * TILE_SIZE) + 12, spriteSheet, scene);
    coins.emplace_back((float)(9 * TILE_SIZE), (float)(8 * TILE_SIZE) + 12, spriteSheet, scene);
    coins.emplace_back((float)(8 * TILE_SIZE), (float)(8 * TILE_SIZE) + 12, spriteSheet, scene);
    coins.emplace_back((float)(7 * TILE_SIZE), (float)(8 * TILE_SIZE) + 12, spriteSheet, scene);
    coins.emplace_back((float)(6 * TILE_SIZE), (float)(8 * TILE_SIZE) + 12, spriteSheet, scene);
    coins.emplace_back((float)(5 * TILE_SIZE), (float)(8 * TILE_SIZE) + 12, spriteSheet, scene);
    coins.emplace_back((float)(4 * TILE_SIZE), (float)(8 * TILE_SIZE) + 12, spriteSheet, scene);
    coins.emplace_back((float)(5 * TILE_SIZE), (float)(6 * TILE_SIZE) + 12, spriteSheet, scene);
    coins.emplace_back((float)(7 * TILE_SIZE), (float)(6 * TILE_SIZE) + 12, spriteSheet, scene);
    coins.emplace_back((float)(6 * TILE_SIZE), (float)(6 * TILE_SIZE) + 12, spriteSheet, scene);
    coins.emplace_back((float)(8 * TILE_SIZE), (float)(6 * TILE_SIZE) + 12, spriteSheet, scene);
    coins.emplace_back((float)(9 * TILE_SIZE), (float)(6 * TILE_SIZE) + 12, spriteSheet, scene);

    blocks.push_back(std::make_unique<DrawTiledRect>(
        0, 600, 672, 84, spriteSheet, GetSceneType(SceneKind::Underground).groundBlock, TILE_SIZE, TILE_SIZE, GetSceneType(SceneKind::Underground)
    ));
    blocks.push_back(std::make_unique<BrickBlock>((0 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((0 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((0 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((4 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((4 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((4 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((5 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((6 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((7 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((9 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((8 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((10 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((10 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((9 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((10 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((8 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((7 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((6 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((5 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((5 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((6 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((7 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((8 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((9 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((0 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((0 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((0 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((0 * TILE_SIZE), (7 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((0 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((0 * TILE_SIZE), (5 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((0 * TILE_SIZE), (4 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((0 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((4 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((5 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((6 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((7 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((9 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((8 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((10 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<WarpPipeBlock>(
        13 * TILE_SIZE, (12 * TILE_SIZE) + 12, 4, 2, spriteSheet,
        LevelAreaIds::Level11, (Vector2){ 163.0f * TILE_SIZE, (12.0f * TILE_SIZE) + 12.0f - TILE_SIZE },
        scene, PipeOrientation::HorizontalRight
    ));
    blocks.push_back(std::make_unique<PipeWallBlock>(
        15 * TILE_SIZE, (3 * TILE_SIZE) + 12, 11, spriteSheet, scene
    ));
}

void LoadLevel12EntranceCutscene(
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
) {
    const SceneType& scene = GetSceneType(SceneKind::Overworld);
    (void)goombas;
    (void)koopas;
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
    coins.emplace_back((float)(58 * TILE_SIZE), (float)(9 * TILE_SIZE) + 12, spriteSheet), GetSceneType(SceneKind::Underground);
    coins.emplace_back((float)(59 * TILE_SIZE), (float)(9 * TILE_SIZE) + 12, spriteSheet), GetSceneType(SceneKind::Underground);
    coins.emplace_back((float)(60 * TILE_SIZE), (float)(9 * TILE_SIZE) + 12, spriteSheet), GetSceneType(SceneKind::Underground);
    coins.emplace_back((float)(61 * TILE_SIZE), (float)(9 * TILE_SIZE) + 12, spriteSheet), GetSceneType(SceneKind::Underground);
    coins.emplace_back((float)(68 * TILE_SIZE), (float)(9 * TILE_SIZE) + 12, spriteSheet), GetSceneType(SceneKind::Underground);
    coins.emplace_back((float)(83 * TILE_SIZE), (float)(6 * TILE_SIZE) + 12, spriteSheet), GetSceneType(SceneKind::Underground);
    coins.emplace_back((float)(84 * TILE_SIZE), (float)(6 * TILE_SIZE) + 12, spriteSheet), GetSceneType(SceneKind::Underground);
    coins.emplace_back((float)(85 * TILE_SIZE), (float)(6 * TILE_SIZE) + 12, spriteSheet), GetSceneType(SceneKind::Underground);
    coins.emplace_back((float)(86 * TILE_SIZE), (float)(6 * TILE_SIZE) + 12, spriteSheet), GetSceneType(SceneKind::Underground);
    coins.emplace_back((float)(87 * TILE_SIZE), (float)(6 * TILE_SIZE) + 12, spriteSheet), GetSceneType(SceneKind::Underground);
    coins.emplace_back((float)(88 * TILE_SIZE), (float)(6 * TILE_SIZE) + 12, spriteSheet), GetSceneType(SceneKind::Underground);
    goombas.push_back(std::make_unique<Goomba>((101 * TILE_SIZE), (14 * TILE_SIZE), enemiesSheet, GetSceneType(SceneKind::Underground)));
    goombas.push_back(std::make_unique<Goomba>((99 * TILE_SIZE), (14 * TILE_SIZE), enemiesSheet, GetSceneType(SceneKind::Underground)));
    goombas.push_back(std::make_unique<Goomba>((97 * TILE_SIZE), (14 * TILE_SIZE), enemiesSheet, GetSceneType(SceneKind::Underground)));
    goombas.push_back(std::make_unique<Goomba>((112 * TILE_SIZE), (14 * TILE_SIZE), enemiesSheet, GetSceneType(SceneKind::Underground)));
    koopas.push_back(std::make_unique<Koopa>((146 * TILE_SIZE), 537, enemiesSheet, GetSceneType(SceneKind::Underground)));
    goombas.push_back(std::make_unique<Goomba>((134 * TILE_SIZE), (10 * TILE_SIZE), enemiesSheet, GetSceneType(SceneKind::Underground)));
    goombas.push_back(std::make_unique<Goomba>((135 * TILE_SIZE), (9 * TILE_SIZE), enemiesSheet, GetSceneType(SceneKind::Underground)));

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
    blocks.push_back(std::make_unique<CoinBrickBlock>((29 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, GetSceneType(SceneKind::Underground)));
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
    blocks.push_back(std::make_unique<MushroomBrickBlock>((69 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, scene));
    blocks.push_back(std::make_unique<BrickBlock>((72 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((72 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((72 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((72 * TILE_SIZE), (7 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((72 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((70 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((71 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<BrickBlock>((72 * TILE_SIZE), (3 * TILE_SIZE) + 12, spriteSheet, GetSceneType(SceneKind::Underground)));
    blocks.push_back(std::make_unique<CoinBrickBlock>((73 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, GetSceneType(SceneKind::Underground)));
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
    blocks.push_back(std::make_unique<MushroomBrickBlock>((150 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, scene));
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
            LevelAreaIds::Level11,
            32.0f * TILE_SIZE
        }
    };

    return configs;
}
