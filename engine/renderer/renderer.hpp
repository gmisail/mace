#ifndef RENDERER
#define RENDERER

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>

#include "../components/position.h"
#include "../components/renderable.h"

class Renderer {
public:
	void update(entt::registry&);
	void render(entt::registry&, sf::RenderWindow&);
};

#endif