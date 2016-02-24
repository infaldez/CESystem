#pragma once

#include <vector>
#include "Entity.h"
#include <SFML\Graphics.hpp>

class RenderSystem
{
public:
	std::vector<Entity*> entityList;
	sf::RenderWindow *window;

	void AddEntity(Entity *entity);
	void RunSystem();

	RenderSystem(sf::RenderWindow&);
	~RenderSystem();
};
