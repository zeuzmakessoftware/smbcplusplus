#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <raylib.h>
#include <string>

class Scoreboard {
private:
    int score = 0;
    int coins = 0;
    int world = 1;
    int stage = 1;
    int time = 400;
    float timerAccumulator = 0.0f;

    static constexpr int maxScore = 999999;
    static constexpr int maxCoins = 99;
    static constexpr float nesTimerTickSeconds = 24.0f / 60.0f;

    static std::string PadNumber(int value, int width);

public:
    Scoreboard(int worldNumber = 1, int stageNumber = 1, int startTime = 400);

    void reset(int startTime = 400);
    void updateTimer(float frameTime);
    void addScore(int points);
    void addCoin();
    void setLevel(int worldNumber, int stageNumber);
    bool isTimeUp() const;

    int getScore() const { return score; }
    int getCoins() const { return coins; }
    int getWorld() const { return world; }
    int getStage() const { return stage; }
    int getTime() const { return time; }

    void draw(Font font, int screenWidth) const;
};

#endif
