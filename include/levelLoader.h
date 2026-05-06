#ifndef LEVEL_LOADER_H
#define LEVEL_LOADER_H

#include <memory>
#include <vector>
#include <raylib.h>
#include "backgroundProp.h"
#include "blocks.h"
#include "castleFlagpole.h"
#include "goomba.h"
#include "koopa.h"
#include "levelData.h"
#include "mario.h"
#include "piranhaPlant.h"
#include "scorepopup.h"

struct LevelLoaderResources {
    Texture2D& spriteSheet;
    Texture2D& mushroomSheet;
    Texture2D& marioSheet;
    Texture2D& enemiesSheet;
    int tileSize;
    int screenWidth;
};

class LevelLoader {
public:
    std::vector<std::unique_ptr<Block>> blocks;
    std::vector<std::unique_ptr<Goomba>> goombas;
    std::vector<std::unique_ptr<Koopa>> koopas;
    std::vector<std::unique_ptr<PiranhaPlant>> piranhaPlants;
    std::vector<Coin> coins;
    std::vector<Rectangle> collisionObjects;
    std::vector<BackgroundProp> levelProps;
    std::unique_ptr<CastleFlagpole> castleFlagpole;

    explicit LevelLoader(LevelLoaderResources resources);

    void load(const LevelAreaId& area, Vector2 marioStart, Mario& mario, Camera2D& camera, ScorePopupManager& scorePopups);
    void rebuildCollisionObjects();

    Vector2 defaultMarioStart(const LevelAreaId& area) const;
    void scoreboardLevel(const LevelAreaId& area, int& world, int& level) const;
    const LevelAreaId& currentArea() const;
    bool shouldFollowCamera() const;
    bool isUnderground() const;
    bool hasFlagpole() const;
    bool isLevel12EntranceCutscene() const;
    const LevelAreaId& flagpoleCompleteArea() const;
    float maxCameraX() const;
    const SceneType& drawScene() const;

private:
    LevelLoaderResources resources;
    LevelAreaId area = LevelAreaIds::Level11;
    bool followCamera = true;

    const LevelAreaConfig* findConfig(const LevelAreaId& requestedArea) const;
    const LevelAreaConfig& currentConfig() const;
    void clearLevelEntities();
};

#endif
