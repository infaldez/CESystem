#include "ComponentCollision.h"


ComponentCollision::ComponentCollision(bool (&ckey)[components::SIZE])
{
	ckey[components::id::COMPONENT_COLLISION] = true;
}


ComponentCollision::~ComponentCollision()
{
}
