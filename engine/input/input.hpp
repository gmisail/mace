#ifndef INPUT
#define INPUT

#include <SFML/Window.hpp>
#include <entt/entt.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>

class Input
{
    public:
        void update(entt::registry&);
        bool getAction(const std::string&);


        void bindButton(std::string, sf::Keyboard::Key);        // keyboard button
        void bindButton(std::string, int, int);                 // controller input
    
    private:
        std::unordered_map<std::string, bool> states;

        std::unordered_map<sf::Keyboard::Key, std::string> keyboardBindings;
        std::unordered_map<int, std::string> controllerBindings;
};

#endif