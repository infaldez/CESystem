#pragma once

#include <vector>
#include <memory>
#include <SFML\Graphics.hpp>

#include "Entity.h"

class MovementSystem
{
private:
	sf::Vector2f scale;
	sf::Vector2f velocity;
public:
	void runSystem(std::vector<std::unique_ptr<Entity>>& entityList);

	sf::Vector2f getNewPosition(sf::Vector2f position, sf::Vector2f velocity);

	MovementSystem();
	~MovementSystem();
};

