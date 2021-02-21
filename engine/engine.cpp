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

    camera.setSize(this->width / 4, this->height / 4);
    camera.setPosition(0, 0);//this->width / 2, this->height / 2);
}

Engine::~Engine()
{
    // destruction
}

entt::entity Engine::createEntity()
{
    return this->registry.create();
}

void Engine::runScript(const std::string& path)
{
    this->sol.script_file(path);
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

void Engine::onResize(sf::Event& event)
{
  //  this->camera.getView()->zoom((event.size.width / (float) event.size.height) / (1 / (this->width / height)));
    //this->camera.getView()->setSize(sf::Vector2f(event.size.width / 2, event.size.height / 2));
}

void Engine::update()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        
        if(event.type == sf::Event::Resized)
            this->onResize(event);
    }

    this->scripting.update(this->registry, this->sol);
    this->input.update(this->registry);
    this->physics.update(this->registry, this->delta, this->input);
    
    this->renderer.update(this->registry);

    this->camera.follow(this->registry, this->delta);
    this->camera.update();
}