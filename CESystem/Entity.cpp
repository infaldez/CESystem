#include "Entity.h"


Entity::Entity()
{	
	for (int i = 0; i < components::SIZE; i++)
	{
		componentKey[i] = false;
	}
	//componentKey[components::id::SIZE] = { false };
}


Entity::~Entity()
{
}

