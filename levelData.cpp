#include "levelData.h"

void LoadLevel1(
    std::vector<std::unique_ptr<Block>>& blocks,
    std::vector<std::unique_ptr<Goomba>>& goombas,
    std::vector<BackgroundProp>& levelProps,
    std::unique_ptr<CastleFlagpole>& castleFlagpole,
    Texture2D& spriteSheet,
    Texture2D& mushroomSheet,
    Texture2D& marioSheet,
    Texture2D& enemiesSheet,
    int tileSize
) {
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

    goombas.push_back(std::make_unique<Goomba>((22 * TILE_SIZE), (14 * TILE_SIZE), enemiesSheet));
    goombas.push_back(std::make_unique<Goomba>((40 * TILE_SIZE), (14 * TILE_SIZE), enemiesSheet));
    goombas.push_back(std::make_unique<Goomba>((51 * TILE_SIZE), (14 * TILE_SIZE), enemiesSheet));
    goombas.push_back(std::make_unique<Goomba>((53 * TILE_SIZE), (14 * TILE_SIZE), enemiesSheet));
    goombas.push_back(std::make_unique<Goomba>((80 * TILE_SIZE), (6 * TILE_SIZE), enemiesSheet));
    goombas.push_back(std::make_unique<Goomba>((82 * TILE_SIZE), (6 * TILE_SIZE), enemiesSheet));
    goombas.push_back(std::make_unique<Goomba>((114 * TILE_SIZE), (14 * TILE_SIZE), enemiesSheet));
    goombas.push_back(std::make_unique<Goomba>((116 * TILE_SIZE), (14 * TILE_SIZE), enemiesSheet));
    goombas.push_back(std::make_unique<Goomba>((124 * TILE_SIZE), (14 * TILE_SIZE), enemiesSheet));
    goombas.push_back(std::make_unique<Goomba>((126 * TILE_SIZE), (14 * TILE_SIZE), enemiesSheet));
    goombas.push_back(std::make_unique<Goomba>((128 * TILE_SIZE), (14 * TILE_SIZE), enemiesSheet));
    goombas.push_back(std::make_unique<Goomba>((130 * TILE_SIZE), (14 * TILE_SIZE), enemiesSheet));
    goombas.push_back(std::make_unique<Goomba>((174 * TILE_SIZE), (14 * TILE_SIZE), enemiesSheet));
    goombas.push_back(std::make_unique<Goomba>((176 * TILE_SIZE), (14 * TILE_SIZE), enemiesSheet));

    blocks.push_back(std::make_unique<DrawTiledRect>(
        0, 600, 2882, 80, spriteSheet, (Rectangle){0, 16, 16, 16}, TILE_SIZE, TILE_SIZE
    ));
    blocks.push_back(std::make_unique<PowerUpBlock>((16 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "coin"));
    blocks.push_back(std::make_unique<BrickBlock>((20 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<PowerUpBlock>((21 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "mushroom"));
    blocks.push_back(std::make_unique<PowerUpBlock>((22 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "coin"));
    blocks.push_back(std::make_unique<BrickBlock>((22 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<PowerUpBlock>((23 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "coin"));
    blocks.push_back(std::make_unique<BrickBlock>((24 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<PipeBlock>((28 * TILE_SIZE), (12 * TILE_SIZE) + 12, 2, 2, spriteSheet));
    blocks.push_back(std::make_unique<PipeBlock>((38 * TILE_SIZE), (11 * TILE_SIZE) + 12, 2, 3, spriteSheet));
    blocks.push_back(std::make_unique<PipeBlock>((46 * TILE_SIZE), (10 * TILE_SIZE) + 12, 2, 4, spriteSheet));
    blocks.push_back(std::make_unique<PipeBlock>((57 * TILE_SIZE), (10 * TILE_SIZE) + 12, 2, 4, spriteSheet));
    blocks.push_back(std::make_unique<DrawTiledRect>(
        2982, 600, 630, 84, spriteSheet, (Rectangle){0, 16, 16, 16}, TILE_SIZE, TILE_SIZE
    ));
    blocks.push_back(std::make_unique<PowerUpBlock>((78 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "fireflower"));
    blocks.push_back(std::make_unique<BrickBlock>((77 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<BrickBlock>((79 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<BrickBlock>((80 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<BrickBlock>((81 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<BrickBlock>((82 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<BrickBlock>((83 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<BrickBlock>((85 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<BrickBlock>((84 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<BrickBlock>((86 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<BrickBlock>((87 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<DrawTiledRect>(
        3738, 600, 2688, 84, spriteSheet, (Rectangle){0, 16, 16, 16}, TILE_SIZE, TILE_SIZE
    ));
    blocks.push_back(std::make_unique<BrickBlock>((91 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<BrickBlock>((92 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<BrickBlock>((93 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<PowerUpBlock>((94 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "coin"));
    blocks.push_back(std::make_unique<BrickBlock>((100 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<PowerUpBlock>((106 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "coin"));
    blocks.push_back(std::make_unique<PowerUpBlock>((109 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "coin"));
    blocks.push_back(std::make_unique<PowerUpBlock>((112 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "coin"));
    blocks.push_back(std::make_unique<PowerUpBlock>((109 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "fireflower"));
    blocks.push_back(std::make_unique<BrickBlock>((118 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<BrickBlock>((121 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<BrickBlock>((122 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<BrickBlock>((123 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<BrickBlock>((129 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<BrickBlock>((130 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<BrickBlock>((128 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<PowerUpBlock>((129 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "coin"));
    blocks.push_back(std::make_unique<PowerUpBlock>((130 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "coin"));
    blocks.push_back(std::make_unique<BrickBlock>((131 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((134 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((135 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((136 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((136 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((137 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((137 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((137 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((136 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((135 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((140 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((140 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((140 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((141 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((141 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((141 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((142 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((142 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((143 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((148 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((149 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((149 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((137 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((140 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((150 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((150 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((150 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((150 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((151 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((151 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((151 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((151 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((152 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((152 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((152 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((152 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<DrawTiledRect>(
        6510, 600, 2470, 84, spriteSheet, (Rectangle){0, 16, 16, 16}, TILE_SIZE, TILE_SIZE
    ));
    blocks.push_back(std::make_unique<ShinyBlock>((155 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((155 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((155 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((155 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((156 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((156 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((156 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((157 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((157 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((158 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<PipeBlock>((163 * TILE_SIZE), (12 * TILE_SIZE) + 12, 2, 2, spriteSheet));
    blocks.push_back(std::make_unique<BrickBlock>((168 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<BrickBlock>((169 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<BrickBlock>((171 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<PowerUpBlock>((170 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "coin"));
    blocks.push_back(std::make_unique<PipeBlock>((179 * TILE_SIZE), (12 * TILE_SIZE) + 12, 2, 2, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((181 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((182 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((182 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((183 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((183 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((183 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((184 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((184 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((184 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((184 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((185 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((185 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((185 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((185 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((185 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((186 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((186 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((186 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((186 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((186 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((186 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((187 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((187 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((187 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((187 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((187 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((187 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((187 * TILE_SIZE), (7 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((188 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((188 * TILE_SIZE), (7 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((188 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((188 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((188 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((188 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((188 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((188 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((189 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((189 * TILE_SIZE), (7 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((189 * TILE_SIZE), (8 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((189 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((189 * TILE_SIZE), (9 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((189 * TILE_SIZE), (12 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((189 * TILE_SIZE), (11 * TILE_SIZE) + 12, spriteSheet));
    blocks.push_back(std::make_unique<ShinyBlock>((189 * TILE_SIZE), (13 * TILE_SIZE) + 12, spriteSheet));
}
