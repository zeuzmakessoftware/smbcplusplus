#ifndef LEVEL_DATA_LOADERS_H
#define LEVEL_DATA_LOADERS_H

#include "levelData.h"

void LoadLevel1(
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
);

void LoadLevel1Subarea(
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
);

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
);

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
);

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
);

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
);

void LoadLevel13(
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
);

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
);

#endif
