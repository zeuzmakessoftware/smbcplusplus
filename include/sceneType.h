#ifndef SCENE_TYPE_H
#define SCENE_TYPE_H

#include <raylib.h>

enum class SceneKind {
    Overworld,
    Underground,
    Castle,
    Underwater
};

struct SceneType {
    SceneKind kind;
    const char* name;
    Color backgroundColor;

    Rectangle groundBlock;
    Rectangle brickBlock;
    Rectangle solidBlock;
    Rectangle emptyBlock;
    Rectangle questionBlockFrames[3];
    Rectangle coinFrames[3];

    Rectangle pipeTopLeft;
    Rectangle pipeTopRight;
    Rectangle pipeBodyLeft;
    Rectangle pipeBodyRight;

    Rectangle goombaFrames[2];
    Rectangle goombaSquashed;

    Rectangle koopaFrames[2];
    Rectangle koopaParatroopaFrames[2];
    Rectangle koopaShellFrames[2];
};

const SceneType& GetSceneType(SceneKind kind);

#endif
