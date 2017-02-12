#pragma once

#include "Entity.h"

class MouseInput
{
private:
	double time;
public:
	void runSystem(std::vector<std::unique_ptr<Entity>>& entityList, sf::Vector2i mousePosition, float time);

	MouseInput();
	~MouseInput();
};