#include "ComponentCollision.h"


ComponentCollision::ComponentCollision()
{
	cId = components::COMPONENT_COLLISION;
}


ComponentCollision::ComponentCollision(bool (&ckey)[components::SIZE])
{
	cId = components::COMPONENT_COLLISION;
	ckey[components::id::COMPONENT_COLLISION] = true;
}


ComponentCollision::~ComponentCollision()
{
}
