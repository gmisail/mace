#include "tilemap.hpp"
#include "tiles.hpp"

#include <sol/sol.hpp>

Tilemap::Tilemap(int seed)
{
    std::cout << "creating tilemap " << std::endl;

    this->seed = seed;

    std::string path = "assets/autotile.png";

    this->tileset = new Tileset(path);
    this->tileset->setTileBitmask(0, 0); //
    this->tileset->setTileBitmask(1, 1);  //
    this->tileset->setTileBitmask(2, 2);
    this->tileset->setTileBitmask(3, 3);
    this->tileset->setTileBitmask(4, 4);
    this->tileset->setTileBitmask(5, 5);
    this->tileset->setTileBitmask(6, 6);
    this->tileset->setTileBitmask(7, 7);    //
    this->tileset->setTileBitmask(8, 8);
    this->tileset->setTileBitmask(9, 9);   //
    this->tileset->setTileBitmask(10, 10);
    this->tileset->setTileBitmask(11, 11);
    this->tileset->setTileBitmask(12, 12);   //
    this->tileset->setTileBitmask(13, 13);  //
    this->tileset->setTileBitmask(14, 14);   //
    this->tileset->setTileBitmask(15, 15);  //
 
    this->state.texture = this->tileset->getTexture();
}

Tilemap::~Tilemap()
{
    std::cout << "deleting tilemap" << std::endl;

    delete this->tileset;

    for(const auto &[key, value] : this->chunks)
    {
        Chunk* chunk = value;
        delete chunk;
    }
}

void Tilemap::addChunk(ChunkCoordinate coord)
{
    std::unordered_map<int, Chunk*>::iterator existingChunk = this->chunks.find(coord.y * 16 + coord.x);

    if(existingChunk != this->chunks.end()) 
        return;

    Chunk* chunk = new Chunk(coord, this->tileset, this->seed);
    this->chunks.insert(std::make_pair(coord.y * 16 + coord.x, chunk));
}

std::unordered_map<int, Chunk*>::iterator Tilemap::removeChunk(ChunkCoordinate coord)
{
    std::unordered_map<int, Chunk*>::iterator chunk = this->chunks.find(coord.y * 16 + coord.x);
    
    if(chunk == this->chunks.end())
    {
        std::cout << "Chunk (" << coord.x << ", " << coord.y << ") does not exist" << std::endl;
    }
    else
    {
        Chunk* addr = chunk->second;
        delete addr;
        
        return this->chunks.erase(chunk);
    } 

    return this->chunks.end();
}

void Tilemap::cullChunks(Camera& camera)
{
    int added = 0;
    int removed = 0;

    ChunkCoordinate coord = camera.getCurrentChunk();

    for(int i = -1; i < 2; i++)
    {
        for(int j = -1; j < 2; j++)
        {            
            addChunk(ChunkCoordinate{ x: coord.x + i, y: coord.y + j });
        }
    }

    for(std::unordered_map<int, Chunk*>::iterator itr = this->chunks.begin(); itr != this->chunks.end(); )
    {
        Chunk* chunk = itr->second;

        // make sure that its within 1 chunk of the camera
        if(abs(chunk->getCoordinate().x - camera.getCurrentChunk().x) > 1 || abs(chunk->getCoordinate().y - camera.getCurrentChunk().y) > 1)
        {
            itr = removeChunk(chunk->getCoordinate());
            removed++;
        }
        else
        {
            itr++;
        }
    }

    std::cout << " ======== active " << std::to_string(this->chunks.size()) << ", added " << added << ", removed " << removed << " ========" << std::endl;
}

void Tilemap::bindFunctions(sol::state& lua)
{
    lua.set_function("RegisterBitwiseTile", [](){
        std::cout << "register bitwise" << std::endl;
    });
}

void Tilemap::update(Camera& camera)
{       
    if(this->previousChunk.x != camera.getCurrentChunk().x || this->previousChunk.y != camera.getCurrentChunk().y)
    {
        this->cullChunks(camera);

        this->previousChunk.x = camera.getCurrentChunk().x;
        this->previousChunk.y = camera.getCurrentChunk().y;
    }
}

void Tilemap::render(sf::RenderWindow& window)
{
    for(const auto &[key, value] : this->chunks)
    {
        Chunk* chunk = value;

        if(chunk)
            chunk->render(window, this->state);
    }
}