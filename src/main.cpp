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
#include "levelData.h"
#include "scoreboard.h"
#include "castleFlagpole.h"
#include "scorepopup.h"

#define TILE_SIZE 42

enum class LevelArea {
    Overworld,
    Subarea
};

struct PipeTransition {
    bool active = false;
    WarpDestination destination = WarpDestination::None;
    Vector2 exitPosition = {0.0f, 0.0f};
    PipeOrientation orientation = PipeOrientation::Vertical;
    Vector2 startPosition = {0.0f, 0.0f};
    bool faceRight = true;
    float timer = 0.0f;
    float duration = 0.72f;
};

int main() {
    int screenWidth = 670;
    int screenHeight = 670;
    InitWindow(screenWidth, screenHeight, "Swag Bros");

    bool gameStarted = false;
    
    Image img1 = LoadImage("assets/images/52571.png");
    ImageColorReplace(&img1, (Color){148, 148, 255, 255}, BLANK);
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
    Texture2D enemiesSheet = LoadTextureFromImage(img4);
    UnloadImage(img4);

    Image hudImg = LoadImage("assets/images/56929.png");
    ImageColorReplace(&hudImg, (Color){148, 148, 255, 255}, BLANK);
    Texture2D hudSheet = LoadTextureFromImage(hudImg);
    UnloadImage(hudImg);

    Font nesFont = LoadFontEx("assets/fonts/super-mario-bros-nes.otf", 36, NULL, 0);
    SetTextureFilter(nesFont.texture, TEXTURE_FILTER_POINT);

    std::vector<std::unique_ptr<Block>> blocks;
    std::vector<std::unique_ptr<Goomba>> goombas;
    std::vector<Coin> coins;
    std::vector<Rectangle> collisionObjects;
    std::vector<std::unique_ptr<Mushroom>> activeMushrooms;
    std::vector<std::unique_ptr<FireFlower>> activeFireFlowers;
    std::vector<std::unique_ptr<Star>> activeStars;
    std::vector<std::unique_ptr<Fireball>> activeFireballs;
    std::vector<Particle> brickParticles;
    std::vector<BackgroundProp> levelProps;
    std::unique_ptr<CastleFlagpole> castleFlagpole;
    ScorePopupManager scorePopups;
    LevelArea currentArea = LevelArea::Overworld;
    PipeTransition pipeTransition;
    bool followCamera = true;

    Mario MarioObj(100, 0, marioSheet);
    Scoreboard scoreboard(1, 1, 400);

    Camera2D camera = { 0 };
    camera.target = (Vector2){ 0, 0 };
    camera.offset = (Vector2){ 0, 0 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    bool isDead = false;
    float deathTimer = 0.0f;

    auto RebuildCollisionObjects = [&]() {
        collisionObjects.clear();
        for (auto& block : blocks) {
            auto* pBlock = dynamic_cast<PowerUpBlock*>(block.get());
            if (pBlock && !pBlock->hasCollision()) {
                continue;
            }
            collisionObjects.push_back(block->returnRec());
        }
        collisionObjects.push_back(castleFlagpole->returnCollisionRec());
    };

    auto LoadArea = [&](LevelArea area, Vector2 marioStart) {
        blocks.clear();
        goombas.clear();
        coins.clear();
        activeMushrooms.clear();
        activeFireFlowers.clear();
        activeStars.clear();
        activeFireballs.clear();
        brickParticles.clear();
        levelProps.clear();
        currentArea = area;

        if (area == LevelArea::Overworld) {
            LoadLevel1(blocks, goombas, coins, levelProps, castleFlagpole, followCamera, spriteSheet, mushroomSheet, marioSheet, enemiesSheet, TILE_SIZE);
        } else {
            LoadLevel1Subarea(blocks, goombas, coins, levelProps, castleFlagpole, followCamera, spriteSheet, mushroomSheet, marioSheet, enemiesSheet, TILE_SIZE);
        }

        RebuildCollisionObjects();
        MarioObj.setScriptedPose(marioStart.x, marioStart.y, true);
        castleFlagpole->reset();
        scorePopups.clear();
        camera.target = (Vector2){
            followCamera && marioStart.x > screenWidth / 2.0f ? marioStart.x - screenWidth / 2.0f : 0.0f,
            0.0f
        };
        isDead = false;
        pipeTransition.active = false;
    };

    auto ResetLevel = [&]() {
        LoadArea(LevelArea::Overworld, (Vector2){100.0f, 0.0f});
        MarioObj.reset(100.0f, 0.0f);
        scoreboard.reset(400);
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

            if (pipeTransition.destination == WarpDestination::Level1Subarea) {
                LoadArea(LevelArea::Subarea, exitPosition);
            } else if (pipeTransition.destination == WarpDestination::Level1Overworld) {
                LoadArea(LevelArea::Overworld, exitPosition);
            }
        }
    };

    ResetLevel();

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (!gameStarted) {
            BeginDrawing();
                if (IsKeyPressed(KEY_ENTER)) gameStarted = true;
                ClearBackground(BLACK);
                DrawTextEx(nesFont, "press enter", (Vector2){50, 50}, 36, 2, WHITE);
            EndDrawing();
        } else {
            if (!isDead) {
                if (pipeTransition.active) {
                    UpdatePipeTransition();
                } else {
                if (currentArea == LevelArea::Subarea || !castleFlagpole->isActive()) {
                    scoreboard.updateTimer(GetFrameTime());
                }
                scorePopups.update(GetFrameTime());

                for (auto it = blocks.begin(); it != blocks.end(); ) {
                    float marioVelY = MarioObj.getVelY();
                    (*it)->update(MarioObj.returnRec(), marioVelY, MarioObj.getIsBig());
                    MarioObj.setVelY(marioVelY);
                    bool bumped = (*it)->justBumped();

                    if (bumped) {
                        Rectangle blockRec = (*it)->returnRec();
                        Rectangle hitArea = { blockRec.x, blockRec.y - 10, blockRec.width, 10 };

                        for (auto& goom : goombas) {
                            Rectangle goomRec = { goom->getPos().x, goom->getPos().y, 42, 42 };
                            if (CheckCollisionRecs(hitArea, goomRec)) {
                                goom->flip();
                            }
                        }
                    }
                    
                    auto* brick = dynamic_cast<BrickBlock*>(it->get());
                    if (brick && brick->isDestroyed()) {
                        brick->SpawnBrickParticles(brickParticles);
                        it = blocks.erase(it);
                        
                        RebuildCollisionObjects();
                    } else {
                        auto* pBlock = dynamic_cast<PowerUpBlock*>(it->get());
                        if (pBlock) {
                            if (bumped && pBlock->isHiddenBlock()) {
                                RebuildCollisionObjects();
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
                        auto* starBlock = dynamic_cast<StarBrickBlock*>(it->get());
                        if (starBlock) {
                            auto newStar = starBlock->takeStar();
                            if (newStar) activeStars.push_back(std::move(newStar));
                        }
                        ++it;
                    }
                }

                for (auto it = coins.begin(); it != coins.end(); ) {
                    if (it->update(MarioObj.returnRec())) {
                        scoreboard.addCoin();
                        scoreboard.addScore(200);
                        scorePopups.spawn(200, { it->returnRec().x, it->returnRec().y - 8.0f });
                    }
                    if (it->isCollected()) it = coins.erase(it);
                    else ++it;
                }

                for (auto it = goombas.begin(); it != goombas.end(); ) {
                    if (!MarioObj.getIsTransforming() && !MarioObj.getIsFireTransforming()) {
                        (*it)->update(collisionObjects, MarioObj, isDead, deathTimer, camera.target.x);
                    } 
                    if ((*it)->justDefeated()) {
                        scoreboard.addScore(100);
                        scorePopups.spawn(100, { (*it)->getPos().x, (*it)->getPos().y - 10.0f });
                    }
                    if ((*it)->shouldRemove()) it = goombas.erase(it);
                    else ++it;
                }

                BrickBlock::updateParticles(brickParticles);
                for (auto& mush : activeMushrooms) mush->update(collisionObjects);
                for (auto& flower : activeFireFlowers) flower->update();
                for (auto& star : activeStars) star->update(collisionObjects);
                for (auto& fireball : activeFireballs) fireball->update(collisionObjects, camera.target.x);

                for (auto& fireball : activeFireballs) {
                    for (auto& goom : goombas) {
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
                }

                for (auto it = activeFireballs.begin(); it != activeFireballs.end(); ) {
                    if ((*it)->shouldRemove()) it = activeFireballs.erase(it);
                    else ++it;
                }

                if (currentArea == LevelArea::Subarea || !castleFlagpole->isActive()) {
                    bool wasBig = MarioObj.getIsBig();
                    bool wasFire = MarioObj.getIsFire();
                    bool wasStarPowered = MarioObj.getIsStarPowered();
                    MarioObj.update(collisionObjects, camera.target.x, activeMushrooms, activeFireFlowers, activeStars, activeFireballs, mushroomSheet);
                    int oneUps = MarioObj.takeCollectedOneUps();
                    for (int i = 0; i < oneUps; i++) {
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
                for (auto& block : blocks) {
                    auto* warpPipe = dynamic_cast<WarpPipeBlock*>(block.get());
                    if (warpPipe && warpPipe->canEnter(MarioObj.returnRec(), wantsDown, wantsRight, wantsLeft)) {
                        StartPipeTransition(warpPipe);
                        break;
                    }
                }

                if (currentArea == LevelArea::Overworld) {
                    castleFlagpole->update(MarioObj, scoreboard, scorePopups, isDead);
                }

                if (followCamera) {
                    float scrollThreshold = screenWidth / 1.967f;
                    if (MarioObj.getPos().x > scrollThreshold) {
                        float targetX = MarioObj.getPos().x - scrollThreshold;
                        if (currentArea == LevelArea::Subarea && targetX > (32 * TILE_SIZE) - screenWidth) {
                            targetX = (32 * TILE_SIZE) - screenWidth;
                        }
                        if (targetX > camera.target.x) camera.target.x = targetX;
                    }
                }

                if (MarioObj.getPos().y > 700) {
                    isDead = true;
                    deathTimer = 4.0f;
                }
                if (currentArea == LevelArea::Overworld && !castleFlagpole->isActive() && !castleFlagpole->isComplete() && scoreboard.isTimeUp()) {
                    isDead = true;
                    deathTimer = 4.0f;
                }
                if (currentArea == LevelArea::Overworld && castleFlagpole->isComplete()) {
                    ResetLevel();
                }
                }
            } else {
                deathTimer -= GetFrameTime();
                if (deathTimer <= 0) ResetLevel();
            }

            BeginDrawing();
                const SceneType& drawScene = currentArea == LevelArea::Subarea ? GetSceneType(SceneKind::Underground) : GetLevel1Scene();
                ClearBackground(drawScene.backgroundColor);
                BeginMode2D(camera);
                    for (auto& prop : levelProps) prop.draw();
                    bool drawMarioBehindPipe = pipeTransition.active;
                    if (drawMarioBehindPipe) {
                        MarioObj.draw();
                    }
                    for (auto& block : blocks) block->draw();
                    for (auto& coin : coins) coin.draw();
                    for (auto& mush : activeMushrooms) mush->draw();
                    for (auto& flower : activeFireFlowers) flower->draw();
                    for (auto& star : activeStars) star->draw();
                    for (auto& fireball : activeFireballs) fireball->draw();
                    for (auto& goom : goombas) goom->draw();

                    if (currentArea == LevelArea::Overworld) castleFlagpole->draw();

                    BrickBlock::drawParticles(brickParticles, spriteSheet, drawScene);
                    scorePopups.draw(mushroomSheet);
                    if (!drawMarioBehindPipe &&
                        (pipeTransition.active || currentArea == LevelArea::Subarea || (!castleFlagpole->isActive() && !castleFlagpole->isComplete()))) {
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
