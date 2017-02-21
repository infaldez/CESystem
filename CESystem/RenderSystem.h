#pragma once

#include <vector>
#include <memory>
#include <SFML\Graphics.hpp>

#include "Entity.h"
#include "ComponentRender.h"


class RenderSystem
{
private:
	std::clock_t _dt;
	sf::RenderWindow* window;

public:
	void runSystem(std::vector<std::unique_ptr<Entity>>& entityList, std::vector<std::string> tilesets, std::clock_t dt);

	RenderSystem(sf::RenderWindow& window);
	~RenderSystem();
};

