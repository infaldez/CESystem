#pragma once

#include <vector>
#include "Entity.h"

#include "ComponentCollision.h"
#include "ComponentMovement.h"
#include "ComponentRender.h"

class CollisionSystem
{
public:
	CollisionSystem();
	~CollisionSystem();

	void runSystem(std::vector<Entity*> entityList);

};

