#pragma once

class Component
{
public:
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
		COMPONENT_MOUSEINPUT,

		SIZE
	};
}
