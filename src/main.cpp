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

    std::vector<std::unique_ptr<Mushroom>> activeMushrooms;
    std::vector<std::unique_ptr<FireFlower>> activeFireFlowers;
    std::vector<std::unique_ptr<Star>> activeStars;
    std::vector<std::unique_ptr<Fireball>> activeFireballs;
    std::vector<Particle> brickParticles;
    ScorePopupManager scorePopups;
    PipeTransition pipeTransition;
    Level12EntranceCutscene level12EntranceCutscene;

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
    LevelAreaId startingArea = LevelAreaIds::Level14;
    LevelAreaId respawnArea = startingArea;

    Camera2D camera = { 0 };
    camera.target = (Vector2){ 0, 0 };
    camera.offset = (Vector2){ 0, 0 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    bool isDead = false;
    float deathTimer = 0.0f;

    auto StartDeath = [&]() {
        if (!isDead && marioLives > 0) marioLives--;
        isDead = true;
        deathTimer = 4.0f;
    };

    auto LoadArea = [&](const LevelAreaId& area, Vector2 marioStart) {
        activeMushrooms.clear();
        activeFireFlowers.clear();
        activeStars.clear();
        activeFireballs.clear();
        brickParticles.clear();

        levelLoader.load(area, marioStart, MarioObj, camera, scorePopups);
        isDead = false;
        pipeTransition.active = false;
        level12EntranceCutscene.active = levelLoader.isLevel12EntranceCutscene();
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

    ResetLevel();

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (!gameStarted) {
            BeginDrawing();
                if (IsKeyPressed(KEY_ENTER)) {
                    gameStarted = true;
                    levelIntro.start();
                }
                ClearBackground(BLACK);
                DrawTextEx(nesFont, "press enter", (Vector2){50, 50}, 36, 2, WHITE);
            EndDrawing();
        } else {
            if (levelIntro.active) {
                levelIntro.update(GetFrameTime());
            } else if (!isDead) {
                if (pipeTransition.active) {
                    UpdatePipeTransition();
                } else if (level12EntranceCutscene.active) {
                    UpdateLevel12EntranceCutscene();
                } else {
                if (!levelLoader.hasFlagpole() || !levelLoader.castleFlagpole->isActive()) {
                    scoreboard.updateTimer(GetFrameTime());
                }
                scorePopups.update(GetFrameTime());

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
                        brick->SpawnBrickParticles(brickParticles);
                        it = levelLoader.blocks.erase(it);
                        
                        levelLoader.rebuildCollisionObjects();
                    } else {
                        auto* pBlock = dynamic_cast<PowerUpBlock*>(it->get());
                        if (pBlock) {
                            if (bumped && pBlock->isHiddenBlock()) {
                                levelLoader.rebuildCollisionObjects();
                            }
                            if (bumped && pBlock->getItemType() == "coin") {
                                scoreboard.addCoin();
                            }
                            if (pBlock->justFinishedCoinAnimation()) {
                                scorePopups.spawn(200, { pBlock->returnRec().x, pBlock->returnRec().y - 8.0f });
                            }
                            auto newMush = pBlock->takeMushroom();
                            if (newMush) activeMushrooms.push_back(std::move(newMush));
                            auto newFlower = pBlock->takeFireFlower();
                            if (newFlower) activeFireFlowers.push_back(std::move(newFlower));
                        }
                        auto* coinBrick = dynamic_cast<CoinBrickBlock*>(it->get());
                        if (coinBrick) {
                            if (bumped) {
                                scoreboard.addCoin();
                            }
                            if (coinBrick->justFinishedCoinAnimation()) {
                                scorePopups.spawn(200, { coinBrick->returnRec().x, coinBrick->returnRec().y - 8.0f });
                            }
                        }
                        auto* starBlock = dynamic_cast<StarBrickBlock*>(it->get());
                        if (starBlock) {
                            auto newStar = starBlock->takeStar();
                            if (newStar) activeStars.push_back(std::move(newStar));
                        }
                        auto* mushroomBrick = dynamic_cast<MushroomBrickBlock*>(it->get());
                        if (mushroomBrick) {
                            auto newMush = mushroomBrick->takeMushroom();
                            if (newMush) activeMushrooms.push_back(std::move(newMush));
                            auto newFlower = mushroomBrick->takeFireFlower();
                            if (newFlower) activeFireFlowers.push_back(std::move(newFlower));
                        }
                        ++it;
                    }
                }

                for (auto it = levelLoader.coins.begin(); it != levelLoader.coins.end(); ) {
                    if (it->update(MarioObj.returnRec())) {
                        scoreboard.addCoin();
                        scoreboard.addScore(200);
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
                    }
                    if ((*it)->shouldRemove()) it = levelLoader.piranhaPlants.erase(it);
                    else ++it;
                }

                if (!MarioObj.getIsTransforming() && !MarioObj.getIsFireTransforming()) {
                    for (auto& fireBar : levelLoader.fireBars) {
                        fireBar.update(MarioObj, isDead, deathTimer, camera.target.x);
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
                    MarioObj.update(levelLoader.collisionObjects, camera.target.x, activeMushrooms, activeFireFlowers, activeStars, activeFireballs, mushroomSheet);
                    int oneUps = MarioObj.takeCollectedOneUps();
                    for (int i = 0; i < oneUps; i++) {
                        marioLives++;
                        scorePopups.spawn(1, { MarioObj.getPos().x, MarioObj.getPos().y - 20.0f });
                    }
                    if (!wasBig && MarioObj.getIsBig()) {
                        scoreboard.addScore(1000);
                        scorePopups.spawn(1000, { MarioObj.getPos().x, MarioObj.getPos().y - 20.0f });
                    }
                    if (!wasFire && MarioObj.getIsFire()) {
                        scoreboard.addScore(1000);
                        scorePopups.spawn(1000, { MarioObj.getPos().x, MarioObj.getPos().y - 20.0f });
                    }
                    if (!wasStarPowered && MarioObj.getIsStarPowered()) {
                        scoreboard.addScore(1000);
                        scorePopups.spawn(1000, { MarioObj.getPos().x, MarioObj.getPos().y - 20.0f });
                    }
                }

                bool wantsDown = IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S);
                bool wantsRight = IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D);
                bool wantsLeft = IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A);
                for (auto& block : levelLoader.blocks) {
                    auto* warpPipe = dynamic_cast<WarpPipeBlock*>(block.get());
                    if (warpPipe && warpPipe->canEnter(MarioObj.returnRec(), wantsDown, wantsRight, wantsLeft)) {
                        StartPipeTransition(warpPipe);
                        break;
                    }
                }

                if (levelLoader.hasFlagpole()) {
                    levelLoader.castleFlagpole->update(MarioObj, scoreboard, scorePopups, isDead);
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
                    for (auto& coin : levelLoader.coins) coin.draw();
                    for (auto& mush : activeMushrooms) mush->draw();
                    for (auto& flower : activeFireFlowers) flower->draw();
                    for (auto& star : activeStars) star->draw();
                    for (auto& fireball : activeFireballs) fireball->draw();
                    for (auto& fireBar : levelLoader.fireBars) fireBar.draw();
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
    CloseWindow();
    return 0;
}
