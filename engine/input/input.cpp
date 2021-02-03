#include "input.hpp"

void Input::update(entt::registry& registry)
{
    for (auto const& button : this->keyboardBindings)
    {
        if(sf::Keyboard::isKeyPressed(button.first))
        {
            this->states[button.second] = true;
        }
        else 
        {
            this->states[button.second] = false;
        }
    }

    for (auto const& button : this->controllerBindings)
    {
        if(sf::Joystick::isButtonPressed(0, button.first))
        {
            this->states[button.second] = true;
        }
        else 
        {
            this->states[button.second] = false;
        }
    }
}

bool Input::getAction(const std::string& action)
{
    return this->states[action];
}

void Input::bindButton(std::string name, sf::Keyboard::Key key)
{
    this->keyboardBindings[key] = name;
    this->states[name] = false;                 // the initial state of each key is false.
}

void Input::bindButton(std::string name, int controller, int button)
{
    this->controllerBindings[button] = name;        
    this->states[name] = false;
}
