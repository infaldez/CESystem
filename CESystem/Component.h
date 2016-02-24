#pragma once

class Component
{
public:
	Component();
	~Component();
};

enum Comp{
	EMPTY = 0,
	COMPONENT_RENDER,
	COMPONENT_MOVEMENT,
	COMPONENT_COLLISION,
	COMPONENT_INPUT,

	SIZE
};