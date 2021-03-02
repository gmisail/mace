#ifndef CHUNK
#define CHUNK

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdlib.h>
#include <SFML/Graphics.hpp>

#include "tiles.hpp"
#include "tileset.hpp"
#include "biome.hpp"
#include "../util/FastNoiseLite.h"

#define TILE_SIZE 16

struct ChunkCoordinate
{
    int x;
    int y;
};

class Chunk
{
public:
    Chunk(ChunkCoordinate, Tileset*, std::unordered_map<std::string, Biome>& biomes, std::unordered_map<std::string, std::vector<int>>& tiles, int);
    ~Chunk();

    void setTile(int, int, int);
    int getTile(int, int);

    Biome* getBiome(int, int, FastNoiseLite&);
    void render(sf::RenderWindow &, sf::RenderStates &);

    const ChunkCoordinate &getCoordinate() const
    {
        return coord;
    }

private:
    Tileset* tileset;
    std::unordered_map<std::string, Biome>* biomes;
    std::unordered_map<std::string, std::vector<int>>* tileGroups;

    std::vector<int> tiles;
    sf::VertexArray vertices;
    sf::VertexArray foreground;

    ChunkCoordinate coord;

    void autotile(FastNoiseLite&);
};

inline int chunkId(ChunkCoordinate coord)
{
    return coord.y * 1000 + coord.x;
}

#endif