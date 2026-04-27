all:
	g++ main.cpp mario.cpp drawTiledRect.cpp backgroundProp.cpp -o main -I/opt/homebrew/include -L/opt/homebrew/lib -lraylib
	./main

texture:
	g++ textureFinderDebug.cpp -o textureFinderDebug -I/opt/homebrew/include -L/opt/homebrew/lib -lraylib
	./textureFinderDebug "52571.png"