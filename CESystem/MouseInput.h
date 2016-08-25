#pragma once

#include "Entity.h"

class MouseInput
{
public:
	void runSystem(std::vector<Entity*>& entityList, sf::Vector2i mousePosition);

	MouseInput();
	~MouseInput();
};

