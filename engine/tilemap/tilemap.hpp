#ifndef TILEMAP
#define TILEMAP

#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>
#include <sol/sol.hpp>
#include <SFML/Graphics.hpp>

#include "tileset.hpp"
#include "chunk.hpp"
#include "../engine.hpp"

class Tilemap
{
    public:
        Tilemap(int, Engine*);
        ~Tilemap();

        void update();
        void render(sf::RenderWindow&);

    	void bindFunctions(sol::state&);

        void addChunk(ChunkCoordinate);
        std::unordered_map<int, Chunk*>::iterator removeChunk(ChunkCoordinate);
        bool chunkExists(ChunkCoordinate);
        
        void cullChunks();
    private:
        Tileset* tileset;
        Camera* camera;
        std::unordered_map<std::string, std::vector<int>> tiles;

        sf::RenderStates state;
        int seed;

        // hash maps allow for faster lookup since we can just encode a
        // chunk as (y * w + x) and use that as the key.
        std::unordered_map<int, Chunk*> chunks;
        ChunkCoordinate previousChunk{ x: 0, y: 0 };
};

#endif