#include "levelLoader.h"
#include "levelData.h"

LevelLoader::LevelLoader(LevelLoaderResources resources)
    : resources(resources) {}

void LevelLoader::load(LevelArea nextArea, Vector2 marioStart, Mario& mario, Camera2D& camera, ScorePopupManager& scorePopups) {
    clearLevelEntities();
    area = nextArea;

    loadLevelContents(nextArea);
    rebuildCollisionObjects();

    mario.setScriptedPose(marioStart.x, marioStart.y, true);
    if (castleFlagpole) {
        castleFlagpole->reset();
    }
    scorePopups.clear();

    camera.target = {
        followCamera && marioStart.x > resources.screenWidth / 2.0f ? marioStart.x - resources.screenWidth / 2.0f : 0.0f,
        0.0f
    };
}

void LevelLoader::rebuildCollisionObjects() {
    collisionObjects.clear();
    for (auto& block : blocks) {
        auto* pBlock = dynamic_cast<PowerUpBlock*>(block.get());
        if (pBlock && !pBlock->hasCollision()) {
            continue;
        }
        collisionObjects.push_back(block->returnRec());
    }
    if (castleFlagpole) {
        collisionObjects.push_back(castleFlagpole->returnCollisionRec());
    }
}

LevelArea LevelLoader::currentArea() const {
    return area;
}

Vector2 LevelLoader::defaultMarioStart(LevelArea requestedArea) const {
    switch (requestedArea) {
        case LevelArea::Level11:
            return {100.0f, 0.0f};
        case LevelArea::Level11Subarea:
            return {(2.0f * resources.tileSize) + 4.0f, (2.0f * resources.tileSize) + 4.0f};
        case LevelArea::Level12Animation:
            return {126.0f, (13.0f * resources.tileSize) + 12.0f};
        case LevelArea::Level12Underground:
            return {(2.0f * resources.tileSize) + 4.0f, (2.0f * resources.tileSize) + 4.0f};
    }
    return {100.0f, 0.0f};
}

void LevelLoader::scoreboardLevel(LevelArea requestedArea, int& world, int& level) const {
    world = 1;
    level = requestedArea == LevelArea::Level11 || requestedArea == LevelArea::Level11Subarea ? 1 : 2;
}

bool LevelLoader::shouldFollowCamera() const {
    return followCamera;
}

bool LevelLoader::isUnderground() const {
    return area == LevelArea::Level11Subarea || area == LevelArea::Level12Underground;
}

bool LevelLoader::isLevel11() const {
    return area == LevelArea::Level11;
}

float LevelLoader::maxCameraX() const {
    if (area == LevelArea::Level11Subarea) {
        return (32 * resources.tileSize) - resources.screenWidth;
    }
    if (area == LevelArea::Level12Underground) {
        return 7140.0f - resources.screenWidth;
    }
    return -1.0f;
}

const SceneType& LevelLoader::drawScene() const {
    return isUnderground() ? GetSceneType(SceneKind::Underground) : GetLevel1Scene();
}

void LevelLoader::clearLevelEntities() {
    blocks.clear();
    goombas.clear();
    koopas.clear();
    coins.clear();
    collisionObjects.clear();
    levelProps.clear();
}

void LevelLoader::loadLevelContents(LevelArea nextArea) {
    switch (nextArea) {
        case LevelArea::Level11:
            LoadLevel1(
                blocks, goombas, koopas, coins, levelProps, castleFlagpole, followCamera,
                resources.spriteSheet, resources.mushroomSheet, resources.marioSheet, resources.enemiesSheet, resources.tileSize
            );
            break;
        case LevelArea::Level11Subarea:
            LoadLevel1Subarea(
                blocks, goombas, koopas, coins, levelProps, castleFlagpole, followCamera,
                resources.spriteSheet, resources.mushroomSheet, resources.marioSheet, resources.enemiesSheet, resources.tileSize
            );
            break;
        case LevelArea::Level12Animation:
            LoadLevel12EntranceCutscene(
                blocks, goombas, koopas, coins, levelProps, castleFlagpole, followCamera,
                resources.spriteSheet, resources.mushroomSheet, resources.marioSheet, resources.enemiesSheet, resources.tileSize
            );
            break;
        case LevelArea::Level12Underground:
            LoadLevel12UndergroundStart(
                blocks, goombas, koopas, coins, levelProps, castleFlagpole, followCamera,
                resources.spriteSheet, resources.mushroomSheet, resources.marioSheet, resources.enemiesSheet, resources.tileSize
            );
            break;
    }
}
