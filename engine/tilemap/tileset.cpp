#include "tileset.hpp"

Tileset::Tileset(std::string& path)
{
	if(!this->texture.loadFromFile(path))
	{
        std::cout << "tileset cannot load texture" << std::endl;
    }
}

void Tileset::setTileBitmask(int tile, int bitmask)
{
	this->bitmasks.insert(std::make_pair(bitmask, tile));
}

int Tileset::getTileBitmask(int bitmask)
{
	return this->bitmasks[bitmask];
}