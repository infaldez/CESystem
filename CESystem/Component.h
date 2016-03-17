#pragma once

class Component
{
protected:
	int cid;

public:
	int getComponentId();

	Component();
	~Component();
};

namespace components
{
	enum id{
		EMPTY = 0,
		COMPONENT_RENDER,
		COMPONENT_MOVEMENT,
		COMPONENT_COLLISION,
		COMPONENT_INPUT,

		SIZE
	};
}
