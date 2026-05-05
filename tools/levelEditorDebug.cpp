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
    Ground,
    Coin,
    CoinBlock,
    MushroomBlock,
    FireFlowerBlock,
    Pipe
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
};

static const int OBJECT_GRID_OFFSET_Y = -72;
static const int BLOCK_GRID_OFFSET_Y = 12;
static const int BLOCK_GRID_DRAW_OFFSET_Y = OBJECT_GRID_OFFSET_Y + 12;
static const float DRAG_START_DISTANCE = 2.0f;

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
        case ObjectType::Ground: return "Ground";
        case ObjectType::Coin: return "Coin";
        case ObjectType::CoinBlock: return "Coin Block";
        case ObjectType::MushroomBlock: return "Mushroom Block";
        case ObjectType::FireFlowerBlock: return "Fire Flower Block";
        case ObjectType::Pipe: return "Pipe";
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
    if (obj.type == ObjectType::Pipe) {
        return {(float)obj.x, (float)obj.y, (float)(obj.pipeWide * TILE_SIZE), (float)(obj.pipeHigh * TILE_SIZE)};
    }
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
    if (type == ObjectType::Block || type == ObjectType::CoinBlock ||
        type == ObjectType::MushroomBlock || type == ObjectType::FireFlowerBlock ||
        type == ObjectType::Pipe || type == ObjectType::Coin) {
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

static void DrawObject(const LevelObject& obj, Texture2D spriteSheet, Texture2D mushroomSheet, Texture2D enemiesSheet, const SceneType& scene) {
    switch (obj.type) {
        case ObjectType::BackgroundProp:
            DrawProp(obj, spriteSheet);
            break;
        case ObjectType::Goomba:
            DrawSpritePart(enemiesSheet, scene.goombaFrames[0], {(float)obj.x, (float)obj.y, TILE_SIZE, TILE_SIZE});
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
        case ObjectType::Pipe:
            DrawPipe(obj, spriteSheet, scene);
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
            case ObjectType::Pipe:
                std::cout << "blocks.push_back(std::make_unique<PipeBlock>(" << Expr(obj.x)
                          << ", " << Expr(obj.y) << ", " << obj.pipeWide << ", " << obj.pipeHigh
                          << ", spriteSheet, " << sceneExpr << "));\n";
                break;
            default:
                break;
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
        } else if (statement.find("Goomba") != std::string::npos) {
            std::vector<std::string> args = SplitTopLevelArgs(ConstructorArgs(statement, "Goomba"));
            if (args.size() >= 2) objects.push_back({ObjectType::Goomba, ReadExpr(args[0]), ReadExpr(args[1])});
        } else if (statement.find("DrawTiledRect") != std::string::npos) {
            std::vector<std::string> args = SplitTopLevelArgs(ConstructorArgs(statement, "DrawTiledRect"));
            if (args.size() >= 4) {
                objects.push_back({ObjectType::Ground, ReadExpr(args[0]), ReadExpr(args[1]), ReadExpr(args[2]), ReadExpr(args[3])});
            }
        } else if (statement.find("std::make_unique<") != std::string::npos &&
                   statement.find("PowerUpBlock") == std::string::npos &&
                   statement.find("PipeBlock") == std::string::npos) {
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
                objects.push_back({type, ReadExpr(args[0]), ReadExpr(args[1])});
            }
        } else if (statement.find("PipeBlock") != std::string::npos) {
            std::vector<std::string> args = SplitTopLevelArgs(ConstructorArgs(statement, "PipeBlock"));
            if (args.size() >= 4) {
                objects.push_back({ObjectType::Pipe, ReadExpr(args[0]), ReadExpr(args[1]), TILE_SIZE, TILE_SIZE, ReadExpr(args[2]), ReadExpr(args[3])});
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
    int selected = -1;
    bool dragging = false;
    bool dragPending = false;
    bool pasteMode = false;
    std::string pastedCode;
    Vector2 dragOffset = {0, 0};
    Vector2 dragStartScreen = {0, 0};

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
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
            if (IsKeyPressed(KEY_SEVEN)) addType = ObjectType::Pipe;
            if (IsKeyPressed(KEY_EIGHT)) addType = ObjectType::Ground;
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
                    LevelObject obj = {addType, SnapXForType(addType, mouseWorld.x), SnapYForType(addType, mouseWorld.y)};
                    if (addType == ObjectType::Block) {
                        obj.blockIndex = addBlockIndex;
                    }
                    if (addType == ObjectType::BackgroundProp) {
                        obj.propIndex = addPropIndex;
                    }
                    if (addType == ObjectType::Ground) {
                        obj.w = TILE_SIZE * 8;
                        obj.h = TILE_SIZE * 2;
                    }
                    objects.push_back(obj);
                    selected = (int)objects.size() - 1;
                    dragging = true;
                    dragPending = false;
                    dragOffset = {0, 0};
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
                if (obj.type == ObjectType::Pipe) {
                    if (IsKeyPressed(KEY_W)) obj.pipeHigh = std::max(1, obj.pipeHigh - 1);
                    if (IsKeyPressed(KEY_S)) obj.pipeHigh++;
                    if (IsKeyPressed(KEY_A)) obj.pipeWide = std::max(1, obj.pipeWide - 1);
                    if (IsKeyPressed(KEY_D)) obj.pipeWide++;
                }
            }
        }

        const SceneType& scene = GetSceneType(sceneKind);
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

        DrawRectangle(0, 0, screenWidth, 160, Fade(BLACK, 0.78f));
        DrawText("LMB select/add/drag | RMB pan | Wheel zoom | P print code | I paste code | Delete remove | Arrows move | Shift+Arrows 1px", 12, 10, 18, RAYWHITE);
        DrawText("1 block  2 ? Coin  3 ? Mushroom  4 ? Fire  5 Coin  6 Goomba  7 Pipe  8 Ground  9/0 props", 12, 34, 18, RAYWHITE);
        DrawText("CTRL/Cmd+Enter loads paste | ,/. cycle blocks | [/] cycle props | -/= cycle scenes", 12, 58, 18, RAYWHITE);
        std::string blockList = "Blocks:";
        const std::vector<BlockDefinition>& blocks = GetBlockDefinitions();
        for (int i = 0; i < (int)blocks.size(); i++) {
            blockList += " ";
            if (i == 0) blockList += "1=";
            if (addType == ObjectType::Block && i == addBlockIndex) blockList += "[";
            blockList += blocks[i].displayName;
            if (addType == ObjectType::Block && i == addBlockIndex) blockList += "]";
        }
        DrawText(blockList.c_str(), 12, 82, 18, RAYWHITE);
        std::string propList = "Props:";
        const std::vector<BackgroundPropDefinition>& props = GetBackgroundPropDefinitions();
        const char* propKeys[] = {"9", "0"};
        for (int i = 0; i < (int)props.size(); i++) {
            propList += " ";
            if (i < 2) {
                propList += propKeys[i];
                propList += "=";
            }
            if (addType == ObjectType::BackgroundProp && i == addPropIndex) propList += "[";
            propList += props[i].displayName;
            if (addType == ObjectType::BackgroundProp && i == addPropIndex) propList += "]";
        }
        DrawText(propList.c_str(), 12, 106, 18, RAYWHITE);
        DrawText(TextFormat("Scene: %s | Add: %s | Selected: %s | Objects: %d",
                 scene.name,
                 addType == ObjectType::BackgroundProp ? props[addPropIndex].displayName :
                 addType == ObjectType::Block ? blocks[addBlockIndex].displayName : TypeName(addType),
                 selected >= 0 ? ObjectName(objects[selected]) : "None",
                 (int)objects.size()), 12, 130, 18, YELLOW);

        if (selected >= 0 && selected < (int)objects.size() &&
            (objects[selected].type == ObjectType::Ground || objects[selected].type == ObjectType::Pipe)) {
            DrawText("Selected size: W/A/S/D resize", 835, 130, 18, ORANGE);
        }

        if (pasteMode) {
            DrawRectangle(80, 120, screenWidth - 160, screenHeight - 190, Fade(BLACK, 0.88f));
            DrawRectangleLines(80, 120, screenWidth - 160, screenHeight - 190, YELLOW);
            DrawText("Paste level code here. Cmd/Ctrl+Enter loads it. Esc cancels.", 100, 140, 20, YELLOW);
            DrawText(pastedCode.c_str(), 100, 175, 16, RAYWHITE);
        }
        EndDrawing();
    }

    UnloadTexture(spriteSheet);
    UnloadTexture(mushroomSheet);
    UnloadTexture(enemiesSheet);
    CloseWindow();
    return 0;
}
