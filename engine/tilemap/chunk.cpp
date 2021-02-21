#include "chunk.hpp"
#include "tiles.hpp"

Chunk::Chunk(ChunkCoordinate coord, Tileset* tileset, int seed)
{
    this->coord.x = coord.x;
    this->coord.y = coord.y;
    this->tileset = tileset;

    this->vertices.setPrimitiveType(sf::Quads);
    this->vertices.resize(16 * 16 * 4);
    this->tiles.resize(16 * 16);

    this->foreground.setPrimitiveType(sf::Quads);

    // since we can't use a single seed for every chunk (it needs to be able to be reproduced at any given time),
    // predictably create a seed for each chunk by combining the (x, y) and the world seed
    srand((coord.x + coord.y * 16) + seed);

    FastNoiseLite noise(seed);
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);

    for (unsigned int i = 0; i < 16; ++i)
    {
        for (unsigned int j = 0; j < 16; ++j)
        {
            int tileNumber = TILE_GRASS;

            float val = noise.GetNoise(16 * coord.x + (float) i, 16 * coord.y + (float) j) * 25;

            if(val < 15)
                tileNumber = TILE_WATER;

            int foregroundVal = rand() % 100;
            if(foregroundVal < 13 && tileNumber != TILE_WATER)
            {
                int tile = foregroundVal < 10 ? TILE_BUSH : TILE_ROCK;
                int tu = tile % (this->tileset->getTexture()->getSize().x / TILE_SIZE);
                int tv = tile / (this->tileset->getTexture()->getSize().x / TILE_SIZE);

                sf::Vertex v1(sf::Vector2f(coord.x * (TILE_SIZE * 16) + (i * TILE_SIZE), coord.y * (TILE_SIZE * 16) + j * TILE_SIZE));
                sf::Vertex v2(sf::Vector2f(coord.x * (TILE_SIZE * 16) + (i + 1) * TILE_SIZE, coord.y * (TILE_SIZE * 16) + j * TILE_SIZE));
                sf::Vertex v3(sf::Vector2f(coord.x * (TILE_SIZE * 16) + (i + 1) * TILE_SIZE, coord.y * (TILE_SIZE * 16) + (j + 1) * TILE_SIZE));
                sf::Vertex v4(sf::Vector2f(coord.x * (TILE_SIZE * 16) + i * TILE_SIZE, coord.y * (TILE_SIZE * 16) + (j + 1) * TILE_SIZE));

                v1.texCoords = sf::Vector2f(tu * TILE_SIZE, tv * TILE_SIZE);
                v2.texCoords = sf::Vector2f((tu + 1) * TILE_SIZE, tv * TILE_SIZE);
                v3.texCoords = sf::Vector2f((tu + 1) * TILE_SIZE, (tv + 1) * TILE_SIZE);
                v4.texCoords = sf::Vector2f(tu * TILE_SIZE, (tv + 1) * TILE_SIZE);

                this->foreground.append(v1);
                this->foreground.append(v2);
                this->foreground.append(v3);
                this->foreground.append(v4);
            }

            this->tiles[j * 16 + i] = tileNumber;
            
            int tu = tileNumber % (this->tileset->getTexture()->getSize().x / 16);
            int tv = tileNumber / (this->tileset->getTexture()->getSize().x / 16);

            sf::Vertex* quad = &this->vertices[(i + j * 16) * 4];

            quad[0].position = sf::Vector2f(coord.x * (TILE_SIZE * 16) + (i * TILE_SIZE), coord.y * (TILE_SIZE * 16) + j * TILE_SIZE);
            quad[1].position = sf::Vector2f(coord.x * (TILE_SIZE * 16) + (i + 1) * TILE_SIZE, coord.y * (TILE_SIZE * 16) + j * TILE_SIZE);
            quad[2].position = sf::Vector2f(coord.x * (TILE_SIZE * 16) + (i + 1) * TILE_SIZE, coord.y * (TILE_SIZE * 16) + (j + 1) * TILE_SIZE);
            quad[3].position = sf::Vector2f(coord.x * (TILE_SIZE * 16) + i * TILE_SIZE, coord.y * (TILE_SIZE * 16) + (j + 1) * TILE_SIZE);

            quad[0].texCoords = sf::Vector2f(tu * TILE_SIZE, tv * TILE_SIZE);
            quad[1].texCoords = sf::Vector2f((tu + 1) * TILE_SIZE, tv * TILE_SIZE);
            quad[2].texCoords = sf::Vector2f((tu + 1) * TILE_SIZE, (tv + 1) * TILE_SIZE);
            quad[3].texCoords = sf::Vector2f(tu * TILE_SIZE, (tv + 1) * TILE_SIZE);
        }
    }

    autotile(noise);

    std::cout << "creating chunk at " << this->coord.x << ", " << this->coord.y << std::endl;   
}

void Chunk::setTile(int x, int y, int id)
{
    this->tiles[y * 16 + x] = id;

    int tu = id % (this->tileset->getTexture()->getSize().x / 16);
    int tv = id / (this->tileset->getTexture()->getSize().x / 16);

    sf::Vertex* quad = &this->vertices[(x + y * 16) * 4];
    quad[0].texCoords = sf::Vector2f(tu * TILE_SIZE, tv * TILE_SIZE);
    quad[1].texCoords = sf::Vector2f((tu + 1) * TILE_SIZE, tv * TILE_SIZE);
    quad[2].texCoords = sf::Vector2f((tu + 1) * TILE_SIZE, (tv + 1) * TILE_SIZE);
    quad[3].texCoords = sf::Vector2f(tu * TILE_SIZE, (tv + 1) * TILE_SIZE);        
}

void Chunk::autotile(FastNoiseLite& noise)
{
    // wont work around chunk seams for now
    for (unsigned int i = 0; i < 16; ++i)
    {
        for (unsigned int j = 0; j < 16; ++j)
        {
            if(this->tiles[j * 16 + i] == TILE_WATER)
                continue;

            int top, bottom, left, right;

            if(i == 0 || i == 15 || j == 0 || j == 15)
            {
                top = (noise.GetNoise(16 * coord.x + (float) i, 16 * coord.y + (float) j - 1) * 25) >= 15;
                bottom = (noise.GetNoise(16 * coord.x + (float) i, 16 * coord.y + (float) (j + 1)) * 25) >= 15;
                right = (noise.GetNoise(16 * coord.x + (float) (i + 1), 16 * coord.y + (float) j) * 25) >= 15;
                left = (noise.GetNoise(16 * coord.x + (float) i - 1, 16 * coord.y + (float) j) * 25) >= 15;
            }
            else
            {
                top = this->tiles[(j - 1) * 16 + i] != TILE_WATER;
                bottom = this->tiles[(j + 1) * 16 + i] != TILE_WATER;
                right = this->tiles[j * 16 + (i + 1)] != TILE_WATER;
                left = this->tiles[j * 16 + (i - 1)] != TILE_WATER;
            }

            int type = (8 * bottom) + (4 * right) + (2 * left) + (1 * top);

            setTile(i, j, this->tileset->getTileBitmask(type));
        }
    }    
}

Chunk::~Chunk()
{
    std::cout << "deleting chunk at " << this->coord.x << ", " << this->coord.y << std::endl;
}

void Chunk::render(sf::RenderWindow& window, sf::RenderStates& state)
{
    window.draw(this->vertices, state);  
    window.draw(this->foreground, state); 
}