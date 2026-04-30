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

void Scoreboard::setLevel(int worldNumber, int stageNumber) {
    world = worldNumber;
    stage = stageNumber;
}

bool Scoreboard::isTimeUp() const {
    return time <= 0;
}

void Scoreboard::draw(Font font, int screenWidth) const {
    const float fontSize = 22.0f;
    const float spacing = 0.67f;
    const float topY = 48.0f;
    const float valueY = 70.0f;

    const float marioX = screenWidth * 0.10f;
    const float coinX = screenWidth * 0.36f;
    const float worldX = screenWidth * 0.52f;
    const float timeX = screenWidth * 0.74f;

    DrawTextEx(font, "MARIO", {marioX, topY}, fontSize, spacing, WHITE);
    DrawTextEx(font, PadNumber(score, 6).c_str(), {marioX, valueY}, fontSize, spacing, WHITE);

    DrawTextEx(font, "x", {coinX, valueY}, fontSize, spacing, WHITE);
    DrawTextEx(font, PadNumber(coins, 2).c_str(), {coinX + 22.0f, valueY}, fontSize, spacing, WHITE);

    DrawTextEx(font, "WORLD", {worldX, topY}, fontSize, spacing, WHITE);
    std::string levelText = std::to_string(world) + "-" + std::to_string(stage);
    DrawTextEx(font, levelText.c_str(), {worldX + 20.0f, valueY}, fontSize, spacing, WHITE);

    DrawTextEx(font, "TIME", {timeX, topY}, fontSize, spacing, WHITE);
    DrawTextEx(font, PadNumber(time, 3).c_str(), {timeX + 10.0f, valueY}, fontSize, spacing, WHITE);
}
