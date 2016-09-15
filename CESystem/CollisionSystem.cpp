#include "CollisionSystem.h"

#include <SFML\Graphics.hpp>

#include "Entity.h"
#include "componentDamage.h"
#include "ComponentHealth.h"

#include <unordered_map>

#include <iostream>

/*
 TODO 
 - entities can occupy more than 4 grids
 - refactor everything
 ISSUES
 - different sized grid_rows and grid_colums cause issues
 - if two or moving objects collide the later in the entitylist "pushes" the other
 */

#define SCREENSIZE 800
#define GRID_ROWS 8
#define GRID_COLUMNS 8
#define GRID_COUNT GRID_ROWS * GRID_COLUMNS
CollisionSystem::CollisionSystem()
{
	//initialize gridmap
	for (int i = 0; i < GRID_COUNT; ++i)
	{
		this->gridMap.insert(std::pair<int, std::vector<Entity*>>(i, std::vector<Entity*>()));
	}
}


CollisionSystem::~CollisionSystem()
{
}

//TODO move this to somewhere else
void HealthCollision(Entity* ent1, Entity* ent2)
{
	if (ent1->componentKey[components::COMPONENT_DAMAGE] == true)
	{
		ComponentHealth* health = ent1->getComponent<ComponentHealth>(components::COMPONENT_HEALTH);
		componentDamage* dmg = ent2->getComponent<componentDamage>(components::COMPONENT_DAMAGE);

		health->setHealth(health->getHealth() - dmg->getDamage());
		ent2->componentKey[components::DELETE] = true;
		if (health->getHealth() <= 0)
		{
			ent1->componentKey[components::DELETE] = true;
		}
	}	
}

// returns position 1
int getGridPos1(sf::Vector2i pos)
{
	pos.x = pos.x / (SCREENSIZE / GRID_COLUMNS);
	pos.y = pos.y / (SCREENSIZE / GRID_ROWS);
	return pos.x + pos.y * GRID_ROWS;
}

// returns position 2
int getGridPos2(sf::Vector2i pos, sf::Vector2i size)
{
	int x = (pos.x + size.x) / (SCREENSIZE / GRID_COLUMNS);
	int y = pos.y / (SCREENSIZE / GRID_ROWS);
	return x + y * GRID_ROWS;
}

// returns position 3
int getGridPos3(sf::Vector2i pos, sf::Vector2i size)
{
	int x = (pos.x + size.x) / (SCREENSIZE / GRID_COLUMNS);
	int y = (pos.y + size.y) / (SCREENSIZE / GRID_ROWS);
	return x + y * GRID_ROWS;
}

// returns position 4
int getGridPos4(sf::Vector2i pos, sf::Vector2i size)
{
	int x = pos.x / (SCREENSIZE / GRID_COLUMNS);
	int y = (pos.y + size.y) / (SCREENSIZE / GRID_ROWS);
	return x + y * GRID_ROWS;
}


std::vector<int> CollisionSystem::getGridPositions(sf::Vector2i position, sf::Vector2i size)
{
	std::vector<int> positions;

	positions.push_back(getGridPos1(position));
	positions.push_back(getGridPos2(position, size));
	positions.push_back(getGridPos3(position, size));
	positions.push_back(getGridPos4(position, size));

	return positions;
}


void CollisionSystem::createCollisionMap(std::vector<Entity*> entityList) 
{
	for (int i = 0; i < entityList.size(); ++i)
	{
		if (entityList.at(i)->componentKey[components::COMPONENT_COLLISION] == true &&
			entityList.at(i)->componentKey[components::COMPONENT_RENDER] == true)
		{
			Entity* ent = entityList.at(i);
			ComponentRender* cRender = entityList.at(i)->getComponent<ComponentRender>(components::COMPONENT_RENDER);
			sf::Vector2i pos = (sf::Vector2i)cRender->getPosition();
			sf::Vector2i size = (sf::Vector2i)cRender->getTileSize();
			std::vector<int> positions = getGridPositions(pos, size);
			
			if (positions[0] < GRID_COUNT && 
				positions[0] >= 0)
					gridMap.find(positions[0])->second.push_back(ent);

			if (positions[1] != positions[0] && 
				positions[1] < GRID_COUNT &&
				positions[1] >= 0)
					gridMap.find(positions[1])->second.push_back(ent);

			if (positions[2] != positions[1] && 
				positions[2] != positions[3] &&
				positions[2] < GRID_COUNT &&
				positions[2] >= 0) 
					gridMap.find(positions[2])->second.push_back(ent);

			if (positions[3] != positions[0] && 
				positions[3] < GRID_COUNT && 
				positions[3] >= 0)
					gridMap.find(positions[3])->second.push_back(ent);
		}
	}
}


void CollisionSystem::clearCollisionMap()
{
	for (auto it = gridMap.begin(); it != gridMap.end(); ++it)
		it->second.clear();
}


sf::Vector2f getNearestDisplacement(sf::Vector2f pos1, sf::Vector2f pos2, sf::Vector2u size1, sf::Vector2u size2)
{
	sf::Vector2f nearestPoint = pos1;
	
	sf::Vector2f center1(pos1.x + (size1.x / 2), pos1.y + (size1.y / 2));
	sf::Vector2f center2(pos2.x + (size2.x / 2), pos2.y + (size2.y / 2));

	//center distance x, y
	float cdx = fabs(center1.x - center2.x);
	float cdy = fabs(center1.y - center2.y);

	float overlapx = ((size1.x + size2.x) / 2) - cdx;
	float overlapy = ((size1.y + size2.y) / 2) - cdy;
	
	if (overlapx * overlapx < overlapy * overlapy)
	{
		if (center1.x > center2.x)
			nearestPoint.x = pos1.x + overlapx;
		else
			nearestPoint.x = pos1.x - overlapx;
	}
	else
	{	
		if (center1.y > center2.y)
			nearestPoint.y = pos1.y + overlapy;
		else
			nearestPoint.y = pos1.y - overlapy;
	}

	return nearestPoint;
}


void CollisionSystem::runSystem(std::vector<Entity*> entityList)
{
	clearCollisionMap();
	createCollisionMap(entityList);
	for (auto it = gridMap.begin(); it != gridMap.end(); ++it)
	{
		for (int i = 0; i < it->second.size(); ++i)
		{	
			Entity* ent1 = it->second.at(i);
			ComponentRender* render1 = ent1->getComponent<ComponentRender>(components::COMPONENT_RENDER);
			ComponentCollision* col1 = ent1->getComponent<ComponentCollision>(components::COMPONENT_COLLISION);
			
			sf::Vector2f pos1 = render1->getPosition();
			sf::Vector2u size1 = render1->getTileSize();
			
			if (ent1->componentKey[components::COMPONENT_MOVEMENT] == true)
			{
				for (int j = 0; j < it->second.size(); ++j)
				{
					if (j != i)
					{
						Entity* ent2 = it->second.at(j);
						ComponentRender* render2 = ent2->getComponent<ComponentRender>(components::COMPONENT_RENDER);
						ComponentCollision* col2 = ent2->getComponent<ComponentCollision>(components::COMPONENT_COLLISION);

						sf::Vector2f pos2 = render2->getPosition();
						sf::Vector2u size2 = render2->getTileSize();

						if (pos1.x < pos2.x + size2.x &&
							pos1.x + size1.x > pos2.x &&
							pos1.y < pos2.y + size2.y &&
							pos1.y + size1.y > pos2.y)
						{
							
							if (col1->getFlag(collisionType::SOLID) && col2->getFlag(collisionType::SOLID))	
								render1->setPosition(getNearestDisplacement(pos1, pos2, size1, size2));


							if (ent2->componentKey[components::COMPONENT_HEALTH] == true)
								HealthCollision(ent1, ent2);
						}
					}
				}
			}
		}
	}
}