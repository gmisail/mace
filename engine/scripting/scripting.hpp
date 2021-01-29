#ifndef SCRIPTING
#define SCRIPTING

#include <entt/entt.hpp>
#include <sol/sol.hpp>

#include "../components/script.hpp"

class Scripting {
public:
	void update(entt::registry&, sol::state&);
};

#endif