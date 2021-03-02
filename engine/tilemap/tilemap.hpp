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
#include "biome.hpp"
#include "../engine.hpp"

class Engine;

class Tilemap
{
    public:
        Tilemap(int, Engine*);
        ~Tilemap();

        void update();
        void render(sf::RenderWindow&);

    	void bindFunctions(sol::state&);

        void addChunk(ChunkCoordinate);
        Chunk* getChunk(ChunkCoordinate);
        std::unordered_map<int, Chunk*>::iterator removeChunk(ChunkCoordinate);
        bool chunkExists(ChunkCoordinate);

        int getTile(int, int);
        bool isTileSolid(int, int);
        
        void cullChunks();
    private:
        Tileset* tileset;
        Camera* camera;

        std::vector<bool> tileType;
        std::unordered_map<std::string, std::vector<int>> tiles;
        std::unordered_map<std::string, Biome> biomes;

        sf::RenderStates state;
        int seed;

        // hash maps allow for faster lookup since we can just encode a
        // chunk as (y * w + x) and use that as the key.
        std::unordered_map<int, Chunk*> chunks;
        ChunkCoordinate previousChunk{ x: 0, y: 0 };
};

#endif