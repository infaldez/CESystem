#pragma once

#include "Component.h"

class componentDamage : public Component
{
private: 
	int dmg;

public:
	componentDamage(int dmg);
	~componentDamage();

	int getDamage();
	void setDamage(int dmg);
};

