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
#include "mario.h"
#include "scorepopup.h"

enum class LevelArea {
    Level11,
    Level11Subarea,
    Level12Animation,
    Level12Underground
};

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
    std::vector<Coin> coins;
    std::vector<Rectangle> collisionObjects;
    std::vector<BackgroundProp> levelProps;
    std::unique_ptr<CastleFlagpole> castleFlagpole;

    explicit LevelLoader(LevelLoaderResources resources);

    void load(LevelArea area, Vector2 marioStart, Mario& mario, Camera2D& camera, ScorePopupManager& scorePopups);
    void rebuildCollisionObjects();

    Vector2 defaultMarioStart(LevelArea area) const;
    void scoreboardLevel(LevelArea area, int& world, int& level) const;
    LevelArea currentArea() const;
    bool shouldFollowCamera() const;
    bool isUnderground() const;
    bool isLevel11() const;
    float maxCameraX() const;
    const SceneType& drawScene() const;

private:
    LevelLoaderResources resources;
    LevelArea area = LevelArea::Level11;
    bool followCamera = true;

    void clearLevelEntities();
    void loadLevelContents(LevelArea nextArea);
};

#endif
