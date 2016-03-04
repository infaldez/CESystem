#pragma once

#include "Component.h"

class ComponentCollision : public Component
{
public:
	ComponentCollision(bool(&ckey)[SIZE]);
	~ComponentCollision();
};

