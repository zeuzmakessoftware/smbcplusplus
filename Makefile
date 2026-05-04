CXX = g++
CXXFLAGS = -Iinclude -I/opt/homebrew/include -MMD -MP
LDFLAGS = -L/opt/homebrew/lib -lraylib

BLOCK_SRCS = $(wildcard src/blocks/*.cpp)
COMMON_SRCS = src/backgroundProp.cpp $(BLOCK_SRCS) src/sceneType.cpp src/mushroom.cpp
MAIN_SRCS = src/main.cpp src/mario.cpp src/drawTiledRect.cpp src/fireflower.cpp src/fireball.cpp \
            src/goomba.cpp src/levelData.cpp src/scoreboard.cpp src/scorepopup.cpp src/castleFlagpole.cpp $(COMMON_SRCS)
EDITOR_SRCS = tools/levelEditorDebug.cpp $(COMMON_SRCS)
TEXTURE_SRCS = tools/textureFinderDebug.cpp

MAIN_OBJS = $(MAIN_SRCS:%.cpp=build/%.o)
EDITOR_OBJS = $(EDITOR_SRCS:%.cpp=build/%.o)
TEXTURE_OBJS = $(TEXTURE_SRCS:%.cpp=build/%.o)

DEPS = $(MAIN_OBJS:.o=.d) $(EDITOR_OBJS:.o=.d) $(TEXTURE_OBJS:.o=.d)

.PHONY: all texture editor clean

all: main
	./bin/main

main: bin/main

bin/main: $(MAIN_OBJS) | bin
	$(CXX) $(MAIN_OBJS) -o $@ $(LDFLAGS)

texture: bin/textureFinderDebug
	./bin/textureFinderDebug "assets/images/52571.png"

bin/textureFinderDebug: $(TEXTURE_OBJS) | bin
	$(CXX) $(TEXTURE_OBJS) -o $@ $(LDFLAGS)

editor: bin/levelEditorDebug
	./bin/levelEditorDebug

bin/levelEditorDebug: $(EDITOR_OBJS) | bin
	$(CXX) $(EDITOR_OBJS) -o $@ $(LDFLAGS)

build/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

bin:
	@mkdir -p $@

-include $(DEPS)

clean:
	rm -rf build bin
