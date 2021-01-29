#include "scripting.hpp"

#include <iostream>

void Scripting::update(entt::registry& registry, sol::state& sol)
{
	auto view = registry.view<Script>();

	for(auto& entity : view)
	{
		auto& script = registry.get<Script>(entity);
		
		sol[script.name]["update"]();
	}
}