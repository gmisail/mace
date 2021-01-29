#include "renderer.hpp"

void Renderer::update(entt::registry& registry)
{
	auto view = registry.view<Position, Renderable>();

	for(auto& entity : view)
	{
		auto& position = registry.get<Position>(entity);
		auto& renderable = registry.get<Renderable>(entity);

		renderable.transformable.setPosition(position.x, position.y);
		renderable.states = sf::RenderStates(renderable.transformable.getTransform());
	}
}

void Renderer::render(entt::registry& registry, sf::RenderWindow& window)
{
	auto view = registry.view<Renderable>();

	for(auto& entity : view)
	{
		auto& renderable = registry.get<Renderable>(entity);
		window.draw(*(renderable.object), renderable.states);
	}
}