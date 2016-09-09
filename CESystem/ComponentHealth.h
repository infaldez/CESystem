#pragma once

#include "Component.h"

class ComponentHealth : public Component
{
private:
	int health;

public:
	ComponentHealth(int health);
	~ComponentHealth();

	void setHealth(int health);
	int getHealth();
};

