#include "scoreboard.h"
Scoreboard::Scoreboard(int worldNumber, int stageNumber, int startTime)
    : world(worldNumber), stage(stageNumber), time(startTime) {}

std::string Scoreboard::PadNumber(int value, int width) {
    std::string text = std::to_string(value);
    if ((int)text.length() >= width) return text;
    return std::string(width - text.length(), '0') + text;
}

void Scoreboard::reset(int startTime) {
    score = 0;
    coins = 0;
    time = startTime;
    timerAccumulator = 0.0f;
}

void Scoreboard::updateTimer(float frameTime) {
    if (time <= 0) return;

    timerAccumulator += frameTime;
    while (timerAccumulator >= nesTimerTickSeconds && time > 0) {
        timerAccumulator -= nesTimerTickSeconds;
        time--;
    }
}

void Scoreboard::addScore(int points) {
    score += points;
    if (score > maxScore) score = maxScore;
}

void Scoreboard::addCoin() {
    coins++;
    addScore(200);

    if (coins > maxCoins) {
        coins = 0;
    }
}

bool Scoreboard::convertOneTimeTickToScore(int pointsPerTick) {
    if (time <= 0) return false;

    time--;
    addScore(pointsPerTick);
    timerAccumulator = 0.0f;
    return true;
}

void Scoreboard::setLevel(int worldNumber, int stageNumber) {
    world = worldNumber;
    stage = stageNumber;
}

void Scoreboard::setTime(int startTime) {
    time = startTime;
    timerAccumulator = 0.0f;
}

bool Scoreboard::isTimeUp() const {
    return time <= 0;
}

void Scoreboard::draw(Font font, Texture2D hudSheet, int screenWidth, bool showTimeValue) const {
    const float fontSize = 22.0f;
    const float spacing = 0.67f;
    const float topY = 48.0f;
    const float valueY = 70.0f;

    const float marioX = screenWidth * 0.10f;
    const float coinX = screenWidth * 0.34f;
    const float worldX = screenWidth * 0.52f;
    const float timeX = screenWidth * 0.74f;
    const int coinFrame = ((int)(GetTime() * 8.0)) % 3;
    const Rectangle coinSource = {(float)(coinFrame * 10), 156.0f, 8.0f, 8.0f};
    const Rectangle coinDest = {coinX, valueY + 3.0f, 18.0f, 18.0f};

    DrawTextEx(font, "MARIO", {marioX, topY}, fontSize, spacing, WHITE);
    DrawTextEx(font, PadNumber(score, 6).c_str(), {marioX, valueY}, fontSize, spacing, WHITE);

    DrawTexturePro(hudSheet, coinSource, coinDest, {0.0f, 0.0f}, 0.0f, WHITE);
    DrawTextEx(font, "x", {coinX + 20.0f, valueY}, fontSize, spacing, WHITE);
    DrawTextEx(font, PadNumber(coins, 2).c_str(), {coinX + 42.0f, valueY}, fontSize, spacing, WHITE);

    DrawTextEx(font, "WORLD", {worldX, topY}, fontSize, spacing, WHITE);
    std::string levelText = std::to_string(world) + "-" + std::to_string(stage);
    DrawTextEx(font, levelText.c_str(), {worldX + 20.0f, valueY}, fontSize, spacing, WHITE);

    DrawTextEx(font, "TIME", {timeX, topY}, fontSize, spacing, WHITE);
    if (showTimeValue) {
        DrawTextEx(font, PadNumber(time, 3).c_str(), {timeX + 20.0f, valueY}, fontSize, spacing, WHITE);
    }
}

void Scoreboard::drawLevelIntro(Font font, Texture2D hudSheet, int screenWidth, int lives) const {
    draw(font, hudSheet, screenWidth, false);

    const float fontSize = 24.0f;
    const float spacing = 0.67f;
    const std::string levelText = std::to_string(world) + "-" + std::to_string(stage);
    const std::string worldText = "WORLD  " + levelText;
    const std::string livesText = "x  " + std::to_string(lives);

    Vector2 worldSize = MeasureTextEx(font, worldText.c_str(), fontSize, spacing);
    Vector2 worldPos = {(screenWidth - worldSize.x) / 2.0f, 238.0f};
    DrawTextEx(font, worldText.c_str(), worldPos, fontSize, spacing, WHITE);

    const Rectangle marioSource = {98.0f, 565.0f, 12.0f, 16.0f};
    const float marioScale = 2.0f;
    const float marioSize = 16.0f * marioScale;
    const float groupWidth = marioSize + 26.0f + MeasureTextEx(font, livesText.c_str(), fontSize, spacing).x;
    const float groupX = (screenWidth - groupWidth) / 2.0f;
    const float groupY = 320.0f;

    DrawTexturePro(
        hudSheet,
        marioSource,
        {groupX, groupY - 5.0f, marioSize - 6.7f, marioSize},
        {6.7f, 0.0f},
        0.0f,
        WHITE
    );
    DrawTextEx(font, livesText.c_str(), {groupX + marioSize + 26.0f, groupY}, fontSize, spacing, WHITE);
}
