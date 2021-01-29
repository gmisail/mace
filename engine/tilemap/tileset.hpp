#ifndef TILESET
#define TILESET

#include <string>
#include <iostream>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <sol/sol.hpp>

class Tileset
{
public:
	Tileset(std::string&);

	int getTile(int, int) const;

	const sf::Texture* getTexture() const
	{
		return &texture;
	}

	void setTileBitmask(int, int);
	int getTileBitmask(int);

private:
	sf::Texture texture;
	std::unordered_map<int, int> bitmasks;
};

#endif