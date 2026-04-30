#include "castleFlagpole.h"
#include <algorithm>
#include <cmath>

CastleFlagpole::CastleFlagpole(float tileX, float groundY, Texture2D spriteSheet, Texture2D mushroomSheet, Texture2D marioSheet)
    : tileX(tileX), groundY(groundY), spriteSheet(spriteSheet), mushroomSheet(mushroomSheet), marioSheet(marioSheet) {
    reset();
}

void CastleFlagpole::reset() {
    state = State::Waiting;
    flagY = poleTopY() + TILE_SIZE;
    castleFlagY = castleFlagHiddenY();
    stateTimer = 0.0f;
    timePayoutTimer = 0.0f;
    marioVisible = true;
    levelFinished = false;
    poleBonusAwarded = 0;
}

float CastleFlagpole::poleX() const {
    return tileX * TILE_SIZE;
}

float CastleFlagpole::poleTopY() const {
    return groundY - (11.0f * TILE_SIZE);
}

float CastleFlagpole::poleBottomY() const {
    return groundY - TILE_SIZE;
}

float CastleFlagpole::castleDoorX() const {
    return (tileX + 5.85f) * TILE_SIZE;
}

float CastleFlagpole::castleFlagTargetY() const {
    return groundY - TILE_SIZE * 6.0f;
}

float CastleFlagpole::castleFlagHiddenY() const {
    return groundY - TILE_SIZE * 3.0f;
}

Rectangle CastleFlagpole::triggerRec() const {
    return { poleX() - TILE_SIZE * 0.35f, poleTopY(), TILE_SIZE * 0.9f, poleBottomY() - poleTopY() };
}

Rectangle CastleFlagpole::marioDest() const {
    const float height = bigMario ? TILE_SIZE * 2.0f : TILE_SIZE;
    return { marioX, marioY, (float)TILE_SIZE, height };
}

Rectangle CastleFlagpole::invisibleCollisionRec() const {
    return { (tileX + 1.0f) * TILE_SIZE, 0.0f, (float)TILE_SIZE, groundY };
}

int CastleFlagpole::poleBonusForCatchY(float catchY) const {
    const float normalized = (catchY - poleTopY()) / (poleBottomY() - poleTopY());
    if (normalized <= 0.12f) return 5000;
    if (normalized <= 0.32f) return 2000;
    if (normalized <= 0.55f) return 800;
    if (normalized <= 0.78f) return 400;
    return 100;
}

bool CastleFlagpole::isActive() const {
    return state != State::Waiting && state != State::Complete;
}

bool CastleFlagpole::isComplete() const {
    return levelFinished;
}

Rectangle CastleFlagpole::returnCollisionRec() const {
    return invisibleCollisionRec();
}

void CastleFlagpole::update(Mario& mario, Scoreboard& scoreboard, ScorePopupManager& scorePopups, bool& isDead) {
    if (state == State::Waiting) {
        if (!isDead && CheckCollisionRecs(mario.returnRec(), triggerRec())) {
            Rectangle marioRec = mario.returnRec();
            bigMario = mario.getIsBig();
            fireMario = mario.getIsFire();
            marioX = poleX() - TILE_SIZE * 0.18f;
            marioY = std::max(poleTopY(), std::min(marioRec.y, poleBottomY() - marioRec.height));
            flagY = poleTopY() + TILE_SIZE;
            poleBonusAwarded = poleBonusForCatchY(marioRec.y);
            scoreboard.addScore(poleBonusAwarded);
            scorePopups.spawn(poleBonusAwarded, { marioRec.x, marioRec.y - 12.0f });
            mario.setScriptedPose(marioX, marioY, false);
            state = State::Sliding;
        }
        return;
    }

    const float dt = GetFrameTime();
    stateTimer += dt;

    if (state == State::Sliding) {
        const float height = bigMario ? TILE_SIZE * 2.0f : TILE_SIZE;
        const float slideTargetY = poleBottomY() - height;
        marioY = std::min(slideTargetY, marioY + (TILE_SIZE * 5.0f * dt));
        flagY = std::min(poleBottomY() - TILE_SIZE, flagY + (TILE_SIZE * 5.0f * dt));
        mario.setScriptedPose(marioX, marioY, false);

        if (marioY >= slideTargetY - 0.5f) {
            state = State::DroppingFlag;
            stateTimer = 0.0f;
        }
    } else if (state == State::DroppingFlag) {
        flagY = std::min(poleBottomY() - TILE_SIZE, flagY + (TILE_SIZE * 5.0f * dt));
        
        const float height = bigMario ? TILE_SIZE * 2.0f : TILE_SIZE;
        const float slideTargetY = poleBottomY() - height;
 
        if (marioY >= slideTargetY - 0.5f && stateTimer >= 0.25f) {
            state = State::FacingRight;
            stateTimer = 0.0f;
            
            marioX = poleX() + TILE_SIZE * 0.55f;
            marioY = (groundY - height) - TILE_SIZE; 
            
            mario.setScriptedPose(marioX, marioY, true);
        }
    } else if (state == State::FacingRight) {
        mario.setScriptedPose(marioX, marioY, true);
        if (stateTimer >= 0.5f) {
            state = State::WalkingToCastle;
            stateTimer = 0.0f;
        }
    } else if (state == State::WalkingToCastle) {
        const float height = bigMario ? TILE_SIZE * 2.0f : TILE_SIZE;
        marioY = groundY - height; 
        
        marioX += TILE_SIZE * 3.0f * dt;
        mario.setScriptedPose(marioX, marioY, true);
        if (marioX >= castleDoorX()) {
            marioVisible = false;
            state = State::ScoringTime;
            stateTimer = 0.0f;
        }
    } else if (state == State::ScoringTime) {
        timePayoutTimer += dt;
        while (timePayoutTimer >= (2.0f / 60.0f) && state == State::ScoringTime) {
            timePayoutTimer -= (2.0f / 60.0f);
            if (!scoreboard.convertOneTimeTickToScore()) {
                state = State::RaiseFlag;
                stateTimer = 0.0f;
            }
        }
    } else if (state == State::RaiseFlag) {
        if (castleFlagY > castleFlagTargetY()) {
            castleFlagY = std::max(castleFlagTargetY(), castleFlagY - (TILE_SIZE * 2.5f * dt));

            if (castleFlagY <= castleFlagTargetY()) {
                castleFlagY = castleFlagTargetY();
                stateTimer = 0.0f; 
            }
        } 
        else {
            if (stateTimer >= 3.0f) {
                state = State::Complete;
                levelFinished = true;
            }
        }
    }
}

void CastleFlagpole::drawMarioPlaceholder(Rectangle dest) const {
    float yOffset = fireMario ? 140.0f : (bigMario ? 32.0f : 8.0f);
    float spriteHeight = bigMario ? 32.0f : 16.0f;
    Rectangle source;

    if (state == State::Sliding || state == State::DroppingFlag) {
        source = { 136.0f, yOffset, 16.0f, spriteHeight };
    } 
    else if (state == State::FacingRight) {
        source = { 136.0f, yOffset, -16.0f, spriteHeight }; 
    } 
    else if (state == State::WalkingToCastle) {
        const int frame = ((int)(GetTime() * 10.0) % 3);
        const float frameX[3] = { 20.0f, 38.0f, 56.0f };
        source = { frameX[frame], yOffset, 16.0f, spriteHeight };
    } else {
        source = { 0.0f, yOffset, 16.0f, spriteHeight };
    }

    DrawTexturePro(marioSheet, source, dest, (Vector2){ 0, 0 }, 0.0f, WHITE);
}

void CastleFlagpole::draw() const {
    //Rectangle collisionRec = invisibleCollisionRec();
    //DrawRectangleRec(collisionRec, Fade(RED, 0.30f));
    //DrawRectangleLinesEx(collisionRec, 2.0f, RED); DEBUG

    DrawTexturePro(mushroomSheet, (Rectangle){ 92.0f, 90.0f, 16.0f, 16.0f },
        (Rectangle){ poleX() - TILE_SIZE * 0.50f, flagY, TILE_SIZE, TILE_SIZE }, (Vector2){ 0, 0 }, 0.0f, WHITE);

    DrawTexturePro(mushroomSheet, (Rectangle){ 110.0f, 90.0f, 16.0f, 16.0f },
        (Rectangle){ poleX() + TILE_SIZE * 6.0f, castleFlagY, TILE_SIZE, TILE_SIZE }, (Vector2){ 0, 0 }, 0.0f, WHITE); // THE FLAG

    DrawTexturePro(spriteSheet, (Rectangle){ 136.0f, 230.0f, 16.0f, 16.0f },
        (Rectangle){ poleX(), poleTopY(), TILE_SIZE, TILE_SIZE }, (Vector2){ 0, 0 }, 0.0f, WHITE);

    for (int i = 1; i <= 9; ++i) {
        DrawTexturePro(spriteSheet, (Rectangle){ 136.0f, 247.0f, 16.0f, 16.0f },
            (Rectangle){ poleX(), poleTopY() + (i * TILE_SIZE), TILE_SIZE, TILE_SIZE }, (Vector2){ 0, 0 }, 0.0f, WHITE);
    }

    DrawTexturePro(spriteSheet, (Rectangle){ 0.0f, 33.0f, 16.0f, 16.0f },
        (Rectangle){ poleX(), groundY - TILE_SIZE, TILE_SIZE, TILE_SIZE }, (Vector2){ 0, 0 }, 0.0f, WHITE);

    DrawTexturePro(spriteSheet, (Rectangle){ 24.0f, 728.0f, 80.0f, 48.0f },
        (Rectangle){ (tileX + 4.0f) * TILE_SIZE, groundY - TILE_SIZE * 3.0f, TILE_SIZE * 5.0f, TILE_SIZE * 3.0f }, (Vector2){ 0, 0 }, 0.0f, WHITE);
    DrawTexturePro(spriteSheet, (Rectangle){ 40.0f, 696.0f, 48.0f, 32.0f },
        (Rectangle){ (tileX + 5.0f) * TILE_SIZE, groundY - TILE_SIZE * 5.0f, TILE_SIZE * 3.0f, TILE_SIZE * 2.0f }, (Vector2){ 0, 0 }, 0.0f, WHITE);

    if (isActive() && marioVisible) {
        drawMarioPlaceholder(marioDest());
    }
}
