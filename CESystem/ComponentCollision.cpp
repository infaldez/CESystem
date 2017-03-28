#include "ComponentCollision.h"


ComponentCollision::ComponentCollision(bool solid) : Component(components::id::COMPONENT_COLLISION)
{
	for (int i = 0; i < collisionType::COUNT; i++) {
		_flags[i] = false;
	}
	_flags[SOLID] = solid;
}


ComponentCollision::~ComponentCollision()
{
}