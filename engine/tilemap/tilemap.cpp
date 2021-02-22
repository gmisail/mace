#include "tilemap.hpp"
#include "tiles.hpp"

#include <sol/sol.hpp>

Tilemap::Tilemap(int seed, Engine* engine)
{
    std::cout << "creating tilemap " << std::endl;

    this->camera = engine->getCamera();
    this->seed = seed;

    std::string path = "assets/autotile.png";

    this->tileset = new Tileset(path);

    auto world = (*engine->getScripting())["world"].get_or_create<sol::table>();
    auto blocks = world["blocks"].get_or_create<sol::table>();
    //auto biomes = world["biomes"].get_or_create<sol::table>();

    blocks.set_function("add", [this](int tile, int bitmask){
        this->tileset->setTileBitmask(tile, bitmask);
    });

    blocks.set_function("addGroup", [this](std::string name, std::vector<int> tileGroup){
        this->tiles[name] = std::vector(tileGroup);
    });

    blocks.set_function("addBiome", [this](std::string name, std::string tiles, float lowerHeight, float upperHeight){
        std::cout << "adding biome" << std::endl;
        this->biomes[name] = Biome{ tiles: tiles, name: name, lowerHeight: lowerHeight, upperHeight: upperHeight };
    });

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

    Chunk* chunk = new Chunk(coord, this->tileset, this->biomes, this->tiles, this->seed);
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

void Tilemap::cullChunks()
{
    int added = 0;
    int removed = 0;

    ChunkCoordinate coord = this->camera->getCurrentChunk();

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
        if(abs(chunk->getCoordinate().x - this->camera->getCurrentChunk().x) > 1 || abs(chunk->getCoordinate().y - this->camera->getCurrentChunk().y) > 1)
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
    
}

void Tilemap::update()
{       
    if(this->previousChunk.x != this->camera->getCurrentChunk().x || this->previousChunk.y != this->camera->getCurrentChunk().y)
    {
        this->cullChunks();

        this->previousChunk.x = this->camera->getCurrentChunk().x;
        this->previousChunk.y = this->camera->getCurrentChunk().y;
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