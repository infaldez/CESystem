#pragma once

#include "Component.h"
#include <SFML/Graphics.hpp>

class ComponentRender : public Component
{
private:
	int positionX;
	int positionY;
	sf::CircleShape shape;

public:
	ComponentRender(bool(&ckey)[SIZE]);
	~ComponentRender();

	void setPosition(int x, int y);
	int getPositionX();
	int getPositionY();
	sf::CircleShape getShape();
};