#include <raylib.h>
#include <raymath.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
#include "backgroundProp.h"
#include "blocks.h"

enum class ObjectType {
    BackgroundProp,
    Block,
    Goomba,
    Koopa,
    Ground,
    Coin,
    CoinBlock,
    MushroomBlock,
    FireFlowerBlock,
    OneUpBlock,
    Pipe,
    WarpPipe,
    PipeWall,
    CastleScenery,
    FlagPole
};

struct LevelObject {
    ObjectType type;
    int x;
    int y;
    int w = TILE_SIZE;
    int h = TILE_SIZE;
    int pipeWide = 2;
    int pipeHigh = 2;
    int propIndex = 0;
    int blockIndex = 0;
    PipeOrientation pipeOrientation = PipeOrientation::Vertical;
};

struct PaletteItem {
    LevelObject object;
    std::string label;
    std::string category;
};

static const int OBJECT_GRID_OFFSET_Y = -72;
static const int BLOCK_GRID_OFFSET_Y = 12;
static const int BLOCK_GRID_DRAW_OFFSET_Y = OBJECT_GRID_OFFSET_Y + 12;
static const float DRAG_START_DISTANCE = 2.0f;
static const int PALETTE_HEIGHT = 304;
static const int PALETTE_CELL_W = 78;
static const int PALETTE_CELL_H = 74;

static constexpr SceneKind SCENE_KINDS[] = {
    SceneKind::Overworld,
    SceneKind::Underground,
    SceneKind::Castle,
    SceneKind::Underwater
};

static const int SCENE_KIND_COUNT = sizeof(SCENE_KINDS) / sizeof(SCENE_KINDS[0]);

static const char* TypeName(ObjectType type) {
    switch (type) {
        case ObjectType::BackgroundProp: return "Background Prop";
        case ObjectType::Block: return "Block";
        case ObjectType::Goomba: return "Goomba";
        case ObjectType::Koopa: return "Koopa";
        case ObjectType::Ground: return "Ground";
        case ObjectType::Coin: return "Coin";
        case ObjectType::CoinBlock: return "Coin Block";
        case ObjectType::MushroomBlock: return "Mushroom Block";
        case ObjectType::FireFlowerBlock: return "Fire Flower Block";
        case ObjectType::OneUpBlock: return "1-Up Block";
        case ObjectType::Pipe: return "Pipe";
        case ObjectType::WarpPipe: return "Warp Pipe";
        case ObjectType::PipeWall: return "Pipe Wall";
        case ObjectType::CastleScenery: return "Castle";
        case ObjectType::FlagPole: return "Flag Pole";
    }
    return "Unknown";
}

static std::string SceneExpr(SceneKind kind) {
    switch (kind) {
        case SceneKind::Overworld: return "GetSceneType(SceneKind::Overworld)";
        case SceneKind::Underground: return "GetSceneType(SceneKind::Underground)";
        case SceneKind::Castle: return "GetSceneType(SceneKind::Castle)";
        case SceneKind::Underwater: return "GetSceneType(SceneKind::Underwater)";
    }
    return "GetSceneType(SceneKind::Overworld)";
}

static std::string PipeOrientationExpr(PipeOrientation orientation) {
    switch (orientation) {
        case PipeOrientation::Vertical: return "PipeOrientation::Vertical";
        case PipeOrientation::HorizontalRight: return "PipeOrientation::HorizontalRight";
        case PipeOrientation::HorizontalLeft: return "PipeOrientation::HorizontalLeft";
    }
    return "PipeOrientation::Vertical";
}

static PipeOrientation ReadPipeOrientation(const std::string& text) {
    if (text.find("HorizontalRight") != std::string::npos) return PipeOrientation::HorizontalRight;
    if (text.find("HorizontalLeft") != std::string::npos) return PipeOrientation::HorizontalLeft;
    return PipeOrientation::Vertical;
}

static int SceneIndex(SceneKind kind) {
    for (int i = 0; i < SCENE_KIND_COUNT; i++) {
        if (SCENE_KINDS[i] == kind) return i;
    }
    return 0;
}

static SceneKind NextSceneKind(SceneKind kind, int direction) {
    int index = SceneIndex(kind);
    return SCENE_KINDS[(index + direction + SCENE_KIND_COUNT) % SCENE_KIND_COUNT];
}

static const BackgroundPropDefinition& PropDefinitionFor(const LevelObject& obj) {
    const std::vector<BackgroundPropDefinition>& props = GetBackgroundPropDefinitions();
    int index = std::max(0, std::min(obj.propIndex, (int)props.size() - 1));
    return props[index];
}

static const char* ObjectName(const LevelObject& obj) {
    if (obj.type == ObjectType::BackgroundProp) {
        return PropDefinitionFor(obj).displayName;
    }
    if (obj.type == ObjectType::Block) {
        const std::vector<BlockDefinition>& blocks = GetBlockDefinitions();
        int index = std::max(0, std::min(obj.blockIndex, (int)blocks.size() - 1));
        return blocks[index].displayName;
    }
    return TypeName(obj.type);
}

static bool IsProp(ObjectType type) {
    return type == ObjectType::BackgroundProp;
}

static LevelObject MakePropObject(int propIndex, int x, int y) {
    LevelObject obj = {ObjectType::BackgroundProp, x, y};
    obj.propIndex = propIndex;
    return obj;
}

static int PropIndexForLayoutName(const std::string& layoutName) {
    const std::vector<BackgroundPropDefinition>& props = GetBackgroundPropDefinitions();
    for (int i = 0; i < (int)props.size(); i++) {
        if (layoutName.find(props[i].layoutName) != std::string::npos) {
            return i;
        }
    }
    return 0;
}

static const BlockDefinition& BlockDefinitionFor(const LevelObject& obj) {
    const std::vector<BlockDefinition>& blocks = GetBlockDefinitions();
    int index = std::max(0, std::min(obj.blockIndex, (int)blocks.size() - 1));
    return blocks[index];
}

static LevelObject MakeBlockObject(int blockIndex, int x, int y) {
    LevelObject obj = {ObjectType::Block, x, y};
    obj.blockIndex = blockIndex;
    return obj;
}

static int BlockIndexForClassName(const std::string& className) {
    const std::vector<BlockDefinition>& blocks = GetBlockDefinitions();
    for (int i = 0; i < (int)blocks.size(); i++) {
        if (className.find(blocks[i].className) != std::string::npos) {
            return i;
        }
    }
    return 0;
}

static Rectangle ObjectBounds(const LevelObject& obj) {
    if (IsProp(obj.type)) {
        int maxX = 1;
        int maxY = 1;
        for (const SpritePart& part : *PropDefinitionFor(obj).layout) {
            maxX = std::max(maxX, (int)part.offset.x + 1);
            maxY = std::max(maxY, (int)part.offset.y + 1);
        }
        return {(float)obj.x, (float)obj.y, (float)(maxX * TILE_SIZE), (float)(maxY * TILE_SIZE)};
    }
    if (obj.type == ObjectType::Ground) return {(float)obj.x, (float)obj.y, (float)obj.w, (float)obj.h};
    if (obj.type == ObjectType::Pipe || obj.type == ObjectType::WarpPipe) {
        return {(float)obj.x, (float)obj.y, (float)(obj.pipeWide * TILE_SIZE), (float)(obj.pipeHigh * TILE_SIZE)};
    }
    if (obj.type == ObjectType::PipeWall) {
        return {(float)obj.x, (float)obj.y, (float)TILE_SIZE, (float)(obj.pipeHigh * TILE_SIZE)};
    }
    if (obj.type == ObjectType::CastleScenery) {
        return {(float)obj.x, (float)obj.y, (float)(TILE_SIZE * 5), (float)(TILE_SIZE * 5)};
    }
    if (obj.type == ObjectType::Koopa) return {(float)obj.x, (float)obj.y, (float)TILE_SIZE, (float)(TILE_SIZE * 1.5f)};
    if (obj.type == ObjectType::FlagPole) return {(float)obj.x, (float)obj.y - TILE_SIZE * 11.0f, (float)(TILE_SIZE * 9), (float)(TILE_SIZE * 11)};
    return {(float)obj.x, (float)obj.y, (float)TILE_SIZE, (float)TILE_SIZE};
}

static int Snap(float value, int gridSize) {
    return (int)std::round(value / gridSize) * gridSize;
}

static int SnapWithOffset(float value, int gridSize, int offset) {
    return offset + (int)std::round((value - offset) / gridSize) * gridSize;
}

static int FirstGridLine(int minValue, int gridSize, int offset = 0) {
    return offset + (int)std::floor((float)(minValue - offset) / gridSize) * gridSize;
}

static int SnapXForType(ObjectType type, float value) {
    (void)type;
    return Snap(value, TILE_SIZE);
}

static int SnapYForType(ObjectType type, float value) {
    if (type == ObjectType::Goomba) {
        return Snap(value, TILE_SIZE);
    }
    if (type == ObjectType::Koopa) {
        return SnapWithOffset(value, TILE_SIZE, -9);
    }
    if (type == ObjectType::Block || type == ObjectType::CoinBlock ||
        type == ObjectType::MushroomBlock || type == ObjectType::FireFlowerBlock ||
        type == ObjectType::OneUpBlock || type == ObjectType::Pipe ||
        type == ObjectType::WarpPipe || type == ObjectType::PipeWall || type == ObjectType::Coin) {
        return SnapWithOffset(value, TILE_SIZE, BLOCK_GRID_OFFSET_Y);
    }
    return SnapWithOffset(value, TILE_SIZE, OBJECT_GRID_OFFSET_Y);
}

static void SnapObject(LevelObject& obj) {
    obj.x = SnapXForType(obj.type, obj.x);
    obj.y = SnapYForType(obj.type, obj.y);
    if (obj.type == ObjectType::Ground) {
        obj.w = std::max(TILE_SIZE, Snap(obj.w, TILE_SIZE));
        obj.h = std::max(TILE_SIZE, Snap(obj.h, TILE_SIZE));
    }
    if (obj.type == ObjectType::Pipe || obj.type == ObjectType::WarpPipe || obj.type == ObjectType::PipeWall) {
        obj.pipeWide = std::max(1, obj.pipeWide);
        obj.pipeHigh = std::max(1, obj.pipeHigh);
    }
}

static void DrawSpritePart(Texture2D texture, Rectangle src, Rectangle dest) {
    DrawTexturePro(texture, src, dest, {0, 0}, 0.0f, WHITE);
}

static void DrawProp(const LevelObject& obj, Texture2D spriteSheet) {
    for (const SpritePart& part : *PropDefinitionFor(obj).layout) {
        DrawSpritePart(spriteSheet, part.source,
            {(float)obj.x + part.offset.x * TILE_SIZE, (float)obj.y + part.offset.y * TILE_SIZE, TILE_SIZE, TILE_SIZE});
    }
}

static Rectangle BlockSourceFor(const BlockDefinition& block, const SceneType& scene) {
    std::string className = block.className;
    if (className == "BrickBlock" || className == "StarBrickBlock") return scene.brickBlock;
    if (className == "EmptyBlock") return scene.emptyBlock;
    if (className == "ShinyBlock") return scene.solidBlock;
    return block.source;
}

static void DrawGround(const LevelObject& obj, Texture2D spriteSheet, const SceneType& scene) {
    for (int y = obj.y; y < obj.y + obj.h; y += TILE_SIZE) {
        for (int x = obj.x; x < obj.x + obj.w; x += TILE_SIZE) {
            DrawSpritePart(spriteSheet, scene.groundBlock, {(float)x, (float)y, TILE_SIZE, TILE_SIZE});
        }
    }
}

static void DrawPipe(const LevelObject& obj, Texture2D spriteSheet, const SceneType& scene) {
    if (obj.pipeOrientation != PipeOrientation::Vertical) {
        for (int i = 0; i < obj.pipeWide; i++) {
            for (int j = 0; j < obj.pipeHigh; j++) {
                Rectangle src;
                if (i == 0) {
                    src = (j == 0) ? (Rectangle){249.0f, 230.0f, 16.0f, 16.0f}
                                   : (Rectangle){249.0f, 247.0f, 16.0f, 16.0f};
                } else {
                    src = (j == 0) ? (Rectangle){266.0f, 230.0f, 16.0f, 16.0f}
                                   : (Rectangle){266.0f, 247.0f, 16.0f, 16.0f};
                }

                float destX = (float)obj.x + i * TILE_SIZE;
                if (obj.pipeOrientation == PipeOrientation::HorizontalLeft) {
                    src.width = -src.width;
                    destX = (float)obj.x + (obj.pipeWide - 1 - i) * TILE_SIZE;
                }
                DrawSpritePart(spriteSheet, src,
                    {destX, (float)obj.y + j * TILE_SIZE, TILE_SIZE, TILE_SIZE});
            }
        }
        return;
    }

    for (int i = 0; i < obj.pipeWide; i++) {
        for (int j = 0; j < obj.pipeHigh; j++) {
            Rectangle src;
            if (j == 0) src = (i == 0) ? scene.pipeTopLeft : scene.pipeTopRight;
            else src = (i == 0) ? scene.pipeBodyLeft : scene.pipeBodyRight;
            DrawSpritePart(spriteSheet, src,
                {(float)obj.x + i * TILE_SIZE, (float)obj.y + j * TILE_SIZE, TILE_SIZE, TILE_SIZE});
        }
    }
}

static void DrawPipeWall(const LevelObject& obj, Texture2D spriteSheet) {
    for (int j = 0; j < obj.pipeHigh; j++) {
        Rectangle src = {119.0f, 213.0f, 16.0f, 16.0f};
        if (j == obj.pipeHigh - 2) {
            src = {119.0f, 230.0f, 16.0f, 16.0f};
        } else if (j == obj.pipeHigh - 1) {
            src = {119.0f, 247.0f, 16.0f, 16.0f};
        }
        DrawSpritePart(spriteSheet, src,
            {(float)obj.x, (float)obj.y + j * TILE_SIZE, TILE_SIZE, TILE_SIZE});
    }
}

static void DrawFlagPole(const LevelObject& obj, Texture2D spriteSheet, Texture2D mushroomSheet) {
    const float groundY = (float)obj.y;
    const float poleX = (float)obj.x;
    const float poleTopY = groundY - (11.0f * TILE_SIZE);

    DrawSpritePart(mushroomSheet, {92.0f, 90.0f, 16.0f, 16.0f},
        {poleX - TILE_SIZE * 0.50f, poleTopY + TILE_SIZE, TILE_SIZE, TILE_SIZE});
    DrawSpritePart(spriteSheet, {136.0f, 230.0f, 16.0f, 16.0f},
        {poleX, poleTopY, TILE_SIZE, TILE_SIZE});
    for (int i = 1; i <= 9; ++i) {
        DrawSpritePart(spriteSheet, {136.0f, 247.0f, 16.0f, 16.0f},
            {poleX, poleTopY + (i * TILE_SIZE), TILE_SIZE, TILE_SIZE});
    }
    DrawSpritePart(spriteSheet, {0.0f, 33.0f, 16.0f, 16.0f},
        {poleX, groundY - TILE_SIZE, TILE_SIZE, TILE_SIZE});
    DrawSpritePart(spriteSheet, {24.0f, 728.0f, 80.0f, 48.0f},
        {poleX + TILE_SIZE * 4.0f, groundY - TILE_SIZE * 3.0f, TILE_SIZE * 5.0f, TILE_SIZE * 3.0f});
    DrawSpritePart(spriteSheet, {40.0f, 696.0f, 48.0f, 32.0f},
        {poleX + TILE_SIZE * 5.0f, groundY - TILE_SIZE * 5.0f, TILE_SIZE * 3.0f, TILE_SIZE * 2.0f});
}

static void DrawCastleScenery(const LevelObject& obj, Texture2D spriteSheet) {
    DrawSpritePart(spriteSheet, {24.0f, 696.0f, 80.0f, 80.0f},
        {(float)obj.x, (float)obj.y, TILE_SIZE * 5.0f, TILE_SIZE * 5.0f});
}

static void DrawObject(const LevelObject& obj, Texture2D spriteSheet, Texture2D mushroomSheet, Texture2D enemiesSheet, const SceneType& scene) {
    switch (obj.type) {
        case ObjectType::BackgroundProp:
            DrawProp(obj, spriteSheet);
            break;
        case ObjectType::Goomba:
            DrawSpritePart(enemiesSheet, scene.goombaFrames[0], {(float)obj.x, (float)obj.y, TILE_SIZE, TILE_SIZE});
            break;
        case ObjectType::Koopa:
            DrawSpritePart(enemiesSheet, scene.koopaFrames[0], {(float)obj.x, (float)obj.y, TILE_SIZE, TILE_SIZE * 1.5f});
            break;
        case ObjectType::Ground:
            DrawGround(obj, spriteSheet, scene);
            break;
        case ObjectType::Coin:
            DrawSpritePart(mushroomSheet, {180, 36, 8, 16}, {(float)obj.x + 10, (float)obj.y, 22, TILE_SIZE});
            break;
        case ObjectType::Block:
            DrawSpritePart(spriteSheet, BlockSourceFor(BlockDefinitionFor(obj), scene), {(float)obj.x, (float)obj.y, TILE_SIZE, TILE_SIZE});
            break;
        case ObjectType::CoinBlock:
            DrawSpritePart(spriteSheet, scene.questionBlockFrames[0], {(float)obj.x, (float)obj.y, TILE_SIZE, TILE_SIZE});
            break;
        case ObjectType::MushroomBlock:
            DrawSpritePart(spriteSheet, scene.questionBlockFrames[0], {(float)obj.x, (float)obj.y, TILE_SIZE, TILE_SIZE});
            DrawSpritePart(mushroomSheet, {0, 8, 16, 16}, {(float)obj.x + 9, (float)obj.y - 18, 24, 24});
            break;
        case ObjectType::FireFlowerBlock:
            DrawSpritePart(spriteSheet, scene.questionBlockFrames[0], {(float)obj.x, (float)obj.y, TILE_SIZE, TILE_SIZE});
            DrawSpritePart(mushroomSheet, {32, 44, 16, 16}, {(float)obj.x + 9, (float)obj.y - 18, 24, 24});
            break;
        case ObjectType::OneUpBlock:
            DrawSpritePart(spriteSheet, scene.questionBlockFrames[0], {(float)obj.x, (float)obj.y, TILE_SIZE, TILE_SIZE});
            DrawSpritePart(mushroomSheet, {0, 8, 16, 16}, {(float)obj.x + 9, (float)obj.y - 18, 24, 24});
            DrawRectangleLinesEx({(float)obj.x + 6, (float)obj.y + 6, TILE_SIZE - 12.0f, TILE_SIZE - 12.0f}, 2.0f, Fade(LIME, 0.9f));
            break;
        case ObjectType::Pipe:
        case ObjectType::WarpPipe:
            DrawPipe(obj, spriteSheet, scene);
            if (obj.type == ObjectType::WarpPipe) {
                DrawCircle(obj.x + obj.pipeWide * TILE_SIZE * 0.5f, obj.y + 10.0f, 8.0f, Fade(YELLOW, 0.8f));
            }
            break;
        case ObjectType::PipeWall:
            DrawPipeWall(obj, spriteSheet);
            break;
        case ObjectType::CastleScenery:
            DrawCastleScenery(obj, spriteSheet);
            break;
        case ObjectType::FlagPole:
            DrawFlagPole(obj, spriteSheet, mushroomSheet);
            break;
    }
}

static void LoadDefaultLevel(std::vector<LevelObject>& objects) {
    objects = {
        {ObjectType::Goomba, 22 * TILE_SIZE, 14 * TILE_SIZE},
        {ObjectType::Goomba, 32 * TILE_SIZE, 14 * TILE_SIZE},
        {ObjectType::Ground, 0, 600, 2000, 80},
    };

}

static std::string Expr(int value) {
    if (value % TILE_SIZE == 0) return "(" + std::to_string(value / TILE_SIZE) + " * TILE_SIZE)";
    int base = value - 12;
    if (base % TILE_SIZE == 0) return "(" + std::to_string(base / TILE_SIZE) + " * TILE_SIZE) + 12";
    return std::to_string(value);
}

static void PrintLevelCode(const std::vector<LevelObject>& objects, SceneKind sceneKind) {
    const std::string sceneExpr = SceneExpr(sceneKind);
    std::cout << "\n// --- Level Editor Output ---\n";
    for (const LevelObject& obj : objects) {
        if (IsProp(obj.type)) {
            std::cout << "levelProps.push_back(BackgroundProp(" << obj.x << ", " << obj.y
                      << ", spriteSheet, " << PropDefinitionFor(obj).layoutName << "));\n";
        }
    }
    std::cout << "\n";
    for (const LevelObject& obj : objects) {
        if (obj.type == ObjectType::Goomba) {
            std::cout << "goombas.push_back(std::make_unique<Goomba>(" << Expr(obj.x)
                      << ", " << Expr(obj.y) << ", enemiesSheet, " << sceneExpr << "));\n";
        } else if (obj.type == ObjectType::Koopa) {
            std::cout << "koopas.push_back(std::make_unique<Koopa>(" << Expr(obj.x)
                      << ", " << Expr(obj.y) << ", enemiesSheet, " << sceneExpr << "));\n";
        } else if (obj.type == ObjectType::Coin) {
            std::cout << "coins.emplace_back((float)" << Expr(obj.x)
                      << ", (float)" << Expr(obj.y) << ", mushroomSheet);\n";
        }
    }
    std::cout << "\n";
    for (const LevelObject& obj : objects) {
        switch (obj.type) {
            case ObjectType::Ground:
                std::cout << "blocks.push_back(std::make_unique<DrawTiledRect>(\n"
                          << "    " << obj.x << ", " << obj.y << ", " << obj.w << ", " << obj.h
                          << ", spriteSheet, " << sceneExpr << ".groundBlock, TILE_SIZE, TILE_SIZE, "
                          << sceneExpr << "\n));\n";
                break;
            case ObjectType::Block:
                if (std::string(BlockDefinitionFor(obj).className) == "StarBrickBlock") {
                    std::cout << "blocks.push_back(std::make_unique<StarBrickBlock>(" << Expr(obj.x)
                              << ", " << Expr(obj.y) << ", spriteSheet, mushroomSheet, "
                              << sceneExpr << "));\n";
                } else {
                    std::cout << "blocks.push_back(std::make_unique<" << BlockDefinitionFor(obj).className
                              << ">(" << Expr(obj.x) << ", " << Expr(obj.y) << ", spriteSheet, "
                              << sceneExpr << "));\n";
                }
                break;
            case ObjectType::CoinBlock:
                std::cout << "blocks.push_back(std::make_unique<PowerUpBlock>(" << Expr(obj.x)
                          << ", " << Expr(obj.y) << ", spriteSheet, mushroomSheet, \"coin\", "
                          << sceneExpr << "));\n";
                break;
            case ObjectType::MushroomBlock:
                std::cout << "blocks.push_back(std::make_unique<PowerUpBlock>(" << Expr(obj.x)
                          << ", " << Expr(obj.y) << ", spriteSheet, mushroomSheet, \"mushroom\", "
                          << sceneExpr << "));\n";
                break;
            case ObjectType::FireFlowerBlock:
                std::cout << "blocks.push_back(std::make_unique<PowerUpBlock>(" << Expr(obj.x)
                          << ", " << Expr(obj.y) << ", spriteSheet, mushroomSheet, \"fireflower\", "
                          << sceneExpr << "));\n";
                break;
            case ObjectType::OneUpBlock:
                std::cout << "blocks.push_back(std::make_unique<PowerUpBlock>(" << Expr(obj.x)
                          << ", " << Expr(obj.y) << ", spriteSheet, mushroomSheet, \"1up\", "
                          << sceneExpr << "));\n";
                break;
            case ObjectType::Pipe:
                std::cout << "blocks.push_back(std::make_unique<PipeBlock>(" << Expr(obj.x)
                          << ", " << Expr(obj.y) << ", " << obj.pipeWide << ", " << obj.pipeHigh
                          << ", spriteSheet, " << sceneExpr;
                if (obj.pipeOrientation != PipeOrientation::Vertical) {
                    std::cout << ", " << PipeOrientationExpr(obj.pipeOrientation);
                }
                std::cout << "));\n";
                break;
            case ObjectType::WarpPipe:
                std::cout << "blocks.push_back(std::make_unique<WarpPipeBlock>(\n"
                          << "    " << Expr(obj.x) << ", " << Expr(obj.y) << ", " << obj.pipeWide << ", " << obj.pipeHigh
                          << ", spriteSheet,\n"
                          << "    WarpDestination::Level1Subarea, (Vector2){ (2.0f * TILE_SIZE) + 4.0f, (2.0f * TILE_SIZE) + 4.0f },\n"
                          << "    " << sceneExpr;
                if (obj.pipeOrientation != PipeOrientation::Vertical) {
                    std::cout << ", " << PipeOrientationExpr(obj.pipeOrientation);
                }
                std::cout << "\n));\n";
                break;
            case ObjectType::PipeWall:
                std::cout << "blocks.push_back(std::make_unique<PipeWallBlock>(" << Expr(obj.x)
                          << ", " << Expr(obj.y) << ", " << obj.pipeHigh << ", spriteSheet, "
                          << sceneExpr << "));\n";
                break;
            default:
                break;
        }
    }
    for (const LevelObject& obj : objects) {
        if (obj.type == ObjectType::FlagPole) {
            std::cout << "castleFlagpole = std::make_unique<CastleFlagpole>("
                      << (obj.x / (float)TILE_SIZE) << "f, "
                      << (float)obj.y << "f, spriteSheet, mushroomSheet, marioSheet);\n";
        } else if (obj.type == ObjectType::CastleScenery) {
            std::cout << "// Castle scenery: DrawTexturePro(spriteSheet, (Rectangle){24.0f, 696.0f, 80.0f, 80.0f}, "
                      << "(Rectangle){" << (float)obj.x << "f, " << (float)obj.y << "f, "
                      << (float)(TILE_SIZE * 5) << "f, " << (float)(TILE_SIZE * 5)
                      << "f}, (Vector2){0, 0}, 0.0f, WHITE);\n";
        }
    }
    std::cout << "// --- End Level Editor Output ---\n" << std::flush;
}

static int ReadExpr(const std::string& text) {
    std::smatch match;
    if (std::regex_search(text, match, std::regex(R"((\d+)\s*\*\s*TILE_SIZE\)\s*\+\s*(\d+))"))) {
        return std::stoi(match[1]) * TILE_SIZE + std::stoi(match[2]);
    }
    if (std::regex_search(text, match, std::regex(R"((\d+)\s*\*\s*TILE_SIZE)"))) {
        return std::stoi(match[1]) * TILE_SIZE;
    }
    if (std::regex_search(text, match, std::regex(R"(-?\d+)"))) return std::stoi(match[0]);
    return 0;
}

static SceneKind ReadSceneKind(const std::string& text, SceneKind fallback) {
    if (text.find("Underground") != std::string::npos) return SceneKind::Underground;
    if (text.find("Castle") != std::string::npos) return SceneKind::Castle;
    if (text.find("Underwater") != std::string::npos) return SceneKind::Underwater;
    if (text.find("Overworld") != std::string::npos) return SceneKind::Overworld;
    return fallback;
}

static std::vector<std::string> SplitTopLevelArgs(const std::string& args) {
    std::vector<std::string> result;
    std::string current;
    int parens = 0;
    int braces = 0;
    bool inString = false;

    for (char ch : args) {
        if (ch == '"') inString = !inString;
        if (!inString) {
            if (ch == '(') parens++;
            else if (ch == ')') parens--;
            else if (ch == '{') braces++;
            else if (ch == '}') braces--;
        }

        if (ch == ',' && parens == 0 && braces == 0 && !inString) {
            result.push_back(current);
            current.clear();
        } else {
            current.push_back(ch);
        }
    }
    if (!current.empty()) result.push_back(current);
    return result;
}

static std::string ConstructorArgs(const std::string& statement, const std::string& name) {
    size_t pos = statement.find(name);
    if (pos == std::string::npos) return "";

    size_t open = statement.find('(', pos + name.size());
    if (open == std::string::npos) return "";

    int depth = 0;
    bool inString = false;
    for (size_t i = open; i < statement.size(); i++) {
        char ch = statement[i];
        if (ch == '"') inString = !inString;
        if (inString) continue;

        if (ch == '(') depth++;
        else if (ch == ')') {
            depth--;
            if (depth == 0) return statement.substr(open + 1, i - open - 1);
        }
    }

    return "";
}

static std::vector<std::string> LevelStatements(const std::string& code) {
    std::vector<std::string> statements;
    std::string current;
    for (char ch : code) {
        current.push_back(ch);
        if (ch == ';') {
            statements.push_back(current);
            current.clear();
        }
    }
    return statements;
}

static void ParseLevelCode(const std::string& code, std::vector<LevelObject>& objects, SceneKind& sceneKind) {
    objects.clear();
    for (const std::string& statement : LevelStatements(code)) {
        sceneKind = ReadSceneKind(statement, sceneKind);

        if (statement.find("BackgroundProp") != std::string::npos) {
            std::vector<std::string> args = SplitTopLevelArgs(ConstructorArgs(statement, "BackgroundProp"));
            if (args.size() < 4) continue;
            objects.push_back(MakePropObject(PropIndexForLayoutName(args[3]), ReadExpr(args[0]), ReadExpr(args[1])));
        } else if (statement.find("coins.emplace_back") != std::string::npos ||
                   statement.find("coins.push_back") != std::string::npos) {
            size_t callStart = statement.find("emplace_back");
            std::string constructorName = "emplace_back";
            if (callStart == std::string::npos) {
                callStart = statement.find("push_back");
                constructorName = "push_back";
            }
            std::vector<std::string> args = SplitTopLevelArgs(ConstructorArgs(statement, constructorName));
            if (args.size() >= 2) objects.push_back({ObjectType::Coin, ReadExpr(args[0]), ReadExpr(args[1])});
        } else if (statement.find("CastleFlagpole") != std::string::npos) {
            std::vector<std::string> args = SplitTopLevelArgs(ConstructorArgs(statement, "CastleFlagpole"));
            if (args.size() >= 2) {
                objects.push_back({ObjectType::FlagPole, ReadExpr(args[0]) * TILE_SIZE, ReadExpr(args[1])});
            }
        } else if (statement.find("Goomba") != std::string::npos) {
            std::vector<std::string> args = SplitTopLevelArgs(ConstructorArgs(statement, "Goomba"));
            if (args.size() >= 2) objects.push_back({ObjectType::Goomba, ReadExpr(args[0]), ReadExpr(args[1])});
        } else if (statement.find("Koopa") != std::string::npos) {
            std::vector<std::string> args = SplitTopLevelArgs(ConstructorArgs(statement, "Koopa"));
            if (args.size() >= 2) objects.push_back({ObjectType::Koopa, ReadExpr(args[0]), ReadExpr(args[1])});
        } else if (statement.find("DrawTiledRect") != std::string::npos) {
            std::vector<std::string> args = SplitTopLevelArgs(ConstructorArgs(statement, "DrawTiledRect"));
            if (args.size() >= 4) {
                objects.push_back({ObjectType::Ground, ReadExpr(args[0]), ReadExpr(args[1]), ReadExpr(args[2]), ReadExpr(args[3])});
            }
        } else if (statement.find("std::make_unique<") != std::string::npos &&
                   statement.find("PowerUpBlock") == std::string::npos &&
                   statement.find("PipeBlock") == std::string::npos &&
                   statement.find("PipeWallBlock") == std::string::npos) {
            for (const BlockDefinition& block : GetBlockDefinitions()) {
                if (statement.find(std::string("std::make_unique<") + block.className + ">") == std::string::npos) {
                    continue;
                }
                std::vector<std::string> args = SplitTopLevelArgs(ConstructorArgs(statement, block.className));
                if (args.size() >= 2) {
                    objects.push_back(MakeBlockObject(BlockIndexForClassName(block.className), ReadExpr(args[0]), ReadExpr(args[1])));
                }
                break;
            }
        } else if (statement.find("PowerUpBlock") != std::string::npos) {
            std::vector<std::string> args = SplitTopLevelArgs(ConstructorArgs(statement, "PowerUpBlock"));
            if (args.size() >= 5) {
                ObjectType type = ObjectType::CoinBlock;
                if (args[4].find("fireflower") != std::string::npos) type = ObjectType::FireFlowerBlock;
                else if (args[4].find("mushroom") != std::string::npos) type = ObjectType::MushroomBlock;
                else if (args[4].find("1up") != std::string::npos) type = ObjectType::OneUpBlock;
                objects.push_back({type, ReadExpr(args[0]), ReadExpr(args[1])});
            }
        } else if (statement.find("WarpPipeBlock") != std::string::npos) {
            std::vector<std::string> args = SplitTopLevelArgs(ConstructorArgs(statement, "WarpPipeBlock"));
            if (args.size() >= 4) {
                LevelObject obj = {ObjectType::WarpPipe, ReadExpr(args[0]), ReadExpr(args[1]), TILE_SIZE, TILE_SIZE, ReadExpr(args[2]), ReadExpr(args[3])};
                if (args.size() >= 9) obj.pipeOrientation = ReadPipeOrientation(args[8]);
                objects.push_back(obj);
            }
        } else if (statement.find("PipeWallBlock") != std::string::npos) {
            std::vector<std::string> args = SplitTopLevelArgs(ConstructorArgs(statement, "PipeWallBlock"));
            if (args.size() >= 3) {
                LevelObject obj = {ObjectType::PipeWall, ReadExpr(args[0]), ReadExpr(args[1])};
                obj.pipeWide = 1;
                obj.pipeHigh = ReadExpr(args[2]);
                objects.push_back(obj);
            }
        } else if (statement.find("PipeBlock") != std::string::npos) {
            std::vector<std::string> args = SplitTopLevelArgs(ConstructorArgs(statement, "PipeBlock"));
            if (args.size() >= 4) {
                LevelObject obj = {ObjectType::Pipe, ReadExpr(args[0]), ReadExpr(args[1]), TILE_SIZE, TILE_SIZE, ReadExpr(args[2]), ReadExpr(args[3])};
                if (args.size() >= 7) obj.pipeOrientation = ReadPipeOrientation(args[6]);
                objects.push_back(obj);
            }
        }
    }

}

static void AppendTextInput(std::string& text) {
    if ((IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL) ||
         IsKeyDown(KEY_LEFT_SUPER) || IsKeyDown(KEY_RIGHT_SUPER)) && IsKeyPressed(KEY_V)) {
        const char* clipboard = GetClipboardText();
        if (clipboard) text += clipboard;
    }

    int key = GetCharPressed();
    while (key > 0) {
        if (key >= 32 && key <= 126) text.push_back((char)key);
        key = GetCharPressed();
    }
    if (IsKeyPressed(KEY_ENTER)) text.push_back('\n');
    if (IsKeyPressed(KEY_BACKSPACE) && !text.empty()) text.pop_back();
}

static bool SamePaletteSelection(const LevelObject& selected, const LevelObject& item) {
    if (selected.type != item.type) return false;
    if (selected.type == ObjectType::Block) return selected.blockIndex == item.blockIndex;
    if (selected.type == ObjectType::BackgroundProp) return selected.propIndex == item.propIndex;
    if (selected.type == ObjectType::Pipe || selected.type == ObjectType::WarpPipe) {
        return selected.pipeOrientation == item.pipeOrientation &&
               selected.pipeWide == item.pipeWide &&
               selected.pipeHigh == item.pipeHigh;
    }
    return true;
}

static LevelObject MakeAddObject(ObjectType addType, int addBlockIndex, int addPropIndex,
                                 int addPipeWide, int addPipeHigh, PipeOrientation addPipeOrientation,
                                 int x, int y) {
    LevelObject obj = {addType, x, y};
    if (addType == ObjectType::Block) obj.blockIndex = addBlockIndex;
    if (addType == ObjectType::BackgroundProp) obj.propIndex = addPropIndex;
    if (addType == ObjectType::Ground) {
        obj.w = TILE_SIZE * 8;
        obj.h = TILE_SIZE * 2;
    }
    if (addType == ObjectType::Pipe || addType == ObjectType::WarpPipe) {
        obj.pipeWide = addPipeWide;
        obj.pipeHigh = addPipeHigh;
        obj.pipeOrientation = addPipeOrientation;
    }
    if (addType == ObjectType::PipeWall) {
        obj.pipeWide = 1;
        obj.pipeHigh = addPipeHigh;
    }
    return obj;
}

static std::vector<PaletteItem> BuildPalette() {
    std::vector<PaletteItem> items;
    for (int i = 0; i < (int)GetBlockDefinitions().size(); i++) {
        LevelObject obj = MakeBlockObject(i, 0, 0);
        items.push_back({obj, GetBlockDefinitions()[i].displayName, "Blocks"});
    }

    items.push_back({{ObjectType::CoinBlock, 0, 0}, "? Coin", "Items"});
    items.push_back({{ObjectType::MushroomBlock, 0, 0}, "? Mushroom", "Items"});
    items.push_back({{ObjectType::FireFlowerBlock, 0, 0}, "? Fire", "Items"});
    items.push_back({{ObjectType::OneUpBlock, 0, 0}, "? 1-Up", "Items"});
    items.push_back({{ObjectType::Coin, 0, 0}, "Coin", "Items"});

    items.push_back({{ObjectType::Goomba, 0, 0}, "Goomba", "Enemies"});
    items.push_back({{ObjectType::Koopa, 0, 0}, "Koopa", "Enemies"});

    LevelObject pipe = {ObjectType::Pipe, 0, 0};
    pipe.pipeWide = 2;
    pipe.pipeHigh = 2;
    items.push_back({pipe, "Pipe Up", "Special"});
    LevelObject pipeRight = pipe;
    pipeRight.pipeWide = 4;
    pipeRight.pipeOrientation = PipeOrientation::HorizontalRight;
    items.push_back({pipeRight, "Pipe Right", "Special"});
    LevelObject pipeLeft = pipeRight;
    pipeLeft.pipeOrientation = PipeOrientation::HorizontalLeft;
    items.push_back({pipeLeft, "Pipe Left", "Special"});
    LevelObject warpPipe = {ObjectType::WarpPipe, 0, 0};
    warpPipe.pipeWide = 2;
    warpPipe.pipeHigh = 4;
    items.push_back({warpPipe, "Warp Pipe", "Special"});
    LevelObject warpPipeRight = warpPipe;
    warpPipeRight.pipeWide = 4;
    warpPipeRight.pipeHigh = 2;
    warpPipeRight.pipeOrientation = PipeOrientation::HorizontalRight;
    items.push_back({warpPipeRight, "Warp Right", "Special"});
    LevelObject pipeWall = {ObjectType::PipeWall, 0, 0};
    pipeWall.pipeWide = 1;
    pipeWall.pipeHigh = 8;
    items.push_back({pipeWall, "Pipe Wall", "Special"});
    items.push_back({{ObjectType::Ground, 0, 0, TILE_SIZE * 8, TILE_SIZE * 2}, "Ground", "Special"});
    items.push_back({{ObjectType::FlagPole, 0, 0}, "Flag Pole", "Special"});
    items.push_back({{ObjectType::CastleScenery, 0, 0}, "Castle", "Scenery"});

    for (int i = 0; i < (int)GetBackgroundPropDefinitions().size(); i++) {
        items.push_back({MakePropObject(i, 0, 0), GetBackgroundPropDefinitions()[i].displayName, "Scenery"});
    }
    return items;
}

static void ApplyPaletteSelection(const LevelObject& item, ObjectType& addType, int& addBlockIndex, int& addPropIndex,
                                  int& addPipeWide, int& addPipeHigh, PipeOrientation& addPipeOrientation) {
    addType = item.type;
    if (item.type == ObjectType::Block) addBlockIndex = item.blockIndex;
    if (item.type == ObjectType::BackgroundProp) addPropIndex = item.propIndex;
    if (item.type == ObjectType::Pipe || item.type == ObjectType::WarpPipe || item.type == ObjectType::PipeWall) {
        addPipeWide = item.pipeWide;
        addPipeHigh = item.pipeHigh;
        addPipeOrientation = item.pipeOrientation;
    }
}

static PipeOrientation NextPipeOrientation(PipeOrientation orientation) {
    switch (orientation) {
        case PipeOrientation::Vertical: return PipeOrientation::HorizontalRight;
        case PipeOrientation::HorizontalRight: return PipeOrientation::HorizontalLeft;
        case PipeOrientation::HorizontalLeft: return PipeOrientation::Vertical;
    }
    return PipeOrientation::Vertical;
}

static void DrawPalettePreview(const LevelObject& item, Rectangle box, Texture2D spriteSheet, Texture2D mushroomSheet, Texture2D enemiesSheet, const SceneType& scene) {
    const float cx = box.x + box.width * 0.5f;
    const float top = box.y + 17.0f;
    switch (item.type) {
        case ObjectType::Block:
            DrawSpritePart(spriteSheet, BlockSourceFor(BlockDefinitionFor(item), scene), {cx - 17.0f, top, 34.0f, 34.0f});
            break;
        case ObjectType::CoinBlock:
        case ObjectType::MushroomBlock:
        case ObjectType::FireFlowerBlock:
        case ObjectType::OneUpBlock:
            DrawSpritePart(spriteSheet, scene.questionBlockFrames[0], {cx - 17.0f, top, 34.0f, 34.0f});
            if (item.type == ObjectType::MushroomBlock || item.type == ObjectType::OneUpBlock) {
                DrawSpritePart(mushroomSheet, {0, 8, 16, 16}, {cx - 10.0f, top - 12.0f, 20.0f, 20.0f});
            } else if (item.type == ObjectType::FireFlowerBlock) {
                DrawSpritePart(mushroomSheet, {32, 44, 16, 16}, {cx - 10.0f, top - 12.0f, 20.0f, 20.0f});
            }
            break;
        case ObjectType::Coin:
            DrawSpritePart(mushroomSheet, {180, 36, 8, 16}, {cx - 8.0f, top, 16.0f, 34.0f});
            break;
        case ObjectType::Goomba:
            DrawSpritePart(enemiesSheet, scene.goombaFrames[0], {cx - 17.0f, top, 34.0f, 34.0f});
            break;
        case ObjectType::Koopa:
            DrawSpritePart(enemiesSheet, scene.koopaFrames[0], {cx - 15.0f, top - 4.0f, 30.0f, 45.0f});
            break;
        case ObjectType::Pipe:
        case ObjectType::WarpPipe:
            if (item.pipeOrientation == PipeOrientation::Vertical) {
                DrawSpritePart(spriteSheet, scene.pipeTopLeft, {cx - 18.0f, top, 18.0f, 18.0f});
                DrawSpritePart(spriteSheet, scene.pipeTopRight, {cx, top, 18.0f, 18.0f});
                DrawSpritePart(spriteSheet, scene.pipeBodyLeft, {cx - 18.0f, top + 18.0f, 18.0f, 18.0f});
                DrawSpritePart(spriteSheet, scene.pipeBodyRight, {cx, top + 18.0f, 18.0f, 18.0f});
            } else {
                Rectangle leftTop = {249.0f, 230.0f, 16.0f, 16.0f};
                Rectangle rightTop = {266.0f, 230.0f, 16.0f, 16.0f};
                if (item.pipeOrientation == PipeOrientation::HorizontalLeft) {
                    leftTop.width *= -1.0f;
                    rightTop.width *= -1.0f;
                }
                DrawSpritePart(spriteSheet, leftTop, {cx - 24.0f, top + 6.0f, 24.0f, 24.0f});
                DrawSpritePart(spriteSheet, rightTop, {cx, top + 6.0f, 24.0f, 24.0f});
            }
            if (item.type == ObjectType::WarpPipe) DrawCircle(cx, top + 8.0f, 5.0f, YELLOW);
            break;
        case ObjectType::PipeWall:
            DrawSpritePart(spriteSheet, {119.0f, 213.0f, 16.0f, 16.0f}, {cx - 9.0f, top - 4.0f, 18.0f, 18.0f});
            DrawSpritePart(spriteSheet, {119.0f, 213.0f, 16.0f, 16.0f}, {cx - 9.0f, top + 14.0f, 18.0f, 18.0f});
            DrawSpritePart(spriteSheet, {119.0f, 230.0f, 16.0f, 16.0f}, {cx - 9.0f, top + 32.0f, 18.0f, 18.0f});
            break;
        case ObjectType::CastleScenery:
            DrawSpritePart(spriteSheet, {24.0f, 696.0f, 80.0f, 80.0f}, {cx - 24.0f, top - 4.0f, 48.0f, 48.0f});
            break;
        case ObjectType::Ground:
            for (int x = 0; x < 2; x++) {
                for (int y = 0; y < 2; y++) {
                    DrawSpritePart(spriteSheet, scene.groundBlock, {cx - 18.0f + x * 18.0f, top + y * 18.0f, 18.0f, 18.0f});
                }
            }
            break;
        case ObjectType::FlagPole:
            DrawRectangle((int)cx, (int)(top - 2), 4, 42, LIGHTGRAY);
            DrawCircle((int)(cx + 2), (int)(top - 5), 5.0f, WHITE);
            DrawTriangle({cx - 2.0f, top + 6.0f}, {cx - 2.0f, top + 23.0f}, {cx - 25.0f, top + 14.0f}, RED);
            DrawRectangle((int)(cx - 12), (int)(top + 37), 28, 5, BROWN);
            break;
        case ObjectType::BackgroundProp: {
            const BackgroundPropDefinition& prop = PropDefinitionFor(item);
            float scale = 13.0f;
            for (const SpritePart& part : *prop.layout) {
                DrawSpritePart(spriteSheet, part.source, {box.x + 10.0f + part.offset.x * scale, top + part.offset.y * scale, scale, scale});
            }
            break;
        }
    }
}

static int DrawPalette(const std::vector<PaletteItem>& palette, ObjectType addType, int addBlockIndex, int addPropIndex,
                       int addPipeWide, int addPipeHigh, PipeOrientation addPipeOrientation,
                       Texture2D spriteSheet, Texture2D mushroomSheet, Texture2D enemiesSheet, const SceneType& scene) {
    LevelObject current = {addType, 0, 0};
    current.blockIndex = addBlockIndex;
    current.propIndex = addPropIndex;
    current.pipeWide = addPipeWide;
    current.pipeHigh = addPipeHigh;
    current.pipeOrientation = addPipeOrientation;

    DrawRectangle(0, 0, GetScreenWidth(), PALETTE_HEIGHT, Fade(BLACK, 0.84f));
    DrawText("LMB place/select/drag | RMB pan | Wheel zoom | P print | I paste | Delete remove | Arrows move | W/A/S/D resize selected", 12, 8, 16, RAYWHITE);
    DrawText(TextFormat("Scene: %s | Add: %s | Objects visible in palette: blocks, items, enemies, pipes, flag pole, scenery",
        scene.name, ObjectName(current)), 12, 30, 16, YELLOW);

    int hovered = -1;
    Vector2 mouse = GetMousePosition();
    int x = 12;
    int y = 58;
    std::string lastCategory;
    for (int i = 0; i < (int)palette.size(); i++) {
        if (palette[i].category != lastCategory) {
            if (!lastCategory.empty()) x += 8;
            if (x + PALETTE_CELL_W > GetScreenWidth() - 12) {
                x = 12;
                y += PALETTE_CELL_H;
            }
            DrawText(palette[i].category.c_str(), x, y + 25, 10, Fade(RAYWHITE, 0.75f));
            x += 46;
            lastCategory = palette[i].category;
        }
        if (x + PALETTE_CELL_W > GetScreenWidth() - 12) {
            x = 12;
            y += PALETTE_CELL_H;
        }
        Rectangle cell = {(float)x, (float)y, (float)PALETTE_CELL_W - 6.0f, (float)PALETTE_CELL_H - 8.0f};
        bool active = SamePaletteSelection(current, palette[i].object);
        bool over = CheckCollisionPointRec(mouse, cell);
        if (over) hovered = i;
        DrawRectangleRounded(cell, 0.08f, 6, active ? Fade(YELLOW, 0.28f) : (over ? Fade(WHITE, 0.16f) : Fade(WHITE, 0.07f)));
        DrawRectangleLinesEx(cell, active ? 2.0f : 1.0f, active ? YELLOW : Fade(RAYWHITE, 0.34f));
        DrawPalettePreview(palette[i].object, cell, spriteSheet, mushroomSheet, enemiesSheet, scene);
        std::string label = palette[i].label;
        if ((int)label.size() > 11) label = label.substr(0, 10) + ".";
        DrawText(label.c_str(), (int)cell.x + 5, (int)cell.y + 52, 10, RAYWHITE);
        x += PALETTE_CELL_W;
    }

    DrawText("Hotkeys: 1 block, 2 ? coin, 3 ? mushroom, 4 ? fire, 5 coin, 6 goomba, 7 pipe, 8 ground, F flag, R cycle selected pipe", 12, PALETTE_HEIGHT - 24, 14, Fade(RAYWHITE, 0.86f));
    return hovered;
}

static int PaletteIndexAtPoint(const std::vector<PaletteItem>& palette, Vector2 point) {
    int x = 12;
    int y = 58;
    std::string lastCategory;
    for (int i = 0; i < (int)palette.size(); i++) {
        if (palette[i].category != lastCategory) {
            if (!lastCategory.empty()) x += 8;
            if (x + PALETTE_CELL_W > GetScreenWidth() - 12) {
                x = 12;
                y += PALETTE_CELL_H;
            }
            x += 46;
            lastCategory = palette[i].category;
        }
        if (x + PALETTE_CELL_W > GetScreenWidth() - 12) {
            x = 12;
            y += PALETTE_CELL_H;
        }
        Rectangle cell = {(float)x, (float)y, (float)PALETTE_CELL_W - 6.0f, (float)PALETTE_CELL_H - 8.0f};
        if (CheckCollisionPointRec(point, cell)) return i;
        x += PALETTE_CELL_W;
    }
    return -1;
}

int main() {
    const int screenWidth = 1200;
    const int screenHeight = 760;
    InitWindow(screenWidth, screenHeight, "Level Editor Debug");

    Image img1 = LoadImage("assets/images/52571.png");
    ImageColorReplace(&img1, (Color){148, 148, 255, 255}, BLANK);
    Texture2D spriteSheet = LoadTextureFromImage(img1);
    UnloadImage(img1);

    Image img2 = LoadImage("assets/images/52569.png");
    ImageColorReplace(&img2, (Color){146, 144, 255, 255}, BLANK);
    Texture2D mushroomSheet = LoadTextureFromImage(img2);
    UnloadImage(img2);

    Image img3 = LoadImage("assets/images/52570.png");
    ImageColorReplace(&img3, (Color){146, 144, 255, 255}, BLANK);
    Texture2D enemiesSheet = LoadTextureFromImage(img3);
    UnloadImage(img3);

    std::vector<LevelObject> objects;
    LoadDefaultLevel(objects);
    SceneKind sceneKind = SceneKind::Overworld;

    Camera2D camera = {0};
    camera.offset = {0, 0};
    camera.zoom = 1.0f;

    ObjectType addType = ObjectType::Block;
    int addPropIndex = 0;
    int addBlockIndex = 0;
    int addPipeWide = 2;
    int addPipeHigh = 2;
    PipeOrientation addPipeOrientation = PipeOrientation::Vertical;
    int selected = -1;
    bool dragging = false;
    bool dragPending = false;
    bool pasteMode = false;
    std::string pastedCode;
    Vector2 dragOffset = {0, 0};
    Vector2 dragStartScreen = {0, 0};

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        const SceneType& scene = GetSceneType(sceneKind);
        const std::vector<PaletteItem> palette = BuildPalette();

        if (pasteMode) {
            bool commandDown = IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL) ||
                               IsKeyDown(KEY_LEFT_SUPER) || IsKeyDown(KEY_RIGHT_SUPER);
            if (commandDown && IsKeyPressed(KEY_ENTER)) {
                ParseLevelCode(pastedCode, objects, sceneKind);
                selected = objects.empty() ? -1 : 0;
                pasteMode = false;
            } else if (IsKeyPressed(KEY_ESCAPE)) {
                pasteMode = false;
            } else {
                AppendTextInput(pastedCode);
            }
        } else {
            float wheel = GetMouseWheelMove();
            if (wheel != 0) {
                Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), camera);
                camera.offset = GetMousePosition();
                camera.target = mouseWorld;
                camera.zoom = std::max(0.25f, camera.zoom + wheel * 0.1f);
            }
            if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
                camera.target = Vector2Add(camera.target, Vector2Scale(GetMouseDelta(), -1.0f / camera.zoom));
            }

            const std::vector<BlockDefinition>& blocks = GetBlockDefinitions();
            if (IsKeyPressed(KEY_ONE) && blocks.size() > 0) { addType = ObjectType::Block; addBlockIndex = 0; }
            if (IsKeyPressed(KEY_TWO)) addType = ObjectType::CoinBlock;
            if (IsKeyPressed(KEY_THREE)) addType = ObjectType::MushroomBlock;
            if (IsKeyPressed(KEY_FOUR)) addType = ObjectType::FireFlowerBlock;
            if (IsKeyPressed(KEY_FIVE)) addType = ObjectType::Coin;
            if (IsKeyPressed(KEY_SIX)) addType = ObjectType::Goomba;
            if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_SIX)) addType = ObjectType::Koopa;
            if (IsKeyPressed(KEY_SEVEN)) {
                addType = ObjectType::Pipe;
                addPipeWide = 2;
                addPipeHigh = 2;
                addPipeOrientation = PipeOrientation::Vertical;
            }
            if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_SEVEN)) {
                addType = ObjectType::WarpPipe;
                addPipeWide = 2;
                addPipeHigh = 4;
                addPipeOrientation = PipeOrientation::Vertical;
            }
            if (IsKeyPressed(KEY_EIGHT)) addType = ObjectType::Ground;
            if (IsKeyPressed(KEY_F)) addType = ObjectType::FlagPole;
            if (IsKeyPressed(KEY_COMMA) && !blocks.empty()) {
                addType = ObjectType::Block;
                addBlockIndex = (addBlockIndex + (int)blocks.size() - 1) % (int)blocks.size();
            }
            if (IsKeyPressed(KEY_PERIOD) && !blocks.empty()) {
                addType = ObjectType::Block;
                addBlockIndex = (addBlockIndex + 1) % (int)blocks.size();
            }
            const std::vector<BackgroundPropDefinition>& props = GetBackgroundPropDefinitions();
            if (IsKeyPressed(KEY_NINE) && props.size() > 0) { addType = ObjectType::BackgroundProp; addPropIndex = 0; }
            if (IsKeyPressed(KEY_ZERO) && props.size() > 1) { addType = ObjectType::BackgroundProp; addPropIndex = 1; }
            if (IsKeyPressed(KEY_LEFT_BRACKET) && !props.empty()) {
                addType = ObjectType::BackgroundProp;
                addPropIndex = (addPropIndex + (int)props.size() - 1) % (int)props.size();
            }
            if (IsKeyPressed(KEY_RIGHT_BRACKET) && !props.empty()) {
                addType = ObjectType::BackgroundProp;
                addPropIndex = (addPropIndex + 1) % (int)props.size();
            }
            if (IsKeyPressed(KEY_MINUS)) sceneKind = NextSceneKind(sceneKind, -1);
            if (IsKeyPressed(KEY_EQUAL)) sceneKind = NextSceneKind(sceneKind, 1);
            if (IsKeyPressed(KEY_P)) PrintLevelCode(objects, sceneKind);
            if (IsKeyPressed(KEY_I)) {
                pastedCode.clear();
                pasteMode = true;
            }
            if (IsKeyPressed(KEY_DELETE) || IsKeyPressed(KEY_BACKSPACE)) {
                if (selected >= 0 && selected < (int)objects.size()) {
                    objects.erase(objects.begin() + selected);
                    selected = -1;
                }
            }

            Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), camera);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                int paletteIndex = GetMouseY() < PALETTE_HEIGHT ? PaletteIndexAtPoint(palette, GetMousePosition()) : -1;
                if (paletteIndex >= 0) {
                    ApplyPaletteSelection(palette[paletteIndex].object, addType, addBlockIndex, addPropIndex,
                        addPipeWide, addPipeHigh, addPipeOrientation);
                    selected = -1;
                    dragging = false;
                    dragPending = false;
                } else if (GetMouseY() >= PALETTE_HEIGHT) {
                    selected = -1;
                    for (int i = (int)objects.size() - 1; i >= 0; i--) {
                        if (CheckCollisionPointRec(mouseWorld, ObjectBounds(objects[i]))) {
                            selected = i;
                            dragOffset = {(float)objects[i].x - mouseWorld.x, (float)objects[i].y - mouseWorld.y};
                            dragPending = true;
                            dragging = false;
                            dragStartScreen = GetMousePosition();
                            break;
                        }
                    }
                    if (selected == -1) {
                        LevelObject obj = MakeAddObject(addType, addBlockIndex, addPropIndex,
                            addPipeWide, addPipeHigh, addPipeOrientation,
                            SnapXForType(addType, mouseWorld.x), SnapYForType(addType, mouseWorld.y));
                        objects.push_back(obj);
                        selected = (int)objects.size() - 1;
                        dragging = true;
                        dragPending = false;
                        dragOffset = {0, 0};
                    }
                }
            }
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                dragging = false;
                dragPending = false;
            }
            if (dragPending && IsMouseButtonDown(MOUSE_BUTTON_LEFT) &&
                Vector2Distance(GetMousePosition(), dragStartScreen) >= DRAG_START_DISTANCE) {
                dragging = true;
                dragPending = false;
            }
            if (dragging && selected >= 0) {
                objects[selected].x = SnapXForType(objects[selected].type, mouseWorld.x + dragOffset.x);
                objects[selected].y = SnapYForType(objects[selected].type, mouseWorld.y + dragOffset.y);
            }

            if (selected >= 0 && selected < (int)objects.size()) {
                LevelObject& obj = objects[selected];
                int move = IsKeyDown(KEY_LEFT_SHIFT) ? 1 : TILE_SIZE;
                if (IsKeyPressed(KEY_LEFT)) obj.x -= move;
                if (IsKeyPressed(KEY_RIGHT)) obj.x += move;
                if (IsKeyPressed(KEY_UP)) obj.y -= move;
                if (IsKeyPressed(KEY_DOWN)) obj.y += move;
                if (obj.type == ObjectType::Ground) {
                    if (IsKeyPressed(KEY_W)) obj.h = std::max(TILE_SIZE, obj.h - TILE_SIZE);
                    if (IsKeyPressed(KEY_S)) obj.h += TILE_SIZE;
                    if (IsKeyPressed(KEY_A)) obj.w = std::max(TILE_SIZE, obj.w - TILE_SIZE);
                    if (IsKeyPressed(KEY_D)) obj.w += TILE_SIZE;
                }
                if (obj.type == ObjectType::Pipe || obj.type == ObjectType::WarpPipe) {
                    if (IsKeyPressed(KEY_W)) obj.pipeHigh = std::max(1, obj.pipeHigh - 1);
                    if (IsKeyPressed(KEY_S)) obj.pipeHigh++;
                    if (IsKeyPressed(KEY_A)) obj.pipeWide = std::max(1, obj.pipeWide - 1);
                    if (IsKeyPressed(KEY_D)) obj.pipeWide++;
                    if (IsKeyPressed(KEY_R)) obj.pipeOrientation = NextPipeOrientation(obj.pipeOrientation);
                }
                if (obj.type == ObjectType::PipeWall) {
                    if (IsKeyPressed(KEY_W)) obj.pipeHigh = std::max(1, obj.pipeHigh - 1);
                    if (IsKeyPressed(KEY_S)) obj.pipeHigh++;
                }
            }
        }

        BeginDrawing();
        ClearBackground(scene.backgroundColor);
        BeginMode2D(camera);
            const int gridMinX = -2100;
            const int gridMaxX = 5200;
            const int gridMinY = -600;
            const int gridMaxY = 1100;

            for (int x = FirstGridLine(gridMinX, TILE_SIZE); x <= gridMaxX; x += TILE_SIZE) {
                DrawLine(x, gridMinY, x, gridMaxY, Fade(WHITE, 0.18f));
            }

            for (int y = FirstGridLine(gridMinY, TILE_SIZE, OBJECT_GRID_OFFSET_Y); y <= gridMaxY; y += TILE_SIZE) {
                DrawLine(gridMinX, y, gridMaxX, y, Fade(WHITE, 0.18f));
            }

            for (int y = FirstGridLine(gridMinY, TILE_SIZE, BLOCK_GRID_DRAW_OFFSET_Y); y <= gridMaxY; y += TILE_SIZE) {
                DrawLine(gridMinX, y, gridMaxX, y, Fade(ORANGE, 0.18f));
            }

            for (int i = 0; i < (int)objects.size(); i++) {
                DrawObject(objects[i], spriteSheet, mushroomSheet, enemiesSheet, scene);
                Rectangle bounds = ObjectBounds(objects[i]);
                DrawRectangleLinesEx(bounds, (i == selected ? 3.0f : 1.0f) / camera.zoom, i == selected ? RED : Fade(BLACK, 0.45f));
            }
        EndMode2D();

        DrawPalette(palette, addType, addBlockIndex, addPropIndex, addPipeWide, addPipeHigh, addPipeOrientation,
            spriteSheet, mushroomSheet, enemiesSheet, scene);
        DrawRectangle(0, screenHeight - 28, screenWidth, 28, Fade(BLACK, 0.72f));
        DrawText(TextFormat("Selected: %s | Objects: %d",
                 selected >= 0 ? ObjectName(objects[selected]) : "None",
                 (int)objects.size()), 12, screenHeight - 22, 16, YELLOW);

        if (selected >= 0 && selected < (int)objects.size() &&
            (objects[selected].type == ObjectType::Ground || objects[selected].type == ObjectType::Pipe ||
             objects[selected].type == ObjectType::WarpPipe || objects[selected].type == ObjectType::PipeWall)) {
            DrawText(objects[selected].type == ObjectType::Pipe || objects[selected].type == ObjectType::WarpPipe
                ? "Selected pipe: W/A/S/D resize | R cycle vertical/right/left"
                : "Selected size: W/A/S/D resize", 560, screenHeight - 22, 16, ORANGE);
        }

        if (pasteMode) {
            DrawRectangle(80, PALETTE_HEIGHT + 20, screenWidth - 160, screenHeight - PALETTE_HEIGHT - 70, Fade(BLACK, 0.88f));
            DrawRectangleLines(80, PALETTE_HEIGHT + 20, screenWidth - 160, screenHeight - PALETTE_HEIGHT - 70, YELLOW);
            DrawText("Paste level code here. Cmd/Ctrl+Enter loads it. Esc cancels.", 100, PALETTE_HEIGHT + 40, 20, YELLOW);
            DrawText(pastedCode.c_str(), 100, PALETTE_HEIGHT + 75, 16, RAYWHITE);
        }
        EndDrawing();
    }

    UnloadTexture(spriteSheet);
    UnloadTexture(mushroomSheet);
    UnloadTexture(enemiesSheet);
    CloseWindow();
    return 0;
}
