#include <cmath>

#include "camera.hpp"
#include "../components/follow.h"
#include "../components/position.h"
#include "../tilemap/chunk.hpp"
#include "../math/lerp.hpp"

Camera::Camera()
{
    this->view = new sf::View();
    this->view->setCenter(0.f, 0.f);
    this->view->setSize(512.f, 360.f);

    this->motion.vx = 0;
    this->motion.vy = 0;
}

Camera::~Camera()
{
    delete this->view;
}

void Camera::setSize(float x, float y)
{
    this->view->setSize(x, y);
}

void Camera::follow(entt::registry& registry, float delta)
{
   	auto view = registry.view<Position, Follow>();

	for(auto& entity : view)
	{
		auto& position = registry.get<Position>(entity);
		auto& follow = registry.get<Follow>(entity);

        float boxOffsetX = 1024 / 2; //this->view->getViewport().left + (1024 - follow.w) / 2;
        float boxOffsetY = 720 / 2; //this->view->getViewport().top + (720 - follow.h) / 2;

        if(abs(position.x - this->view->getCenter().x) >= follow.w)
        {
            this->motion.vx = (position.x - this->view->getCenter().x) / (1 / delta);
        }
        else if(abs(this->motion.vx) > 0)
        {
            this->motion.vx = lerp(this->motion.vx, 0, 0.1);

            if(abs(this->motion.vx) < 0.005)
                this->motion.vx = 0;
        }

        if(abs(position.y - this->view->getCenter().y) >= follow.h)
        {
            this->motion.vy = (position.y - this->view->getCenter().y) / (1 / delta);   
        }
        else if(abs(this->motion.vy) > 0)
        {
            this->motion.vy = lerp(this->motion.vy, 0, 0.1);
            
            if(abs(this->motion.vy) < 0.005)
                this->motion.vy = 0;
        }

        this->moveBy(this->motion.vx, this->motion.vy);
    }
}

void Camera::update()
{
    int chunkX = (int) this->getPosition().x / (TILE_SIZE * 16);
    int chunkY = (int) this->getPosition().y / (TILE_SIZE * 16);

    if(chunkX != this->currentChunk.x || chunkY != this->currentChunk.y)
    {
        this->currentChunk = ChunkCoordinate{ x: chunkX, y: chunkY };
    }
}

void Camera::moveBy(float dx, float dy)
{
    this->view->move(dx, dy);
}

void Camera::moveTo(float x, float y)
{
    this->view->setCenter(x, y);
}