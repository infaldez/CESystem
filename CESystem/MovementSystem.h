#pragma once

#include <vector>
#include <SFML\Graphics.hpp>

#include "Entity.h"
#include "ComponentMovement.h"
#include "ComponentRender.h"

class MovementSystem
{
private:
	sf::Vector2f scale;
	sf::Vector2f velocity;
public:
	void runSystem(std::vector<Entity*> entityList);

	sf::Vector2f countScale(int rotation);
	sf::Vector2f countVelocity(sf::Vector2f scale, int speed);
	sf::Vector2i newPosition(sf::Vector2i position, sf::Vector2f velocity);

	MovementSystem();
	~MovementSystem();
};

