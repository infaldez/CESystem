#include "ComponentCollision.h"


ComponentCollision::ComponentCollision() : Component(components::id::COMPONENT_COLLISION)
{
	for (int i = 0; i < collisionType::COUNT; i++) {
		flags[i] = false;
	}
}


ComponentCollision::~ComponentCollision()
{
}