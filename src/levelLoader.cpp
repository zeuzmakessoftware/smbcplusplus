#include "levelLoader.h"

LevelLoader::LevelLoader(LevelLoaderResources resources)
    : resources(resources) {}

void LevelLoader::load(const LevelAreaId& nextArea, Vector2 marioStart, Mario& mario, Camera2D& camera, ScorePopupManager& scorePopups) {
    clearLevelEntities();
    const LevelAreaConfig* config = findConfig(nextArea);
    if (!config) {
        config = findConfig(LevelAreaIds::Level11);
    }
    area = config->id;

    config->load(
        blocks, goombas, koopas, piranhaPlants, lifts, coins, levelProps, castleFlagpole, followCamera,
        resources.spriteSheet, resources.mushroomSheet, resources.marioSheet, resources.enemiesSheet, resources.tileSize
    );
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
        if (!block->hasCollision()) {
            continue;
        }
        collisionObjects.push_back(block->returnRec());
    }
    if (castleFlagpole) {
        collisionObjects.push_back(castleFlagpole->returnCollisionRec());
    }
    for (auto& lift : lifts) {
        collisionObjects.push_back(lift.returnRec());
    }
}

void LevelLoader::updateLifts(Mario& mario, float cameraX) {
    std::vector<Rectangle> solidObjects;
    solidObjects.reserve(collisionObjects.size());
    for (auto& block : blocks) {
        if (!block->hasCollision()) {
            continue;
        }
        solidObjects.push_back(block->returnRec());
    }
    if (castleFlagpole) {
        solidObjects.push_back(castleFlagpole->returnCollisionRec());
    }

    for (auto& lift : lifts) {
        lift.update(mario, solidObjects, cameraX);
    }
    rebuildCollisionObjects();
}

const LevelAreaId& LevelLoader::currentArea() const {
    return area;
}

Vector2 LevelLoader::defaultMarioStart(const LevelAreaId& requestedArea) const {
    const LevelAreaConfig* config = findConfig(requestedArea);
    return config ? config->defaultMarioStart : Vector2{100.0f, 0.0f};
}

void LevelLoader::scoreboardLevel(const LevelAreaId& requestedArea, int& world, int& level) const {
    const LevelAreaConfig* config = findConfig(requestedArea);
    if (!config) {
        world = 1;
        level = 1;
        return;
    }
    world = config->scoreboardWorld;
    level = config->scoreboardLevel;
}

bool LevelLoader::shouldFollowCamera() const {
    return followCamera;
}

bool LevelLoader::isUnderground() const {
    return currentConfig().underground;
}

bool LevelLoader::hasFlagpole() const {
    return currentConfig().hasFlagpole;
}

bool LevelLoader::isLevel12EntranceCutscene() const {
    return currentConfig().level12EntranceCutscene;
}

const LevelAreaId& LevelLoader::flagpoleCompleteArea() const {
    return currentConfig().flagpoleCompleteArea;
}

float LevelLoader::maxCameraX() const {
    float levelWidth = currentConfig().levelWidth;
    return levelWidth < 0.0f ? -1.0f : levelWidth - resources.screenWidth;
}

const SceneType& LevelLoader::drawScene() const {
    return isUnderground() ? GetSceneType(SceneKind::Underground) : GetLevel1Scene();
}

const LevelAreaConfig* LevelLoader::findConfig(const LevelAreaId& requestedArea) const {
    for (const LevelAreaConfig& config : GetLevelAreaConfigs()) {
        if (config.id == requestedArea) {
            return &config;
        }
    }
    return nullptr;
}

const LevelAreaConfig& LevelLoader::currentConfig() const {
    const LevelAreaConfig* config = findConfig(area);
    if (config) {
        return *config;
    }
    return GetLevelAreaConfigs().front();
}

void LevelLoader::clearLevelEntities() {
    blocks.clear();
    goombas.clear();
    koopas.clear();
    piranhaPlants.clear();
    lifts.clear();
    coins.clear();
    collisionObjects.clear();
    levelProps.clear();
}
