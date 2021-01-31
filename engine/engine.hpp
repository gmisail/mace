#ifndef ENGINE
#define ENGINE

#include <SFML/Graphics.hpp>
#include <sol/sol.hpp>
#include <string>

#include "input/input.hpp"
#include "physics/physics.hpp"
#include "renderer/renderer.hpp"
#include "camera/camera.hpp"
#include "scripting/scripting.hpp"

#include "components/script.hpp"

class Engine
{

    public:
        Engine();
        ~Engine();

        entt::entity createEntity();
        void createScript(entt::entity entity, const std::string& name, const std::string& path);

        void update();
        void begin();
        void end();

        sf::RenderWindow* getWindow()
        {
            return &(this->window);
        }

        Camera* getCamera() 
        {
            return &(this->camera);
        }

        entt::registry* getRegistry()
        {
            return &(this->registry);
        }

        const int getWidth() const;
        const int getHeight() const;
        const float getDelta() const;

    private:
        int width;
        int height;
        int fps;

        std::string title;

        float delta;

        //entities
        entt::registry registry;

        // subsystems
        Camera camera;
        Renderer renderer;
        Input input;
        Physics physics;
        Scripting scripting;

        sol::state sol;

        sf::RenderWindow window;
        sf::Clock clock;
};

#endif