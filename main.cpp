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
#include "levelData.h"

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

        LoadLevel1(blocks, goombas, levelProps, spriteSheet, mushroomSheet, enemiesSheet, TILE_SIZE);

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