#include "engine.hpp"

Engine::Engine()
{
    this->sol.open_libraries(sol::lib::base, sol::lib::math, sol::lib::package);
    this->sol.script_file("config.lua");

    this->width = this->sol["window"]["width"];
    this->height = this->sol["window"]["height"];
    this->title = this->sol["window"]["title"];

    window.create(sf::VideoMode(this->width, this->height), this->title);
    window.setFramerateLimit(60);

    camera.setPosition(this->width / 2, this->height / 2);
}

Engine::~Engine()
{
    // destruction
}

entt::entity Engine::createEntity()
{
    return this->registry.create();
}

void Engine::createScript(entt::entity entity, const std::string& name, const std::string& path)
{
    this->sol.script_file(path);
    this->sol[name]["setup"]();
    this->registry.emplace<Script>(entity, name);
}

void Engine::begin()
{
    this->window.setView(*camera.getView());
    this->window.clear(sf::Color::Black);
}

void Engine::end()
{
    this->renderer.render(this->registry, this->window);

    this->window.display();
    this->delta = clock.restart().asSeconds();
}

void Engine::update()
{
    this->scripting.update(this->registry, this->sol);
    this->input.update(this->registry);
    this->physics.update(this->registry, this->delta);
    
    

    this->camera.follow(this->registry, this->delta);
    this->camera.update();
    
    this->renderer.update(this->registry);
}