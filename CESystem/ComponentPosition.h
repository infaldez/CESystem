#pragma once

#include "Component.h"

#include <SFML/Graphics.hpp>

class ComponentPosition : public Component
{
public:
	ComponentPosition(sf::Vector2f position);
	~ComponentPosition();

	sf::Vector2f position;
	sf::Vector2f previousPosition;

	void setPosition(sf::Vector2f position);
	void setNewPosition(sf::Vector2f position);

	sf::Vector2f getPosition();
	sf::Vector2f getPreviousPosition();

};

