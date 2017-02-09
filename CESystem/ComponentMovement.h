#pragma once

#include "Component.h"
#include <SFML/Graphics.hpp>

class ComponentMovement : public Component
{
private:
	float rotation;
	float speed;
	sf::Vector2f scale;
	sf::Vector2f velocity;

	void _setVelocity(float rotation, float speed);

public:
	ComponentMovement(float speed, float rotation);
	~ComponentMovement();

	void setRotation(float rotation);
	void setSpeed(float speed);
	void setVelocity(sf::Vector2f velocity);

	sf::Vector2f getVelocity();
	sf::Vector2f getScale();
	float getRotation();
	float getSpeed();
};

