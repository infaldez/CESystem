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
	
	std::vector<int> getGridPositions(sf::Vector2i position, sf::Vector2i size);
	void createCollisionMap(std::vector<Entity*> entityList);
	void clearCollisionMap();

public:
	CollisionSystem();
	~CollisionSystem();

	void runSystem(std::vector<Entity*> entityList);
};

