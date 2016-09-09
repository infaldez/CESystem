#pragma once

#include <vector>
#include "Entity.h"

#include "ComponentCollision.h"
#include "ComponentMovement.h"
#include "ComponentRender.h"

#include <unordered_map>

class CollisionSystem
{
private:
	std::unordered_map<int, std::vector<Entity*>> gridMap;

public:
	CollisionSystem();
	~CollisionSystem();

	void runSystem(std::vector<Entity*> entityList);
	int getGridPosition(ComponentRender* render);
	void createCollisionMap(std::vector<Entity*> entityList);
	void updateCollisionMap();
};

