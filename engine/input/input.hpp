#ifndef INPUT
#define INPUT

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>

class Input
{
    public:
        void update(entt::registry&);
        void on(std::string, std::function<void()>);
        void emit(std::string);
    
    private:
        std::unordered_map<std::string, std::function<void()> > bindings;
};

#endif