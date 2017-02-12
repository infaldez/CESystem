#pragma once

#include <vector>
#include <memory>
#include <SFML\Graphics.hpp>

#include "Entity.h"
#include "ComponentRender.h"


class RenderSystem
{
private:
	sf::RenderWindow *window;

public:
	void runSystem(std::vector<std::unique_ptr<Entity>>& entityList);

	RenderSystem(sf::RenderWindow& window);
	~RenderSystem();
};

