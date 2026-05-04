#ifndef BACKGROUND_PROP_H
#define BACKGROUND_PROP_H

#include <raylib.h>
#include <string>
#include <vector>

#define TILE_SIZE 42

struct SpritePart {
    Rectangle source;
    Vector2 offset;
};

extern std::vector<SpritePart> HILL_LAYOUT;
extern std::vector<SpritePart> SMALL_HILL_LAYOUT;
extern std::vector<SpritePart> GRASS_LAYOUT;
extern std::vector<SpritePart> TINY_GRASS_LAYOUT;
extern std::vector<SpritePart> MEDIUM_GRASS_LAYOUT;
extern std::vector<SpritePart> CLOUD_LAYOUT;
extern std::vector<SpritePart> MEDIUM_CLOUD_LAYOUT;
extern std::vector<SpritePart> LARGE_CLOUD_LAYOUT;

struct BackgroundPropDefinition {
    const char* displayName;
    const char* layoutName;
    const std::vector<SpritePart>* layout;
};

const std::vector<BackgroundPropDefinition>& GetBackgroundPropDefinitions();
const BackgroundPropDefinition* FindBackgroundPropDefinitionByLayoutName(const std::string& layoutName);

class BackgroundPropRegistration {
public:
    BackgroundPropRegistration(const char* displayName, const char* layoutName, const std::vector<SpritePart>* layout);
};

#define DEFINE_BACKGROUND_PROP(LAYOUT_NAME, ...) \
    std::vector<SpritePart> LAYOUT_NAME = __VA_ARGS__; \
    namespace { \
        BackgroundPropRegistration LAYOUT_NAME##_registration(#LAYOUT_NAME, #LAYOUT_NAME, &LAYOUT_NAME); \
    }

class BackgroundProp {
private:
    float posX, posY;
    Texture2D texture;
    const std::vector<SpritePart>* blueprint;

public:
    BackgroundProp(float x, float y, Texture2D tex, const std::vector<SpritePart>& parts);
    void draw();
};

#endif
