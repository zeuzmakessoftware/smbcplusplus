#include <raylib.h>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "mario.h"
#include "drawTiledRect.h"
#include "backgroundProp.h"
#include "blocks.h"
#include "mushroom.h"
#include "fireflower.h"
#include "star.h"
#include "fireball.h"
#include "goomba.h"
#include "koopa.h"
#include "piranhaPlant.h"
#include "levelLoader.h"
#include "scoreboard.h"
#include "castleFlagpole.h"
#include "scorepopup.h"
#include "bowserBoss.h"
#include "blocks/bridgeBlock.h"
#include "soundObject.h"

#define TILE_SIZE 42

struct PipeTransition {
    bool active = false;
    WarpDestination destination;
    Vector2 exitPosition = {0.0f, 0.0f};
    PipeOrientation orientation = PipeOrientation::Vertical;
    Vector2 startPosition = {0.0f, 0.0f};
    bool faceRight = true;
    float timer = 0.0f;
    float duration = 0.72f;
};

struct Level12EntranceCutscene {
    bool active = false;
    float walkSpeed = 84.0f;
    float marioY = (13.0f * TILE_SIZE) + 12.0f;
};

struct LevelIntro {
    bool active = false;
    float timer = 0.0f;
    float duration = 3.0f;

    void start() {
        active = true;
        timer = duration;
    }

    void update(float dt) {
        if (!active) return;

        timer -= dt;
        if (timer <= 0.0f) {
            active = false;
        }
    }
};

namespace {
constexpr int CastleBridgeSegments = 13;
constexpr float CastleBridgeY = (11.0f * TILE_SIZE) + 12.0f;
constexpr float CastleAxeX = (140.0f * TILE_SIZE) + 10.0f;
constexpr float CastleAxeY = (9.0f * TILE_SIZE) + 12.0f;
constexpr float CastleChainX = 139.0f * TILE_SIZE;
constexpr float CastleChainY = (10.0f * TILE_SIZE) + 12.0f;
constexpr float CastleBowserX = 136.0f * TILE_SIZE;
constexpr float CastleBowserY = (9.0f * TILE_SIZE) + 13.0f;
constexpr float CastleBowserLeft = 133.0f * TILE_SIZE;
constexpr float CastleBowserRight = 140.0f * TILE_SIZE;
constexpr float CastleToadX = 154.0f * TILE_SIZE;
constexpr float CastleToadGroundY = (14.0f * TILE_SIZE) + 12.0f;
constexpr float CastleMarioToadStopX = CastleToadX - 80.0f;

Rectangle CastleAxeRec() {
    return {CastleAxeX, CastleAxeY, (float)TILE_SIZE, (float)TILE_SIZE};
}

enum class CastleEndingState {
    Inactive,
    BridgeCollapse,
    WalkToToad,
    Message
};

struct CastleEnding {
    CastleEndingState state = CastleEndingState::Inactive;
    float timer = 0.0f;
    float bridgeTimer = 0.0f;
    int removedBridgeSegments = 0;

    void reset() {
        state = CastleEndingState::Inactive;
        timer = 0.0f;
        bridgeTimer = 0.0f;
        removedBridgeSegments = 0;
    }

    void start() {
        state = CastleEndingState::BridgeCollapse;
        timer = 0.0f;
        bridgeTimer = 0.0f;
        removedBridgeSegments = 0;
    }

    bool active() const {
        return state != CastleEndingState::Inactive;
    }
};
}

int main() {
    int screenWidth = 670;
    int screenHeight = 670;
    InitWindow(screenWidth, screenHeight, "Swag Bros");

    bool gameStarted = false;
    LevelIntro levelIntro;
    int marioLives = 3;
    
    Image img1 = LoadImage("assets/images/52571.png");
    ImageColorReplace(&img1, (Color){148, 148, 255, 255}, BLANK);
    ImageColorReplace(&img1, (Color){0, 41, 140, 255}, BLANK);
    Texture2D spriteSheet = LoadTextureFromImage(img1);
    UnloadImage(img1);

    Image img2 = LoadImage("assets/images/50365.png");
    ImageColorReplace(&img2, (Color){146, 144, 255, 255}, BLANK);
    Texture2D marioSheet = LoadTextureFromImage(img2);
    UnloadImage(img2);

    Image img3 = LoadImage("assets/images/52569.png");
    ImageColorReplace(&img3, (Color){146, 144, 255, 255}, BLANK);
    ImageColorReplace(&img3, (Color){108, 106, 255, 255}, BLANK);
    Texture2D mushroomSheet = LoadTextureFromImage(img3);
    UnloadImage(img3);

    Image img4 = LoadImage("assets/images/52570.png");
    ImageColorReplace(&img4, (Color){146, 144, 255, 255}, BLANK);
    ImageColorReplace(&img4, (Color){0, 41, 140, 255}, BLANK);
    Texture2D enemiesSheet = LoadTextureFromImage(img4);
    UnloadImage(img4);

    Image hudImg = LoadImage("assets/images/56929.png");
    ImageColorReplace(&hudImg, (Color){148, 148, 255, 255}, BLANK);
    Texture2D hudSheet = LoadTextureFromImage(hudImg);
    UnloadImage(hudImg);

    Font nesFont = LoadFontEx("assets/fonts/super-mario-bros-nes.otf", 36, NULL, 0);
    SetTextureFilter(nesFont.texture, TEXTURE_FILTER_POINT);

    SoundObject sound;
    sound.load();

    std::vector<std::unique_ptr<Mushroom>> activeMushrooms;
    std::vector<std::unique_ptr<FireFlower>> activeFireFlowers;
    std::vector<std::unique_ptr<Star>> activeStars;
    std::vector<std::unique_ptr<Fireball>> activeFireballs;
    std::vector<Particle> brickParticles;
    ScorePopupManager scorePopups;
    PipeTransition pipeTransition;
    Level12EntranceCutscene level12EntranceCutscene;
    CastleEnding castleEnding;
    std::unique_ptr<BowserBoss> bowserBoss;

    Mario MarioObj(100, 0, marioSheet);
    Scoreboard scoreboard(1, 1, 400);
    LevelLoader levelLoader({
        spriteSheet,
        mushroomSheet,
        marioSheet,
        enemiesSheet,
        TILE_SIZE,
        screenWidth
    });
    // Change this to another LevelAreaIds value or registered area id to boot elsewhere.
    LevelAreaId startingArea = LevelAreaIds::Level11;
    LevelAreaId respawnArea = startingArea;

    Camera2D camera = { 0 };
    camera.target = (Vector2){ 0, 0 };
    camera.offset = (Vector2){ 0, 0 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    bool isDead = false;
    float deathTimer = 0.0f;

    auto StartDeath = [&]() {
        if (isDead) return;
        if (marioLives > 0) marioLives--;
        isDead = true;
        deathTimer = 4.0f;
        sound.stopMusic();
        sound.play(SoundCue::Death);
    };

    auto LoadArea = [&](const LevelAreaId& area, Vector2 marioStart) {
        activeMushrooms.clear();
        activeFireFlowers.clear();
        activeStars.clear();
        activeFireballs.clear();
        brickParticles.clear();
        castleEnding.reset();
        bowserBoss.reset();

        levelLoader.load(area, marioStart, MarioObj, camera, scorePopups);
        sound.playMusic(levelLoader.musicTrack(area));
        isDead = false;
        pipeTransition.active = false;
        level12EntranceCutscene.active = levelLoader.isLevel12EntranceCutscene();
        if (area == LevelAreaIds::Level14) {
            bowserBoss = std::make_unique<BowserBoss>(CastleBowserX, CastleBowserY, CastleBowserLeft, CastleBowserRight, enemiesSheet);
        }
    };

    auto ResetLevel = [&]() {
        Vector2 startPosition = levelLoader.defaultMarioStart(respawnArea);
        MarioObj.reset(startPosition.x, startPosition.y);
        LoadArea(respawnArea, startPosition);
        scoreboard.reset(400);
        int world = 1;
        int level = 1;
        levelLoader.scoreboardLevel(respawnArea, world, level);
        scoreboard.setLevel(world, level);
    };

    auto StartAreaIntro = [&](const LevelAreaId& area) {
        respawnArea = area;
        int world = 1;
        int level = 1;
        levelLoader.scoreboardLevel(area, world, level);
        scoreboard.setLevel(world, level);
        scoreboard.setTime(400);
        LoadArea(area, levelLoader.defaultMarioStart(area));
        levelIntro.start();
    };

    auto StartPipeTransition = [&](WarpPipeBlock* warpPipe) {
        Rectangle pipeRec = warpPipe->returnRec();
        Rectangle marioRec = MarioObj.returnRec();
        PipeOrientation orientation = warpPipe->getOrientation();

        pipeTransition.active = true;
        sound.play(SoundCue::Pipe);
        pipeTransition.destination = warpPipe->getDestination();
        pipeTransition.exitPosition = warpPipe->getExitPosition();
        pipeTransition.orientation = orientation;
        pipeTransition.timer = 0.0f;
        pipeTransition.faceRight = orientation != PipeOrientation::HorizontalLeft;

        if (orientation == PipeOrientation::Vertical) {
            pipeTransition.startPosition = {
                marioRec.x,
                marioRec.y
            };
            pipeTransition.faceRight = true;
        } else {
            pipeTransition.startPosition = {marioRec.x, pipeRec.y + pipeRec.height - marioRec.height};
        }

        MarioObj.setScriptedPose(pipeTransition.startPosition.x, pipeTransition.startPosition.y, pipeTransition.faceRight);
    };

    auto UpdatePipeTransition = [&]() {
        pipeTransition.timer += GetFrameTime();
        float t = pipeTransition.timer / pipeTransition.duration;
        if (t > 1.0f) t = 1.0f;

        Vector2 p = pipeTransition.startPosition;
        if (pipeTransition.orientation == PipeOrientation::Vertical) {
            p.y += t * TILE_SIZE * 1.35f;
        } else if (pipeTransition.orientation == PipeOrientation::HorizontalRight) {
            p.x += t * TILE_SIZE * 1.35f;
        } else {
            p.x -= t * TILE_SIZE * 1.35f;
        }
        MarioObj.setScriptedPose(p.x, p.y, pipeTransition.faceRight);

        if (pipeTransition.timer >= pipeTransition.duration) {
            Vector2 exitPosition = pipeTransition.exitPosition;
            if (MarioObj.getIsBig()) exitPosition.y -= TILE_SIZE;

            if (!pipeTransition.destination.empty()) {
                LoadArea(pipeTransition.destination, exitPosition);
            }
        }
    };

    auto UpdateLevel12EntranceCutscene = [&]() {
        Vector2 pos = MarioObj.getPos();
        const float pipeMouthX = (10.0f * TILE_SIZE) - TILE_SIZE;
        pos.x += level12EntranceCutscene.walkSpeed * GetFrameTime();

        if (pos.x >= pipeMouthX) {
            pos.x = pipeMouthX;
            MarioObj.setScriptedPose(pos.x, level12EntranceCutscene.marioY, true);
            level12EntranceCutscene.active = false;

            for (auto& block : levelLoader.blocks) {
                auto* warpPipe = dynamic_cast<WarpPipeBlock*>(block.get());
                if (warpPipe && warpPipe->getDestination() == LevelAreaIds::Level12Underground) {
                    StartPipeTransition(warpPipe);
                    break;
                }
            }
            return;
        }

        MarioObj.setScriptedPose(pos.x, level12EntranceCutscene.marioY - (MarioObj.getIsBig() || MarioObj.getIsFire() ? TILE_SIZE : 0.0f), true, 3.0f);
    };

    auto DrawLevel12EntranceCastle = [&]() {
        DrawTexturePro(
            spriteSheet,
            (Rectangle){24.0f, 696.0f, 80.0f, 80.0f},
            (Rectangle){0.0f, 390.0f, 210.0f, 210.0f},
            (Vector2){0.0f, 0.0f},
            0.0f,
            WHITE
        );
    };

    auto MarioScriptedGroundY = [&]() {
        return CastleToadGroundY - (MarioObj.getIsBig() || MarioObj.getIsFire() ? (2.0f * TILE_SIZE) : (float)TILE_SIZE);
    };

    auto RemoveBridgeSegment = [&](int segmentIndex) {
        for (auto it = levelLoader.blocks.begin(); it != levelLoader.blocks.end(); ++it) {
            auto* bridge = dynamic_cast<BridgeBlock*>(it->get());
            if (bridge && bridge->getSegmentIndex() == segmentIndex) {
                levelLoader.blocks.erase(it);
                levelLoader.rebuildCollisionObjects();
                return;
            }
        }
    };

    auto StartCastleEnding = [&]() {
        castleEnding.start();
        activeFireballs.clear();
        if (bowserBoss) bowserBoss->dropFromBridge();

        Vector2 pos = MarioObj.getPos();
        MarioObj.setScriptedPose(pos.x, pos.y, true);
    };

    auto UpdateCastleEnding = [&]() {
        const float dt = GetFrameTime();
        castleEnding.timer += dt;

        if (bowserBoss) {
            bowserBoss->updateFalling(MarioObj, isDead, deathTimer, camera.target.x);
        }

        if (castleEnding.state == CastleEndingState::BridgeCollapse) {
            castleEnding.bridgeTimer += dt;
            while (castleEnding.bridgeTimer >= 0.075f && castleEnding.removedBridgeSegments < CastleBridgeSegments) {
                castleEnding.bridgeTimer -= 0.075f;
                RemoveBridgeSegment((CastleBridgeSegments - 1) - castleEnding.removedBridgeSegments);
                castleEnding.removedBridgeSegments++;
            }

            bool grounded = MarioObj.updateScriptedWalk(levelLoader.collisionObjects, camera.target.x, 112.0f);
            Vector2 pos = MarioObj.getPos();
            float targetX = pos.x - screenWidth * 0.48f;
            if (targetX < 0.0f) targetX = 0.0f;
            float maxCameraX = levelLoader.maxCameraX();
            if (maxCameraX >= 0.0f && targetX > maxCameraX) targetX = maxCameraX;
            if (targetX > camera.target.x) camera.target.x = targetX;

            if (castleEnding.timer >= 1.0f && grounded && pos.y >= MarioScriptedGroundY() - 1.0f) {
                castleEnding.state = CastleEndingState::WalkToToad;
                castleEnding.timer = 0.0f;
            }
            return;
        }

        if (castleEnding.state == CastleEndingState::WalkToToad) {
            Vector2 pos = MarioObj.getPos();
            pos.x += 112.0f * dt;
            if (pos.x >= CastleMarioToadStopX) {
                pos.x = CastleMarioToadStopX;
                castleEnding.state = CastleEndingState::Message;
                castleEnding.timer = 0.0f;
            }
            MarioObj.setScriptedPose(pos.x, MarioScriptedGroundY(), true, 3.0f);

            float targetX = pos.x - screenWidth * 0.48f;
            if (targetX < 0.0f) targetX = 0.0f;
            float maxCameraX = levelLoader.maxCameraX();
            if (maxCameraX >= 0.0f && targetX > maxCameraX) targetX = maxCameraX;
            if (targetX > camera.target.x) camera.target.x = targetX;
            return;
        }

        if (castleEnding.state == CastleEndingState::Message) {
            MarioObj.setScriptedPose(CastleMarioToadStopX, MarioScriptedGroundY(), true);
            if (castleEnding.timer >= 6.5f) {
                StartAreaIntro(LevelAreaIds::Level11);
            }
        }
    };

    auto DrawCastleBossFixtures = [&]() {
        if (levelLoader.currentArea() != LevelAreaIds::Level14) return;

        DrawTexturePro(
            spriteSheet,
            {17.0f, 314.0f, 16.0f, 16.0f},
            {CastleChainX, CastleChainY, (float)TILE_SIZE, (float)TILE_SIZE},
            {0.0f, 0.0f},
            0.0f,
            WHITE
        );

        if (!castleEnding.active()) {
            DrawTexturePro(
                spriteSheet,
                {248.0f, 460.0f, 16.0f, 16.0f},
                {CastleAxeX, CastleAxeY, (float)TILE_SIZE, (float)TILE_SIZE},
                {0.0f, 0.0f},
                0.0f,
                WHITE
            );
        }

        DrawTexturePro(
            mushroomSheet,
            {-0.0f, 444.0f, 16.0f, 24.0f},
            {CastleToadX, CastleToadGroundY - 63.0f, (float)TILE_SIZE, 63.0f},
            {0.0f, 0.0f},
            0.0f,
            WHITE
        );
    };

    auto DrawCastleEndingMessage = [&]() {
        if (castleEnding.state != CastleEndingState::Message) return;

        DrawRectangle(0, 118, screenWidth, 202, Fade(BLACK, 0.86f));
        const char* lines[] = {
            "THANK YOU MARIO!",
            "BUT PRINCESS PEACH IS IN",
            "ANOTHER CASTLE!"
        };
        int visibleLines = castleEnding.timer > 2.0f ? 3 : (castleEnding.timer > 1.0f ? 2 : 1);
        const float fontSize = 24.0f;
        const float spacing = 2.0f;
        for (int i = 0; i < visibleLines; i++) {
            Vector2 size = MeasureTextEx(nesFont, lines[i], fontSize, spacing);
            DrawTextEx(
                nesFont,
                lines[i],
                {(float)screenWidth * 0.5f - size.x * 0.5f, 152.0f + (float)i * 46.0f},
                fontSize,
                spacing,
                WHITE
            );
        }
    };

    ResetLevel();

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (!gameStarted) {
            BeginDrawing();
                if (IsKeyPressed(KEY_ENTER)) {
                    gameStarted = true;
                    sound.play(SoundCue::GameStart);
                    sound.playMusic(levelLoader.musicTrack(levelLoader.currentArea()));
                    levelIntro.start();
                }
                ClearBackground(BLACK);
                DrawTextEx(nesFont, "press enter", (Vector2){50, 50}, 36, 2, WHITE);
            EndDrawing();
        } else {
            sound.update();
            if (levelIntro.active) {
                levelIntro.update(GetFrameTime());
            } else if (!isDead) {
                if (pipeTransition.active) {
                    UpdatePipeTransition();
                } else if (level12EntranceCutscene.active) {
                    UpdateLevel12EntranceCutscene();
                } else if (castleEnding.active()) {
                    UpdateCastleEnding();
                } else {
                if (!levelLoader.hasFlagpole() || !levelLoader.castleFlagpole->isActive()) {
                    scoreboard.updateTimer(GetFrameTime());
                }
                scorePopups.update(GetFrameTime());
                bool marioWasPoweredAtFrameStart = MarioObj.getIsBig() || MarioObj.getIsFire();

                for (auto it = levelLoader.blocks.begin(); it != levelLoader.blocks.end(); ) {
                    float marioVelY = MarioObj.getVelY();
                    (*it)->update(MarioObj.returnRec(), marioVelY, MarioObj.getIsBig());
                    MarioObj.setVelY(marioVelY);
                    bool bumped = (*it)->justBumped();

                    if (bumped) {
                        Rectangle blockRec = (*it)->returnRec();
                        Rectangle hitArea = { blockRec.x, blockRec.y - 10, blockRec.width, 10 };

                        for (auto& goom : levelLoader.goombas) {
                            Rectangle goomRec = { goom->getPos().x, goom->getPos().y, 42, 42 };
                            if (CheckCollisionRecs(hitArea, goomRec)) {
                                goom->flip();
                            }
                        }
                        for (auto& koopa : levelLoader.koopas) {
                            if (CheckCollisionRecs(hitArea, koopa->returnRec())) {
                                koopa->flip();
                            }
                        }
                    }
                    
                    auto* brick = dynamic_cast<BrickBlock*>(it->get());
                    if (brick && brick->isDestroyed()) {
                        sound.play(SoundCue::BrickBreak);
                        brick->SpawnBrickParticles(brickParticles);
                        it = levelLoader.blocks.erase(it);
                        
                        levelLoader.rebuildCollisionObjects();
                    } else {
                        if (bumped) {
                            sound.play(SoundCue::BlockBump);
                        }
                        auto* pBlock = dynamic_cast<PowerUpBlock*>(it->get());
                        if (pBlock) {
                            if (bumped && pBlock->isHiddenBlock()) {
                                levelLoader.rebuildCollisionObjects();
                            }
                            if (bumped && pBlock->getItemType() == "coin") {
                                scoreboard.addCoin();
                                sound.play(SoundCue::Coin);
                            }
                            if (pBlock->justFinishedCoinAnimation()) {
                                scorePopups.spawn(200, { pBlock->returnRec().x, pBlock->returnRec().y - 8.0f });
                            }
                            auto newMush = pBlock->takeMushroom();
                            if (newMush) {
                                sound.play(SoundCue::PowerupAppears);
                                activeMushrooms.push_back(std::move(newMush));
                            }
                            auto newFlower = pBlock->takeFireFlower();
                            if (newFlower) {
                                sound.play(SoundCue::PowerupAppears);
                                activeFireFlowers.push_back(std::move(newFlower));
                            }
                        }
                        auto* coinBrick = dynamic_cast<CoinBrickBlock*>(it->get());
                        if (coinBrick) {
                            if (bumped) {
                                scoreboard.addCoin();
                                sound.play(SoundCue::Coin);
                            }
                            if (coinBrick->justFinishedCoinAnimation()) {
                                scorePopups.spawn(200, { coinBrick->returnRec().x, coinBrick->returnRec().y - 8.0f });
                            }
                        }
                        auto* starBlock = dynamic_cast<StarBrickBlock*>(it->get());
                        if (starBlock) {
                            auto newStar = starBlock->takeStar();
                            if (newStar) {
                                sound.play(SoundCue::PowerupAppears);
                                activeStars.push_back(std::move(newStar));
                            }
                        }
                        auto* mushroomBrick = dynamic_cast<MushroomBrickBlock*>(it->get());
                        if (mushroomBrick) {
                            auto newMush = mushroomBrick->takeMushroom();
                            if (newMush) {
                                sound.play(SoundCue::PowerupAppears);
                                activeMushrooms.push_back(std::move(newMush));
                            }
                            auto newFlower = mushroomBrick->takeFireFlower();
                            if (newFlower) {
                                sound.play(SoundCue::PowerupAppears);
                                activeFireFlowers.push_back(std::move(newFlower));
                            }
                        }
                        ++it;
                    }
                }

                for (auto it = levelLoader.coins.begin(); it != levelLoader.coins.end(); ) {
                    if (it->update(MarioObj.returnRec())) {
                        scoreboard.addCoin();
                        scoreboard.addScore(200);
                        sound.play(SoundCue::Coin);
                    }
                    if (it->isCollected()) it = levelLoader.coins.erase(it);
                    else ++it;
                }

                levelLoader.updateLifts(MarioObj, camera.target.x);

                for (auto it = levelLoader.goombas.begin(); it != levelLoader.goombas.end(); ) {
                    if (!MarioObj.getIsTransforming() && !MarioObj.getIsFireTransforming()) {
                        (*it)->update(levelLoader.collisionObjects, MarioObj, isDead, deathTimer, camera.target.x);
                    } 
                    if ((*it)->justDefeated()) {
                        scoreboard.addScore(100);
                        scorePopups.spawn(100, { (*it)->getPos().x, (*it)->getPos().y - 10.0f });
                        sound.play(SoundCue::EnemyDefeat);
                    }
                    if ((*it)->shouldRemove()) it = levelLoader.goombas.erase(it);
                    else ++it;
                }

                for (auto it = levelLoader.koopas.begin(); it != levelLoader.koopas.end(); ) {
                    if (!MarioObj.getIsTransforming() && !MarioObj.getIsFireTransforming()) {
                        (*it)->update(levelLoader.collisionObjects, MarioObj, isDead, deathTimer, camera.target.x);
                    }
                    if ((*it)->justDefeated()) {
                        scoreboard.addScore(100);
                        scorePopups.spawn(100, { (*it)->getPos().x, (*it)->getPos().y - 10.0f });
                        sound.play(SoundCue::EnemyDefeat);
                    }
                    if ((*it)->shouldRemove()) it = levelLoader.koopas.erase(it);
                    else ++it;
                }

                for (auto it = levelLoader.piranhaPlants.begin(); it != levelLoader.piranhaPlants.end(); ) {
                    if (!MarioObj.getIsTransforming() && !MarioObj.getIsFireTransforming()) {
                        (*it)->update(MarioObj, isDead, deathTimer, camera.target.x);
                    }
                    if ((*it)->justDefeated()) {
                        scoreboard.addScore(100);
                        scorePopups.spawn(100, { (*it)->getPos().x, (*it)->getPos().y - 10.0f });
                        sound.play(SoundCue::EnemyDefeat);
                    }
                    if ((*it)->shouldRemove()) it = levelLoader.piranhaPlants.erase(it);
                    else ++it;
                }

                if (!MarioObj.getIsTransforming() && !MarioObj.getIsFireTransforming()) {
                    for (auto& fireBar : levelLoader.fireBars) {
                        fireBar.update(MarioObj, isDead, deathTimer, camera.target.x);
                    }
                    for (auto& bowserFire : levelLoader.bowserFires) {
                        bowserFire->update(MarioObj, isDead, deathTimer, camera.target.x, (float)screenWidth);
                    }
                    for (auto it = levelLoader.bowserFires.begin(); it != levelLoader.bowserFires.end(); ) {
                        if ((*it)->shouldRemove()) it = levelLoader.bowserFires.erase(it);
                        else ++it;
                    }
                    if (bowserBoss) {
                        bowserBoss->update(levelLoader.collisionObjects, MarioObj, isDead, deathTimer, camera.target.x, activeFireballs);
                        if (bowserBoss->justDefeated()) {
                            scoreboard.addScore(5000);
                            scorePopups.spawn(5000, { CastleBowserX, CastleBowserY - 10.0f });
                            sound.play(SoundCue::BowserDefeat);
                        }
                    }
                }

                for (auto& koopa : levelLoader.koopas) {
                    if (!koopa->isMovingShell()) continue;

                    for (auto& goom : levelLoader.goombas) {
                        if (CheckCollisionRecs(koopa->returnRec(), { goom->getPos().x, goom->getPos().y, 42, 42 })) {
                            goom->flip();
                            if (goom->justDefeated()) {
                                scoreboard.addScore(100);
                                scorePopups.spawn(100, { goom->getPos().x, goom->getPos().y - 10.0f });
                                sound.play(SoundCue::EnemyDefeat);
                            }
                        }
                    }
                    for (auto& otherKoopa : levelLoader.koopas) {
                        if (otherKoopa.get() == koopa.get() || otherKoopa->isFlippedOrDead()) continue;
                        if (CheckCollisionRecs(koopa->returnRec(), otherKoopa->returnRec())) {
                            otherKoopa->hitByShell();
                            if (otherKoopa->justDefeated()) {
                                scoreboard.addScore(100);
                                scorePopups.spawn(100, { otherKoopa->getPos().x, otherKoopa->getPos().y - 10.0f });
                                sound.play(SoundCue::EnemyDefeat);
                            }
                        }
                    }
                }

                BrickBlock::updateParticles(brickParticles);
                for (auto& mush : activeMushrooms) mush->update(levelLoader.collisionObjects);
                for (auto& flower : activeFireFlowers) flower->update();
                for (auto& star : activeStars) star->update(levelLoader.collisionObjects);
                for (auto& fireball : activeFireballs) fireball->update(levelLoader.collisionObjects, camera.target.x);

                for (auto& fireball : activeFireballs) {
                    for (auto& goom : levelLoader.goombas) {
                        Rectangle goomRec = { goom->getPos().x, goom->getPos().y, 42, 42 };
                        if (CheckCollisionRecs(fireball->returnRec(), goomRec)) {
                            goom->flip();
                            if (goom->justDefeated()) {
                                scoreboard.addScore(100);
                                scorePopups.spawn(100, { goom->getPos().x, goom->getPos().y - 10.0f });
                                sound.play(SoundCue::EnemyDefeat);
                            }
                            fireball->destroy();
                        }
                    }
                    for (auto& koopa : levelLoader.koopas) {
                        if (CheckCollisionRecs(fireball->returnRec(), koopa->returnRec())) {
                            koopa->flip();
                            if (koopa->justDefeated()) {
                                scoreboard.addScore(100);
                                scorePopups.spawn(100, { koopa->getPos().x, koopa->getPos().y - 10.0f });
                                sound.play(SoundCue::EnemyDefeat);
                            }
                            fireball->destroy();
                        }
                    }
                    for (auto& plant : levelLoader.piranhaPlants) {
                        if (CheckCollisionRecs(fireball->returnRec(), plant->returnRec())) {
                            plant->defeat();
                            if (plant->justDefeated()) {
                                scoreboard.addScore(100);
                                scorePopups.spawn(100, { plant->getPos().x, plant->getPos().y - 10.0f });
                                sound.play(SoundCue::EnemyDefeat);
                            }
                            fireball->destroy();
                        }
                    }
                }

                for (auto it = activeFireballs.begin(); it != activeFireballs.end(); ) {
                    if ((*it)->shouldRemove()) it = activeFireballs.erase(it);
                    else ++it;
                }

                if (!levelLoader.hasFlagpole() || !levelLoader.castleFlagpole->isActive()) {
                    bool wasBig = MarioObj.getIsBig();
                    bool wasFire = MarioObj.getIsFire();
                    bool wasStarPowered = MarioObj.getIsStarPowered();
                    int fireballsBefore = (int)activeFireballs.size();
                    bool jumpPressed = IsKeyPressed(KEY_SPACE);
                    MarioObj.update(levelLoader.collisionObjects, camera.target.x, activeMushrooms, activeFireFlowers, activeStars, activeFireballs, mushroomSheet);
                    if (jumpPressed) {
                        sound.play(SoundCue::Jump);
                    }
                    if ((int)activeFireballs.size() > fireballsBefore) {
                        sound.play(SoundCue::Fireball);
                    }
                    int oneUps = MarioObj.takeCollectedOneUps();
                    for (int i = 0; i < oneUps; i++) {
                        marioLives++;
                        scorePopups.spawn(1, { MarioObj.getPos().x, MarioObj.getPos().y - 20.0f });
                        sound.play(SoundCue::OneUp);
                    }
                    if (!wasBig && MarioObj.getIsBig()) {
                        scoreboard.addScore(1000);
                        scorePopups.spawn(1000, { MarioObj.getPos().x, MarioObj.getPos().y - 20.0f });
                        sound.play(SoundCue::PowerupCollect);
                    }
                    if (!wasFire && MarioObj.getIsFire()) {
                        scoreboard.addScore(1000);
                        scorePopups.spawn(1000, { MarioObj.getPos().x, MarioObj.getPos().y - 20.0f });
                        sound.play(SoundCue::PowerupCollect);
                    }
                    if (!wasStarPowered && MarioObj.getIsStarPowered()) {
                        scoreboard.addScore(1000);
                        scorePopups.spawn(1000, { MarioObj.getPos().x, MarioObj.getPos().y - 20.0f });
                        sound.play(SoundCue::PowerupCollect);
                    }
                }
                if (!isDead && marioWasPoweredAtFrameStart && !MarioObj.getIsBig() && !MarioObj.getIsFire()) {
                    sound.play(SoundCue::PlayerDamage);
                }

                bool wantsDown = IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S);
                bool wantsRight = IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D);
                bool wantsLeft = IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A);
                if (levelLoader.currentArea() == LevelAreaIds::Level14 && CheckCollisionRecs(MarioObj.returnRec(), CastleAxeRec())) {
                    StartCastleEnding();
                }
                for (auto& block : levelLoader.blocks) {
                    auto* warpPipe = dynamic_cast<WarpPipeBlock*>(block.get());
                    if (warpPipe && warpPipe->canEnter(MarioObj.returnRec(), wantsDown, wantsRight, wantsLeft)) {
                        StartPipeTransition(warpPipe);
                        break;
                    }
                }

                if (levelLoader.hasFlagpole()) {
                    bool flagpoleWasActive = levelLoader.castleFlagpole->isActive();
                    levelLoader.castleFlagpole->update(MarioObj, scoreboard, scorePopups, isDead);
                    if (!flagpoleWasActive && levelLoader.castleFlagpole->isActive()) {
                        sound.play(SoundCue::Flagpole);
                    }
                }

                if (levelLoader.shouldFollowCamera()) {
                    float scrollThreshold = screenWidth / 1.967f;
                    if (MarioObj.getPos().x > scrollThreshold) {
                        float targetX = MarioObj.getPos().x - scrollThreshold;
                        float maxCameraX = levelLoader.maxCameraX();
                        if (maxCameraX >= 0.0f && targetX > maxCameraX) {
                            targetX = maxCameraX;
                        }
                        if (targetX > camera.target.x) camera.target.x = targetX;
                    }
                }

                if (MarioObj.getPos().y > 700) {
                    StartDeath();
                }
                if (levelLoader.hasFlagpole() && !levelLoader.castleFlagpole->isActive() && !levelLoader.castleFlagpole->isComplete() && scoreboard.isTimeUp()) {
                    StartDeath();
                }
                if (levelLoader.hasFlagpole() && levelLoader.castleFlagpole->isComplete() && !levelLoader.flagpoleCompleteArea().empty()) {
                    StartAreaIntro(levelLoader.flagpoleCompleteArea());
                }
                }
            } else {
                deathTimer -= GetFrameTime();
                if (deathTimer <= 0) ResetLevel();
            }

            BeginDrawing();
            if (levelIntro.active) {
                ClearBackground(BLACK);
                scoreboard.drawLevelIntro(nesFont, hudSheet, screenWidth, marioLives);
            } else {
                const SceneType& drawScene = levelLoader.drawScene();
                ClearBackground(drawScene.backgroundColor);
                BeginMode2D(camera);
                    for (auto& prop : levelLoader.levelProps) prop.draw();
                    if (levelLoader.isLevel12EntranceCutscene()) DrawLevel12EntranceCastle();
                    bool drawMarioBehindPipe = pipeTransition.active;
                    if (drawMarioBehindPipe) {
                        MarioObj.draw();
                    }
                    for (auto& plant : levelLoader.piranhaPlants) plant->draw();
                    for (auto& lift : levelLoader.lifts) lift.draw();
                    for (auto& block : levelLoader.blocks) block->draw();
                    DrawCastleBossFixtures();
                    for (auto& coin : levelLoader.coins) coin.draw();
                    for (auto& mush : activeMushrooms) mush->draw();
                    for (auto& flower : activeFireFlowers) flower->draw();
                    for (auto& star : activeStars) star->draw();
                    for (auto& fireball : activeFireballs) fireball->draw();
                    for (auto& fireBar : levelLoader.fireBars) fireBar.draw();
                    for (auto& bowserFire : levelLoader.bowserFires) bowserFire->draw();
                    if (bowserBoss) bowserBoss->draw();
                    for (auto& goom : levelLoader.goombas) goom->draw();
                    for (auto& koopa : levelLoader.koopas) koopa->draw();

                    if (levelLoader.hasFlagpole()) levelLoader.castleFlagpole->draw();

                    BrickBlock::drawParticles(brickParticles, spriteSheet, drawScene);
                    scorePopups.draw(mushroomSheet);
                    if (!drawMarioBehindPipe &&
                        (pipeTransition.active || !levelLoader.hasFlagpole() || (!levelLoader.castleFlagpole->isActive() && !levelLoader.castleFlagpole->isComplete()))) {
                        MarioObj.draw();
                    }
                EndMode2D();
                
                scoreboard.draw(nesFont, hudSheet, screenWidth);
                DrawCastleEndingMessage();
                if (isDead) {
                    DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.6f));
                    
                    const char* deathText = "SKULL EMOJI";
                    float fontSize = 30.0f;
                    float spacing = 2.0f;

                    Vector2 textSize = MeasureTextEx(nesFont, deathText, fontSize, spacing);

                    Vector2 textPos = {
                        (float)screenWidth/2 - textSize.x/2,
                        (float)screenHeight/2 - textSize.y/2
                    };

                    DrawTextEx(nesFont, deathText, textPos, fontSize, spacing, RED);
                }
            }
            EndDrawing();
        }
    }
    UnloadTexture(spriteSheet);
    UnloadTexture(marioSheet);
    UnloadTexture(mushroomSheet);
    UnloadTexture(enemiesSheet);
    UnloadTexture(hudSheet);
    UnloadFont(nesFont);
    sound.unload();
    CloseWindow();
    return 0;
}
