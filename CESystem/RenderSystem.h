#pragma once

#include <vector>
#include <SFML\Graphics.hpp>

#include "Entity.h"
#include "ComponentRender.h"


class RenderSystem
{
private:
	sf::RenderWindow *window;

public:
	void runSystem(std::vector<Entity*> entityList);

	RenderSystem(sf::RenderWindow& window);
	~RenderSystem();
};

