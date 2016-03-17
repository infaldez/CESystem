#pragma once

#include "Component.h"
#include <SFML/Graphics.hpp>

class ComponentRender : public Component
{
private:
	sf::CircleShape shape;

public:
	ComponentRender(bool(&ckey)[components::SIZE]);
	~ComponentRender();

	void setPosition(sf::Vector2f);
	float getPositionX();
	float getPositionY();
	sf::CircleShape getShape();
};