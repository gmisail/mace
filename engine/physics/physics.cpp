#include "physics.hpp"
#include "../math/lerp.hpp"
#include "../components/movement.h"
#include "../components/position.h"
#include "../components/motion.h"

#include <iostream>

void Physics::update(entt::registry& registry, float delta)
{
    auto view = registry.view<Motion, Position, Movement>();

	for(auto& entity : view)
	{
        bool moving = false;
		auto& movement = registry.get<Movement>(entity);
        auto& motion = registry.get<Motion>(entity);
        auto& position = registry.get<Position>(entity);
		
        if(sf::Keyboard::isKeyPressed(movement.up))
        {
            motion.vy = -movement.speed * delta; // use some sort of delta here
            moving = true;
        }
        else if(sf::Keyboard::isKeyPressed(movement.down))
        {
            motion.vy = movement.speed * delta;
            moving = true;
        }
        else
        {
            motion.vy = lerp(motion.vy, 0, 0.5);
        }

        if(sf::Keyboard::isKeyPressed(movement.right))
        {
            motion.vx = movement.speed * delta;
            moving = true;
        }
        else if(sf::Keyboard::isKeyPressed(movement.left))
        {
            motion.vx = -movement.speed * delta;
            moving = true;
        }
        else
        {
            motion.vx = lerp(motion.vx, 0, 0.5);
        }

        // if moving in x & y directions, normalize the vector
        if(motion.vx != 0 && motion.vy != 0)
        {
            motion.vx /= 1.41421; // <-- roughly the sqrt(2), faster than re-computing it 60 times a frame.
            motion.vy /= 1.41421;
        }
        
        position.x += motion.vx;
        position.y += motion.vy;
    }
    // run physics simulation 
}