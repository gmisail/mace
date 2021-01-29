#include "input.hpp"

void Input::update(entt::registry& registry)
{
    //auto view = registry.view<
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        this->emit("left");
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        this->emit("right");
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        this->emit("up");
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        this->emit("down");
    }
}

void Input::on(std::string name, std::function<void()> callback)
{
    this->bindings.insert(std::make_pair(name, callback));
}

void Input::emit(std::string name)
{
    std::unordered_map<std::string, std::function<void()>>::iterator callback = this->bindings.find(name);
    
    if(callback == this->bindings.end())
    {
        std::cerr << "Cannot find event with name " << name << std::endl;
        return;
    }

    callback->second();
}   