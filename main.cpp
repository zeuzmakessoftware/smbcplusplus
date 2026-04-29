#include <raylib.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "mario.h"
#include "drawTiledRect.h"
#include "backgroundProp.h"
#include "blocks.h"
#include "mushroom.h"
#include "goomba.h"

#define TILE_SIZE 42

int main() {
    int screenWidth = 670;
    int screenHeight = 670;
    InitWindow(screenWidth, screenHeight, "Swag Bros");

    bool gameStarted = false;
    
    Image img1 = LoadImage("52571.png");
    ImageColorReplace(&img1, (Color){148, 148, 255, 255}, BLANK);
    Texture2D spriteSheet = LoadTextureFromImage(img1);
    UnloadImage(img1);

    Image img2 = LoadImage("50365.png");
    ImageColorReplace(&img2, (Color){146, 144, 255, 255}, BLANK);
    Texture2D marioSheet = LoadTextureFromImage(img2);
    UnloadImage(img2);

    Image img3 = LoadImage("52569.png");
    ImageColorReplace(&img3, (Color){146, 144, 255, 255}, BLANK);
    Texture2D mushroomSheet = LoadTextureFromImage(img3);
    UnloadImage(img3);

    Image img4 = LoadImage("52570.png");
    ImageColorReplace(&img4, (Color){146, 144, 255, 255}, BLANK);
    Texture2D enemiesSheet = LoadTextureFromImage(img4);
    UnloadImage(img4);

    std::vector<std::unique_ptr<Block>> blocks;
    std::vector<std::unique_ptr<Goomba>> goombas;
    std::vector<Rectangle> collisionObjects;
    std::vector<std::unique_ptr<Mushroom>> activeMushrooms;
    std::vector<Particle> brickParticles;
    std::vector<BackgroundProp> levelProps;

    Mario MarioObj(100, 0, marioSheet);

    Camera2D camera = { 0 };
    camera.target = (Vector2){ 0, 0 };
    camera.offset = (Vector2){ 0, 0 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    bool isDead = false;
    float deathTimer = 0.0f;

    auto ResetLevel = [&]() {
        blocks.clear();
        goombas.clear();
        activeMushrooms.clear();
        brickParticles.clear();
        collisionObjects.clear();
        levelProps.clear();

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
        blocks.push_back(std::make_unique<PowerUpBlock>((16 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, spriteSheet, "coin"));
        blocks.push_back(std::make_unique<BrickBlock>((20 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet));
        blocks.push_back(std::make_unique<PowerUpBlock>((21 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "mushroom"));
        blocks.push_back(std::make_unique<PowerUpBlock>((22 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, spriteSheet, "coin"));
        blocks.push_back(std::make_unique<BrickBlock>((22 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet));
        blocks.push_back(std::make_unique<PowerUpBlock>((23 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, spriteSheet, "coin"));
        blocks.push_back(std::make_unique<BrickBlock>((24 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet));
        blocks.push_back(std::make_unique<PipeBlock>((28 * TILE_SIZE), (12 * TILE_SIZE) + 12, 2, 2, spriteSheet));
        blocks.push_back(std::make_unique<PipeBlock>((38 * TILE_SIZE), (11 * TILE_SIZE) + 12, 2, 3, spriteSheet));
        blocks.push_back(std::make_unique<PipeBlock>((46 * TILE_SIZE), (10 * TILE_SIZE) + 12, 2, 4, spriteSheet));
        blocks.push_back(std::make_unique<PipeBlock>((57 * TILE_SIZE), (10 * TILE_SIZE) + 12, 2, 4, spriteSheet));
        blocks.push_back(std::make_unique<DrawTiledRect>(
            2982, 600, 630, 84, spriteSheet, (Rectangle){0, 16, 16, 16}, TILE_SIZE, TILE_SIZE
        ));
        blocks.push_back(std::make_unique<PowerUpBlock>((78 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "mushroom"));
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
        blocks.push_back(std::make_unique<PowerUpBlock>((94 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, spriteSheet, "coin"));
        blocks.push_back(std::make_unique<BrickBlock>((100 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet));
        blocks.push_back(std::make_unique<PowerUpBlock>((106 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, spriteSheet, "coin"));
        blocks.push_back(std::make_unique<PowerUpBlock>((109 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, spriteSheet, "coin"));
        blocks.push_back(std::make_unique<PowerUpBlock>((112 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, spriteSheet, "coin"));
        blocks.push_back(std::make_unique<PowerUpBlock>((109 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, mushroomSheet, "mushroom"));
        blocks.push_back(std::make_unique<BrickBlock>((118 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet));
        blocks.push_back(std::make_unique<BrickBlock>((121 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet));
        blocks.push_back(std::make_unique<BrickBlock>((122 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet));
        blocks.push_back(std::make_unique<BrickBlock>((123 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet));
        blocks.push_back(std::make_unique<BrickBlock>((129 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet));
        blocks.push_back(std::make_unique<BrickBlock>((130 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet));
        blocks.push_back(std::make_unique<BrickBlock>((128 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet));
        blocks.push_back(std::make_unique<PowerUpBlock>((129 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, spriteSheet, "coin"));
        blocks.push_back(std::make_unique<PowerUpBlock>((130 * TILE_SIZE), (6 * TILE_SIZE) + 12, spriteSheet, spriteSheet, "coin"));
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
            6510, 600, 1470, 84, spriteSheet, (Rectangle){0, 16, 16, 16}, TILE_SIZE, TILE_SIZE
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
        blocks.push_back(std::make_unique<PowerUpBlock>((170 * TILE_SIZE), (10 * TILE_SIZE) + 12, spriteSheet, spriteSheet, "coin"));
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

        for (auto& block : blocks) {
            collisionObjects.push_back(block->returnRec());
        }

        MarioObj.reset(100, 0);
        camera.target = (Vector2){ 0, 0 };
        isDead = false;
    };

    ResetLevel();

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (!gameStarted) {
            BeginDrawing();
                if (IsKeyPressed(KEY_ENTER)) gameStarted = true;
                ClearBackground(BLACK);
                DrawText("press enter", 50, 50, 36, WHITE);
            EndDrawing();
        } else {
            if (!isDead) {
                for (auto it = blocks.begin(); it != blocks.end(); ) {
                    (*it)->update(MarioObj.returnRec(), MarioObj.getVelY(), MarioObj.getIsBig());
                    
                    auto* brick = dynamic_cast<BrickBlock*>(it->get());
                    if (brick && brick->isDestroyed()) {
                        brick->SpawnBrickParticles(brickParticles);
                        it = blocks.erase(it);
                        
                        collisionObjects.clear();
                        for (auto& b : blocks) collisionObjects.push_back(b->returnRec());
                    } else {
                        auto* pBlock = dynamic_cast<PowerUpBlock*>(it->get());
                        if (pBlock) {
                            auto newMush = pBlock->takeMushroom();
                            if (newMush) activeMushrooms.push_back(std::move(newMush));
                        }
                        ++it;
                    }
                }

                for (auto it = goombas.begin(); it != goombas.end(); ) {
                    if (!MarioObj.getIsTransforming()) {
                        (*it)->update(collisionObjects, MarioObj, isDead, deathTimer, camera.target.x);
                    } 
                    if ((*it)->shouldRemove()) it = goombas.erase(it);
                    else ++it;
                }

                BrickBlock::updateParticles(brickParticles);
                for (auto& mush : activeMushrooms) mush->update(collisionObjects);
                MarioObj.update(collisionObjects, camera.target.x, activeMushrooms);

                float scrollThreshold = screenWidth / 1.967f;
                if (MarioObj.getPos().x > scrollThreshold) {
                    float targetX = MarioObj.getPos().x - scrollThreshold;
                    if (targetX > camera.target.x) camera.target.x = targetX;
                }

                if (MarioObj.getPos().y > 700) {
                    isDead = true;
                    deathTimer = 4.0f;
                }
            } else {
                deathTimer -= GetFrameTime();
                if (deathTimer <= 0) ResetLevel();
            }

            BeginDrawing();
                ClearBackground(Color({91, 140, 255, 255}));
                BeginMode2D(camera);
                    for (auto& prop : levelProps) prop.draw();
                    for (auto& block : blocks) block->draw();
                    for (auto& mush : activeMushrooms) mush->draw();
                    for (auto& goom : goombas) goom->draw();
                    BrickBlock::drawParticles(brickParticles, spriteSheet);
                    MarioObj.draw();
                EndMode2D();
                
                DrawText("swag bros", 50, 50, 36, WHITE);
                if (isDead) {
                    DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.6f));
                    int textWidth = MeasureText("skull emoji", 60);
                    DrawText("skull emoji", (screenWidth / 2) - (textWidth / 2), (screenHeight / 2) - 30, 60, RED);
                }
            EndDrawing();
        }
    }
    UnloadTexture(spriteSheet);
    UnloadTexture(marioSheet);
    UnloadTexture(mushroomSheet);
    CloseWindow();
    return 0;
}