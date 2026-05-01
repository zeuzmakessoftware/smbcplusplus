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
#include "fireball.h"
#include "goomba.h"
#include "levelData.h"
#include "scoreboard.h"
#include "castleFlagpole.h"
#include "scorepopup.h"

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
    ImageColorReplace(&img3, (Color){108, 106, 255, 255}, BLANK);
    Texture2D mushroomSheet = LoadTextureFromImage(img3);
    UnloadImage(img3);

    Image img4 = LoadImage("52570.png");
    ImageColorReplace(&img4, (Color){146, 144, 255, 255}, BLANK);
    Texture2D enemiesSheet = LoadTextureFromImage(img4);
    UnloadImage(img4);

    Font nesFont = LoadFontEx("super-mario-bros-nes.otf", 36, NULL, 0);
    SetTextureFilter(nesFont.texture, TEXTURE_FILTER_POINT);

    std::vector<std::unique_ptr<Block>> blocks;
    std::vector<std::unique_ptr<Goomba>> goombas;
    std::vector<Rectangle> collisionObjects;
    std::vector<std::unique_ptr<Mushroom>> activeMushrooms;
    std::vector<std::unique_ptr<FireFlower>> activeFireFlowers;
    std::vector<std::unique_ptr<Fireball>> activeFireballs;
    std::vector<Particle> brickParticles;
    std::vector<BackgroundProp> levelProps;
    std::unique_ptr<CastleFlagpole> castleFlagpole;
    ScorePopupManager scorePopups;

    Mario MarioObj(100, 0, marioSheet);
    Scoreboard scoreboard(1, 1, 400);

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
        activeFireFlowers.clear();
        activeFireballs.clear();
        brickParticles.clear();
        collisionObjects.clear();
        levelProps.clear();

        LoadLevel1(blocks, goombas, levelProps, castleFlagpole, spriteSheet, mushroomSheet, marioSheet, enemiesSheet, TILE_SIZE);

        for (auto& block : blocks) {
            collisionObjects.push_back(block->returnRec());
        }
        collisionObjects.push_back(castleFlagpole->returnCollisionRec());

        MarioObj.reset(100, 0);
        castleFlagpole->reset();
        scoreboard.reset(400);
        scorePopups.clear();
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
                DrawTextEx(nesFont, "press enter", (Vector2){50, 50}, 36, 2, WHITE);
            EndDrawing();
        } else {
            if (!isDead) {
                if (!castleFlagpole->isActive()) {
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
                        
                        collisionObjects.clear();
                        for (auto& b : blocks) collisionObjects.push_back(b->returnRec());
                        collisionObjects.push_back(castleFlagpole->returnCollisionRec());
                    } else {
                        auto* pBlock = dynamic_cast<PowerUpBlock*>(it->get());
                        if (pBlock) {
                            if (bumped && pBlock->getItemType() == "coin") {
                                scoreboard.addCoin();
                                scorePopups.spawn(200, { pBlock->returnRec().x, pBlock->returnRec().y - 8.0f });
                            }
                            auto newMush = pBlock->takeMushroom();
                            if (newMush) activeMushrooms.push_back(std::move(newMush));
                            auto newFlower = pBlock->takeFireFlower();
                            if (newFlower) activeFireFlowers.push_back(std::move(newFlower));
                        }
                        ++it;
                    }
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

                if (!castleFlagpole->isActive()) {
                    bool wasBig = MarioObj.getIsBig();
                    bool wasFire = MarioObj.getIsFire();
                    MarioObj.update(collisionObjects, camera.target.x, activeMushrooms, activeFireFlowers, activeFireballs, mushroomSheet);
                    if (!wasBig && MarioObj.getIsBig()) {
                        scoreboard.addScore(1000);
                        scorePopups.spawn(1000, { MarioObj.getPos().x, MarioObj.getPos().y - 20.0f });
                    }
                    if (!wasFire && MarioObj.getIsFire()) {
                        scoreboard.addScore(1000);
                        scorePopups.spawn(1000, { MarioObj.getPos().x, MarioObj.getPos().y - 20.0f });
                    }
                }

                castleFlagpole->update(MarioObj, scoreboard, scorePopups, isDead);

                float scrollThreshold = screenWidth / 1.967f;
                if (MarioObj.getPos().x > scrollThreshold) {
                    float targetX = MarioObj.getPos().x - scrollThreshold;
                    if (targetX > camera.target.x) camera.target.x = targetX;
                }

                if (MarioObj.getPos().y > 700) {
                    isDead = true;
                    deathTimer = 4.0f;
                }
                if (!castleFlagpole->isActive() && !castleFlagpole->isComplete() && scoreboard.isTimeUp()) {
                    isDead = true;
                    deathTimer = 4.0f;
                }
                if (castleFlagpole->isComplete()) {
                    ResetLevel();
                }
            } else {
                deathTimer -= GetFrameTime();
                if (deathTimer <= 0) ResetLevel();
            }

            BeginDrawing();
                ClearBackground(GetLevel1Scene().backgroundColor);
                BeginMode2D(camera);
                    for (auto& prop : levelProps) prop.draw();
                    for (auto& block : blocks) block->draw();
                    for (auto& mush : activeMushrooms) mush->draw();
                    for (auto& flower : activeFireFlowers) flower->draw();
                    for (auto& fireball : activeFireballs) fireball->draw();
                    for (auto& goom : goombas) goom->draw();

                    castleFlagpole->draw();

                    BrickBlock::drawParticles(brickParticles, spriteSheet, GetLevel1Scene());
                    scorePopups.draw(mushroomSheet);
                    if (!castleFlagpole->isActive() && !castleFlagpole->isComplete()) {
                        MarioObj.draw();
                    }
                EndMode2D();
                
                scoreboard.draw(nesFont, screenWidth);
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
    UnloadFont(nesFont);
    CloseWindow();
    return 0;
}
