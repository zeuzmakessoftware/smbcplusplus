#include "sceneType.h"

namespace {
constexpr Color NES_SKY_BLUE = {92, 148, 252, 255};
constexpr Color NES_BLACK = {0, 0, 0, 255};

constexpr Rectangle Rect(float x, float y, float width = 16.0f, float height = 16.0f) {
    return {x, y, width, height};
}

constexpr SceneType MakeScene(
    SceneKind kind,
    const char* name,
    Color backgroundColor,
    float tileOffsetX,
    float tileOffsetY,
    float questionOffsetX,
    float enemyOffsetX
) {
    return {
        kind,
        name,
        backgroundColor,
        Rect(0.0f + tileOffsetX, 16.0f + tileOffsetY),
        Rect(17.0f + tileOffsetX, 16.0f + tileOffsetY),
        Rect(0.0f + tileOffsetX, 33.0f + tileOffsetY),
        Rect(349.0f + questionOffsetX, 78.0f),
        {
            Rect(298.0f + questionOffsetX, 78.0f),
            Rect(315.0f + questionOffsetX, 78.0f),
            Rect(332.0f + questionOffsetX, 78.0f),
        },
        Rect(119.0f + tileOffsetX, 196.0f + tileOffsetY),
        Rect(136.0f + tileOffsetX, 196.0f + tileOffsetY),
        Rect(119.0f + tileOffsetX, 213.0f + tileOffsetY),
        Rect(136.0f + tileOffsetX, 213.0f + tileOffsetY),
        {
            Rect(0.0f + enemyOffsetX, 16.0f),
            Rect(18.0f + enemyOffsetX, 16.0f),
        },
        Rect(36.0f + enemyOffsetX, 24.0f, 16.0f, 8.0f),
    };
}

constexpr SceneType WithPipeSources(
    SceneType scene,
    Rectangle topLeft,
    Rectangle topRight,
    Rectangle bodyLeft,
    Rectangle bodyRight
) {
    scene.pipeTopLeft = topLeft;
    scene.pipeTopRight = topRight;
    scene.pipeBodyLeft = bodyLeft;
    scene.pipeBodyRight = bodyRight;
    return scene;
}

constexpr SceneType WithBlockSources(
    SceneType scene,
    Rectangle groundBlock,
    Rectangle brickBlock,
    Rectangle solidBlock
) {
    scene.groundBlock = groundBlock;
    scene.brickBlock = brickBlock;
    scene.solidBlock = solidBlock;
    return scene;
}

constexpr SceneType OVERWORLD_SCENE = MakeScene(
    SceneKind::Overworld, "Overworld", NES_SKY_BLUE, 0.0f, 0.0f, 0.0f, 0.0f
);
constexpr SceneType UNDERGROUND_SCENE = WithPipeSources(
    WithBlockSources(
        MakeScene(SceneKind::Underground, "Underground", NES_BLACK, 147.0f, 0.0f, 96.0f, 74.0f),
        Rect(147.0f, 16.0f),
        Rect(181.0f, 16.0f),
        Rect(164.0f, 16.0f)
    ),
    Rect(283.0f, 196.0f),
    Rect(300.0f, 196.0f),
    Rect(283.0f, 213.0f),
    Rect(300.0f, 213.0f)
);
constexpr SceneType CASTLE_SCENE = MakeScene(
    SceneKind::Castle, "Castle", NES_BLACK, 0.0f, 84.0f, 96.0f * 2, 74.0f * 2
);
constexpr SceneType UNDERWATER_SCENE = WithPipeSources(
    MakeScene(SceneKind::Underwater, "Underwater", NES_SKY_BLUE, 147.0f, 84.0f, 96.0f * 3, 74.0f * 3),
    Rect(283.0f, 280.0f),
    Rect(300.0f, 280.0f),
    Rect(283.0f, 297.0f),
    Rect(300.0f, 297.0f)
);
}

const SceneType& GetSceneType(SceneKind kind) {
    switch (kind) {
        case SceneKind::Overworld:
            return OVERWORLD_SCENE;
        case SceneKind::Underground:
            return UNDERGROUND_SCENE;
        case SceneKind::Castle:
            return CASTLE_SCENE;
        case SceneKind::Underwater:
            return UNDERWATER_SCENE;
    }

    return OVERWORLD_SCENE;
}
