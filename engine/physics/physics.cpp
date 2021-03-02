#include "physics.hpp"

void Physics::update(entt::registry& registry, float delta, Input& input)
{
    auto view = registry.view<Motion, Position, Movement>();

	for(auto& entity : view)
	{
        bool moving = false;
		auto& movement = registry.get<Movement>(entity);
        auto& motion = registry.get<Motion>(entity);
        auto& position = registry.get<Position>(entity);
		
        if(input.getAction("up"))
        {
            motion.vy = -movement.speed * delta; // use some sort of delta here
            moving = true;
        }
        else if(input.getAction("down"))
        {
            motion.vy = movement.speed * delta;
            moving = true;
        }
        else
        {
            motion.vy = lerp(motion.vy, 0, 0.35);
        }

        if(input.getAction("right"))
        {
            motion.vx = movement.speed * delta;
            moving = true;
        }
        else if(input.getAction("left"))
        {
            motion.vx = -movement.speed * delta;
            moving = true;
        }
        else
        {
            motion.vx = lerp(motion.vx, 0, 0.35);
        }

        // if moving in x & y directions, normalize the vector
        if(motion.vx != 0 && motion.vy != 0)
        {
            motion.vx /= 1.4; // <-- roughly the sqrt(2), faster than re-computing it 60 times a frame.
            motion.vy /= 1.4;
        }
        
        position.x += motion.vx;
        position.y += motion.vy;
    }
    
    /*
    auto colliderView = registry.view<TilemapCollider, Motion, Position>();

    for(auto& entity : view)
    {
        auto& motion = registry.get<Motion>(entity);
        auto& position = registry.get<Position>(entity);
        auto& collider = registry.get<TilemapCollider>(entity);

        if(motion.vx <= 0)
        {
            float oldY = position.y -= motion.vy;

            if(collider.tilemap->isTileSolid(position.x + 0.0f, oldY + 0.0f) || collider.tilemap->isTileSolid(position.x + 0.0f, oldY + 0.9f))
            {
                position.x = (int) position.x + 1;
                motion.vx = 0;
            }
        }
        else
        {
            float oldY = position.y -= motion.vy;

            if(collider.tilemap->isTileSolid(position.x + 1.0f, oldY + 0.0f) || collider.tilemap->isTileSolid(position.x + 1.0f, oldY + 0.9f))
            {
                position.x = (int) position.x;
                motion.vx = 0;
            }
        }

        if(motion.vy <= 0)
        {
            if(collider.tilemap->isTileSolid(position.x + 0.0f, position.y) || collider.tilemap->isTileSolid(position.x + 0.9f, position.y))
            {
                position.y = (int) position.y + 1;
                motion.vy = 0;
            }
        }
        else 
        {
            if(collider.tilemap->isTileSolid(position.x + 0.0f, position.y + 1.0f) || collider.tilemap->isTileSolid(position.x + 9.0f, position.y + 1.0f))
            {
                position.y = (int) position.y;
                motion.vy = 0;
            }
        }
    }
    */
}