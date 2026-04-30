#ifndef SCOREPOPUP_H
#define SCOREPOPUP_H

#include <raylib.h>
#include <vector>

#define TILE_SIZE 42

class ScorePopupManager {
private:
    struct Popup {
        Vector2 pos;
        float age = 0.0f;
        int points = 0;
    };

    std::vector<Popup> popups;

    static Rectangle GetSourceRect(int points);

public:
    void spawn(int points, Vector2 pos);
    void update(float dt);
    void draw(Texture2D spriteSheet) const;
    void clear();
};

#endif
