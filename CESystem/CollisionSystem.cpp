#include "CollisionSystem.h"

#include <SFML\Graphics.hpp>

#include "Entity.h"
#include "componentDamage.h"
#include "ComponentHealth.h"
#include "ComponentPosition.h"
#include "ComponentAABB.h"

#include <unordered_map>
#include <algorithm>

#include <iostream>

/*
TODO
- entities can occupy more than 4 grids
- refactor everything
ISSUES
- different sized grid_rows and grid_colums cause issues
- two moving objects cause weird collisions
- sliding is slower when going right or down
*/

#define SCREENSIZE 800
#define GRID_ROWS 4
#define GRID_COLUMNS 4
#define GRID_COUNT GRID_ROWS * GRID_COLUMNS


CollisionSystem::CollisionSystem()
{
	//initialize gridMap
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
		ComponentHealth* health = ent2->getComponent<ComponentHealth>(components::COMPONENT_HEALTH);
		componentDamage* dmg = ent1->getComponent<componentDamage>(components::COMPONENT_DAMAGE);
				
		health->setHealth(health->getHealth() - dmg->getDamage());
		ent1->componentKey[components::DELETE] = true;
		if (health->getHealth() <= 0)
		{
			ent2->componentKey[components::DELETE] = true;
		}
	}
}


float sweepTestAABB(Entity* ent1, Entity* ent2, float& normalx, float& normaly)
{
	// Entity 1 AABB positions and movement
	ComponentPosition* posA = ent1->getComponent<ComponentPosition>(components::COMPONENT_POSITION);
	ComponentAABB* boxA = ent1->getComponent<ComponentAABB>(components::COMPONENT_AABB);
	ComponentMovement* movA = ent1->getComponent<ComponentMovement>(components::COMPONENT_MOVEMENT);

	// Entity 2 AABB positions
	ComponentPosition* posB = ent2->getComponent<ComponentPosition>(components::COMPONENT_POSITION);
	ComponentAABB* boxB = ent2->getComponent<ComponentAABB>(components::COMPONENT_AABB);

	sf::Vector2f pos2 = posB->getPosition();

	sf::Vector2f Ea = boxA->getExtents();
	sf::Vector2f A0 = boxA->getPosition(posA->getPreviousPosition());
	sf::Vector2f A1 = boxA->getPosition(posA->getPosition());

	sf::Vector2f Eb = boxB->getExtents();
	sf::Vector2f B0 = boxB->getPosition(posB->getPreviousPosition());
	sf::Vector2f B1 = boxB->getPosition(posB->getPosition());

	float u0 = 0.0f;
	float u1 = 1.0f;

	sf::Vector2f va = movA->getVelocity();

	sf::Vector2f u_0; // Entry time (x,y)
	sf::Vector2f u_1; // Exit time (x,y)

	float xEntryDistance, xExitDistance, yEntryDistance, yExitDistance;

	// Get the distance of entry and exit points
	if (va.x > 0.0f)
	{
		xEntryDistance = B0.x - (A0.x + Ea.x);
		xExitDistance = (B0.x + Eb.x) - A0.x;
	}
	else
	{
		xEntryDistance = (B0.x + Eb.x) - A0.x;
		xExitDistance = B0.x - (A0.x + Ea.x);
	}

	if (va.y > 0.0f)
	{
		yEntryDistance = B0.y - (A0.y + Ea.y);
		yExitDistance = (B0.y + Eb.y) - A0.y;
	}
	else
	{
		yEntryDistance = (B0.y + Eb.y) - A0.y;
		yExitDistance = B0.y - (A0.y + Ea.y);
	}

	// Get the time of collision entry and exit
	if (va.x <= 0.0001f &&  va.x >= -0.0001)
	{
		u_0.x = std::numeric_limits<float>::infinity();
		u_1.x = std::numeric_limits<float>::infinity();
	}
	else
	{
		u_0.x = xEntryDistance / va.x;
		u_1.x = xExitDistance / va.x;
	}
	if (va.y <= 0.0001f && va.y >= -0.0001)
	{
		u_0.y = std::numeric_limits<float>::infinity();
		u_1.y = std::numeric_limits<float>::infinity();
	}
	else
	{
		u_0.y = yEntryDistance / va.y;
		u_1.y = yExitDistance / va.y;
	}

	float entryTime = std::max(u_0.x, u_0.y);
	float exitTime = std::min(u_1.x, u_1.y);

	if (entryTime == std::numeric_limits<float>::infinity())
		entryTime = std::min(u_0.x, u_0.y);
	if (exitTime == std::numeric_limits<float>::infinity())
		exitTime = std::max(u_1.x, u_1.y);

	// Check if collision did not happen
	if (entryTime > exitTime || entryTime == std::numeric_limits<float>::infinity() || exitTime == std::numeric_limits<float>::infinity())
	{
		normalx = normaly = 0.0f;
		return 1.0f;
	}
	else
	{
		if (u_0.x > u_0.y && u_0.x != std::numeric_limits<float>::infinity() || u_0.y == std::numeric_limits<float>::infinity())
		{
			if (xEntryDistance < 0.0f)
			{
				normalx = 1.0f;
				normaly = 0.0f;
			}
			else
			{
				normalx = -1.0f;
				normaly = 0.0f;
			}
		}
		else
		{
			if (yEntryDistance < 0.0f)
			{
				normalx = 0.0f;
				normaly = 1.0f;
			}
			else
			{
				normalx = 0.0f;
				normaly = -1.0f;
			}
		}
		return entryTime;
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


void CollisionSystem::createCollisionMap(std::vector<std::unique_ptr<Entity>>& entityList)
{
	for (int i = 0; i < entityList.size(); ++i)
	{
		if (entityList.at(i)->componentKey[components::COMPONENT_COLLISION] == true &&
			entityList.at(i)->componentKey[components::COMPONENT_AABB] == true &&
			entityList.at(i)->componentKey[components::COMPONENT_POSITION] == true)
		{
			Entity* ent = entityList.at(i).get();
			ComponentPosition* cPosition = ent->getComponent<ComponentPosition>(components::COMPONENT_POSITION);
			ComponentAABB* cAABB = ent->getComponent<ComponentAABB>(components::COMPONENT_AABB);
			sf::Vector2i pos = (sf::Vector2i)cPosition->getPosition();
			sf::Vector2i size = (sf::Vector2i)cAABB->getExtents();
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


sf::Vector2f getNearestDisplacement(Entity* ent1, Entity* ent2)
{
	sf::Vector2f pos1 = ent1->getComponent<ComponentPosition>(components::COMPONENT_POSITION)->getPosition();
	sf::Vector2f pos2 = ent2->getComponent<ComponentPosition>(components::COMPONENT_POSITION)->getPosition();
	sf::Vector2f size1 = ent1->getComponent<ComponentAABB>(components::COMPONENT_AABB)->getExtents();
	sf::Vector2f size2 = ent2->getComponent<ComponentAABB>(components::COMPONENT_AABB)->getExtents();

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

bool aabbCheck(Entity* ent1, Entity* ent2)
{
	// Entity 1 AABB positions
	ComponentPosition* posA = ent1->getComponent<ComponentPosition>(components::COMPONENT_POSITION);
	ComponentAABB* aabbA = ent1->getComponent<ComponentAABB>(components::COMPONENT_AABB);

	sf::Vector2f pos1 = posA->getPosition();
	sf::Vector2f colPos1 = aabbA->getPosition(pos1);
	sf::Vector2f size1 = aabbA->getExtents();

	// Entity 2 AABB positions
	ComponentPosition* posB = ent2->getComponent<ComponentPosition>(components::COMPONENT_POSITION);
	ComponentAABB* aabbB = ent2->getComponent<ComponentAABB>(components::COMPONENT_AABB);

	sf::Vector2f pos2 = posB->getPosition();
	sf::Vector2f size2 = aabbB->getExtents();
	sf::Vector2f colPos2 = aabbB->getPosition(pos2);

	// Check if there's AABB overlap
	if (colPos1.x < colPos2.x + size2.x &&
		colPos1.x + size1.x > colPos2.x &&
		colPos1.y < colPos2.y + size2.y &&
		colPos1.y + size1.y > colPos2.y)
		return true;
	return false;
}

void checkCollision(std::unordered_map<int, std::vector<Entity*>>::iterator it, bool first)
{
	struct impactData
	{
		impactData(int aPos, float eTime) : arrayPos(aPos), entryTime(eTime){}

		int arrayPos;
		float entryTime;
	};


	for (std::size_t i = 0; i != it->second.size(); ++i)
	{
		std::vector<impactData> timeOfImpact; // first = j, second = entryTime, normalx, normaly

		Entity* ent1 = it->second.at(i);

		ComponentCollision* colA = ent1->getComponent<ComponentCollision>(components::COMPONENT_COLLISION);

		if (ent1->componentKey[components::COMPONENT_MOVEMENT] == true)
		{
			for (std::size_t j = 0; j != it->second.size(); ++j)
			{
				if (j != i)
				{
					Entity* ent2 = it->second.at(j);
			
					ComponentCollision* colB = ent2->getComponent<ComponentCollision>(components::COMPONENT_COLLISION);

					if (aabbCheck(ent1, ent2))
					{
						// Do a sweep test and push the results into timeOfImpact		
						float entryTime, normalx, normaly;
						entryTime = sweepTestAABB(ent1, ent2, normalx, normaly);
						timeOfImpact.push_back(impactData(j, entryTime));
					}
				}
			}
			/*
				Sort the impacts by entryTime, smallest first
			*/
			if (timeOfImpact.size() > 1)
			{
				std::sort(timeOfImpact.begin(), timeOfImpact.end(), [](const impactData &a, const impactData &b) {
					return a.entryTime < b.entryTime;
				});
			}
			
			for (auto toi_it : timeOfImpact)
			{
				// ent1
				ComponentPosition* posA = ent1->getComponent<ComponentPosition>(components::COMPONENT_POSITION);
				ComponentMovement* movA = ent1->getComponent<ComponentMovement>(components::COMPONENT_MOVEMENT);

				sf::Vector2f oldpos1 = posA->getPreviousPosition();
				sf::Vector2f v = movA->getVelocity();

				// ent2
				Entity* ent2 = it->second.at(toi_it.arrayPos);
				ComponentCollision* colB = ent2->getComponent<ComponentCollision>(components::COMPONENT_COLLISION);
				//ComponentMovement* movB = ent2->getComponent<ComponentMovement>(components::COMPONENT_MOVEMENT);
				//sf::Vector2f v2 = movB->getVelocity();

				if (aabbCheck(ent1, ent2))
				{
					// Do the health/damage thing
					if (ent2->componentKey[components::COMPONENT_HEALTH] == true)
						HealthCollision(ent1, ent2);

					// if both A and B are solid do collision things
					if (colA->getFlag(collisionType::SOLID) && colB->getFlag(collisionType::SOLID))
					{
						// if only A is moving
						if (ent2->componentKey[components::COMPONENT_MOVEMENT] == false)
						{
							float normalx;
							float normaly;

							float entryTime = sweepTestAABB(ent1, ent2, normalx, normaly);

							oldpos1.x += v.x * entryTime;
							oldpos1.y += v.y * entryTime;

							float dotproduct = (v.x * normaly + v.y * normalx) + (1.0f - entryTime);
							if (dotproduct != 1)
							{
								if (fabs(v.x) >= 0.0001f)
									oldpos1.x = oldpos1.x + (dotproduct * normaly);
								if (fabs(v.y) >= 0.0001f)
									oldpos1.y = oldpos1.y + (dotproduct * normalx);

								// set position twice so that suggested(current) and previous position are same.
								posA->setPosition(oldpos1);
								posA->setPosition(oldpos1);
							}
							else
							{
								// set position twice
								posA->setPosition(oldpos1);
								posA->setPosition(oldpos1);
							}

							float xv = dotproduct * normaly;
							float yv = dotproduct * normalx;

							if (timeOfImpact.size() > 1)
								movA->setVelocity(sf::Vector2f(xv, yv));
						}
						else // Both A and B are moving
						{
							posA->setPosition(getNearestDisplacement(ent1, ent2));
						}

					}
				}		
			}
		}
	}
}


void CollisionSystem::runSystem(std::vector<std::unique_ptr<Entity>>& entityList)
{
	clearCollisionMap();
	createCollisionMap(entityList);
	for (auto it = gridMap.begin(); it != gridMap.end(); ++it)
	{
		checkCollision(it, true);
	}
}