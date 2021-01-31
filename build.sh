g++ main.cpp \
engine/engine.cpp \
engine/scripting/*.cpp \
engine/camera/*.cpp \
engine/renderer/*.cpp \
engine/input/*.cpp \
engine/tilemap/*.cpp \
engine/physics/*.cpp \
-o Tiles -Iinclude -lsfml-graphics -lsfml-window -lsfml-network -lsfml-system -Llibs -llua54 -std=c++17 -pthread
./Tiles
