#pragma once

class Component
{
public:
	Component();
	~Component();
};

enum Comp{
	EMPTY = 0,
	COMPONENT_PLAYER,
	COMPONENT_RENDER,
	COMPONENT_TEST,

	SIZE
};