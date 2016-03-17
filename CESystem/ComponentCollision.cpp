#include "ComponentCollision.h"


ComponentCollision::ComponentCollision(bool (&ckey)[components::SIZE])
{
	cid = components::id::COMPONENT_COLLISION;
	ckey[components::id::COMPONENT_COLLISION] = true;
}


ComponentCollision::~ComponentCollision()
{
}
