#pragma once

#include "Entity.h"

class MouseInput
{
private:
	double time;
public:
	void runSystem(std::vector<Entity*>& entityList, sf::Vector2i mousePosition, float time);

	MouseInput();
	~MouseInput();
};