#include "ComponentCollision.h"


ComponentCollision::ComponentCollision(bool (&ckey)[SIZE])
{
	ckey[COMPONENT_COLLISION] = true;
}


ComponentCollision::~ComponentCollision()
{
}
