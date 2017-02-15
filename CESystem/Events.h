#pragma once

#include "Entity.h"

/*
	LOCAL COLLISION EVENTS
*/
void causeDamage(Entity* a, Entity* b);


/*
	GLOBAL COLLISION EVENTS
*/
void tagTest(std::vector<std::unique_ptr<Entity>>& entityList);