#pragma once

#include "Component.h"
#include <SFML/Graphics.hpp>

class ComponentMovement : public Component
{
private:
	float rotation;
	float speed;

public:
	ComponentMovement(float speed, float rotation);
	ComponentMovement(bool(&ckey)[components::SIZE]);
	~ComponentMovement();

	void setRotation(float rotation);
	void setSpeed(float speed);

	float getRotation();
	float getSpeed();
};

