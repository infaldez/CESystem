#pragma once

#include <vector>
#include <SFML\Graphics.hpp>

#include "Entity.h"

class MovementSystem
{
private:
	sf::Vector2f scale;
	sf::Vector2f velocity;
public:
	void runSystem(std::vector<Entity*> &entityList);

	sf::Vector2f countScale(int rotation);
	sf::Vector2f countVelocity(sf::Vector2f scale, float speed);
	sf::Vector2f newPosition(sf::Vector2f position, sf::Vector2f velocity);

	MovementSystem();
	~MovementSystem();
};

