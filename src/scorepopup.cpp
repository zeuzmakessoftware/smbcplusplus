#include "scorepopup.h"

static constexpr float kPopupLifetime = 0.67f;
static constexpr float kPopupRisePixels = 60.0f;

Rectangle ScorePopupManager::GetSourceRect(int points) {
    switch (points) {
        case 100: return { 234.0f, 26.0f, 16.0f, 8.0f };
        case 200: return { 234.0f, 36.0f, 16.0f, 8.0f };
        case 400: return { 234.0f, 46.0f, 16.0f, 8.0f };
        case 500: return { 234.0f, 56.0f, 16.0f, 8.0f };
        case 800: return { 234.0f, 66.0f, 16.0f, 8.0f };
        case 1000: return { 252.0f, 26.0f, 16.0f, 8.0f };
        case 2000: return { 252.0f, 36.0f, 16.0f, 8.0f };
        case 4000: return { 252.0f, 46.0f, 16.0f, 8.0f };
        case 5000: return { 252.0f, 56.0f, 16.0f, 8.0f };
        case 8000: return { 252.0f, 66.0f, 16.0f, 8.0f };
        case 1: return { 252.0f, 76.0f, 16.0f, 8.0f };
        default: return { 234.0f, 26.0f, 16.0f, 8.0f };
    }
}

void ScorePopupManager::spawn(int points, Vector2 pos) {
    popups.push_back({ pos, 0.0f, points });
}

void ScorePopupManager::update(float dt) {
    for (auto it = popups.begin(); it != popups.end(); ) {
        it->age += dt;
        if (it->age >= kPopupLifetime) it = popups.erase(it);
        else ++it;
    }
}

void ScorePopupManager::draw(Texture2D spriteSheet) const {
    for (const Popup& popup : popups) {
        float progress = popup.age / kPopupLifetime;
        Vector2 destPos = {
            popup.pos.x,
            popup.pos.y - (kPopupRisePixels * progress)
        };

        DrawTexturePro(
            spriteSheet,
            GetSourceRect(popup.points),
            { destPos.x, destPos.y - TILE_SIZE, TILE_SIZE, TILE_SIZE / 2 },
            { 0, 0 },
            0.0f,
            WHITE
        );
    }
}

void ScorePopupManager::clear() {
    popups.clear();
}
