#pragma once

#include "Component.h"

class ComponentCollision : public Component
{
public:
	ComponentCollision();
	ComponentCollision(bool(&ckey)[components::SIZE]);
	~ComponentCollision();
};

