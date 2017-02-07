#pragma once
namespace components
{
	enum id{
		EMPTY = 0,
		COMPONENT_RENDER,
		COMPONENT_MOVEMENT,
		COMPONENT_COLLISION,
		COMPONENT_INPUT,
		COMPONENT_MOUSEINPUT,
		COMPONENT_HEALTH,
		COMPONENT_DAMAGE,
		COMPONENT_AABB,
		COMPONENT_POSITION,

		DELETE,
		SIZE
	};
}

class Component
{
public:
	int cId;
	Component(enum components::id cid);
	~Component();
};