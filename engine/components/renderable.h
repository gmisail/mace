#ifndef RENDERABLE
#define RENDERABLE

#include <SFML/Graphics.hpp>

struct Renderable {
	sf::Drawable* object;
	sf::RenderStates states;
	sf::Transformable transformable;
};

#endif