#ifndef CAMERA
#define CAMERA

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>

#include "../tilemap/chunk.hpp"
#include "../components/motion.h"

class Camera 
{
    public:
        Camera();
        ~Camera();

        sf::View* getView()
        {
            return view;
        }

        void update();
        void follow(entt::registry&, float);
        void setSize(float, float);
        
        const sf::Vector2f getPosition() const
        {
            return view->getCenter();
        }

        void setPosition(float x, float y)
        {
            view->setCenter(x, y);
        }

        ChunkCoordinate getCurrentChunk() const
        {
            return currentChunk;
        }

        void moveTo(float, float);
        void moveBy(float, float);

    private:
        sf::View* view;

        Motion motion;
        ChunkCoordinate currentChunk;        
};

#endif 