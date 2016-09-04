#pragma once

#include "Component.h"
#include <SFML/Graphics.hpp>

class ComponentMovement : public Component
{
private:
	int rotation;
	int speed;

public:
	ComponentMovement(int speed, int rotation);
	ComponentMovement(bool(&ckey)[components::SIZE]);
	~ComponentMovement();

	void setRotation(int rotation);
	void setSpeed(float speed);

	int getRotation();
	int getSpeed();
};

