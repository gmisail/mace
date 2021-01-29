#ifndef PHYSICS
#define PHYSICS

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>

class Physics
{
    public:
        void update(entt::registry&, float delta);

};

#endif