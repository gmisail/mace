#ifndef TILEMAP
#define TILEMAP

#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>
#include <mutex>
#include <future>
#include <SFML/Graphics.hpp>

#include "tileset.hpp"
#include "chunk.hpp"
#include "../camera/camera.hpp"

class Tilemap
{
    public:
        Tilemap(int);
        ~Tilemap();

        void update(Camera&);
        void render(sf::RenderWindow&);

    	void bindFunctions(sol::state&);

        void addChunk(ChunkCoordinate);
        std::unordered_map<int, Chunk*>::iterator removeChunk(ChunkCoordinate);
        bool chunkExists(ChunkCoordinate);
        
        void cullChunks(Camera&);
    private:
        Tileset* tileset;
        sf::RenderStates state;
        int seed;
        
        // hash maps allow for faster lookup since we can just encode a
        // chunk as (y * w + x) and use that as the key.
        std::unordered_map<int, Chunk*> chunks;
        ChunkCoordinate previousChunk{ x: 0, y: 0 };
};

#endif