#ifndef CHUNK
#define CHUNK

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <SFML/Graphics.hpp>

#include "tileset.hpp"
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
    Chunk(ChunkCoordinate, Tileset*, int);
    ~Chunk();

    void setTile(int, int, int);
    void render(sf::RenderWindow &, sf::RenderStates &);

    const ChunkCoordinate &getCoordinate() const
    {
        return coord;
    }

private:
    Tileset* tileset;

    std::vector<int> tiles;
    sf::VertexArray vertices;
    sf::VertexArray foreground;

    ChunkCoordinate coord;

    void autotile(FastNoiseLite&);
};

#endif