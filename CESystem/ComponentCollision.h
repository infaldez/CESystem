#pragma once

#include "Component.h"

enum collisionType{
	SOLID,

	COUNT
};

class ComponentCollision : public Component
{
private:
	bool flags[collisionType::COUNT];

public:
	ComponentCollision();
	~ComponentCollision();

	void setFlag(collisionType cType, bool state) {
		flags[cType] = state;
	}

	bool getFlag(collisionType cType) {
		return flags[cType];
	}
};

