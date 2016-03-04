#pragma once

#include <vector>
#include "Entity.h"

class CollisionSystem
{
public:
	CollisionSystem();
	~CollisionSystem();

	void runSystem(std::vector<Entity*> &entityList);

};

