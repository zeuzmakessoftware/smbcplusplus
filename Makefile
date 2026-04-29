all:
	g++ main.cpp mario.cpp drawTiledRect.cpp backgroundProp.cpp blocks.cpp mushroom.cpp fireflower.cpp fireball.cpp goomba.cpp levelData.cpp -o main -I/opt/homebrew/include -L/opt/homebrew/lib -lraylib
	./main

texture:
	g++ textureFinderDebug.cpp -o textureFinderDebug -I/opt/homebrew/include -L/opt/homebrew/lib -lraylib
	./textureFinderDebug "50365.png"

editor:
	g++ levelEditorDebug.cpp backgroundProp.cpp blocks.cpp mushroom.cpp -o levelEditorDebug -I/opt/homebrew/include -L/opt/homebrew/lib -lraylib
	./levelEditorDebug
