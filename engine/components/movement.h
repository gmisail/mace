#ifndef MOVEMENT
#define MOVEMENT

#include <SFML/Graphics.hpp>

struct Movement 
{
    sf::Keyboard::Key up;
    sf::Keyboard::Key down;
    sf::Keyboard::Key left;
    sf::Keyboard::Key right;

    float speed;
};

#endif