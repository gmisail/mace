#ifndef PHYSICS
#define PHYSICS

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "../input/input.hpp"
#include "../math/lerp.hpp"
#include "../components/movement.h"
#include "../components/position.h"
#include "../components/motion.h"

class Physics
{
    public:
        void update(entt::registry&, float delta, Input&);

};

#endif