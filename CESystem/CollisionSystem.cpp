#include "CollisionSystem.h"

#include <SFML\Graphics.hpp>

#include "Entity.h"
#include "componentDamage.h"
#include "ComponentHealth.h"

#include <unordered_map>

#include <iostream>

/*
 TODO refactor everything
 - update grid when entities are added/deleted
 - update grid if entities move
 */

#define SCREENSIZE 800
#define GRID_COUNT 8
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
	if (ent2->componentKey[components::COMPONENT_DAMAGE] == true)
	{
		std::cout << "PAM" << std::endl;
		ComponentHealth* health = ent1->getComponent<ComponentHealth>(components::COMPONENT_HEALTH);
		componentDamage* dmg = ent2->getComponent<componentDamage>(components::COMPONENT_DAMAGE);

		std::cout << health->getHealth() << std::endl;
		health->setHealth(health->getHealth() - dmg->getDamage());
		if (health->getHealth() <= 0)
		{
			ent1->componentKey[components::DELETE] = true;
		}
	}	
}


int CollisionSystem::getGridPosition(ComponentRender* render)
{
	return render->getPosition().x / ( SCREENSIZE / GRID_COUNT );
}


int getGridPositionEnd(ComponentRender* render)
{
	return (render->getPosition().x + render->getTileSize().x) / (SCREENSIZE / GRID_COUNT);
}


void CollisionSystem::createCollisionMap(std::vector<Entity*> entityList) 
{
	for (int i = 0; i < entityList.size(); ++i)
	{
		if (entityList.at(i)->componentKey[components::COMPONENT_COLLISION] == true &&
			entityList.at(i)->componentKey[components::COMPONENT_RENDER] == true)
		{
			ComponentRender* cRender = entityList.at(i)->getComponent<ComponentRender>(components::COMPONENT_RENDER);
			Entity* ent = entityList.at(i);

			std::unordered_map<int, std::vector<Entity*>>::iterator it = gridMap.find(getGridPosition(cRender));
			it->second.push_back(ent);
			
			if (getGridPosition(cRender) != getGridPositionEnd(cRender))
			{
				it = gridMap.find(getGridPositionEnd(cRender));
				it->second.push_back(ent);
			}
		}
	}
}


void CollisionSystem::updateCollisionMap()
{
	for (auto it = gridMap.begin(); it != gridMap.end(); ++it)
	{
		std::vector<Entity*>::iterator eit = it->second.begin();
		while (eit != it->second.end())
		{
			if ((*eit)->componentKey[components::COMPONENT_MOVEMENT] == true)
			{
				ComponentRender* cRender = (*eit)->getComponent<ComponentRender>(components::COMPONENT_RENDER);
				
				/*if (getGridPositionEnd(cRender) != it->first)
				{
					Entity* ent = *eit;
					gridMap.find(getGridPositionEnd(cRender))->second.push_back(ent);
				}*/

				if (getGridPosition(cRender) != it->first)
				{
					Entity* ent = *eit;
					gridMap.find(getGridPosition(cRender))->second.push_back(ent);

					eit = it->second.erase(eit);
				}
				else { ++eit; }
			}
		}
	}
}


void CollisionSystem::runSystem(std::vector<Entity*> entityList)
{
	updateCollisionMap();
	for (auto it = gridMap.begin(); it != gridMap.end(); ++it)
	{
		for (int i = 0; i < it->second.size(); ++i)
		{	
			Entity* ent1 = it->second.at(i);
			ComponentRender* render1 = ent1->getComponent<ComponentRender>(components::COMPONENT_RENDER);
			ComponentCollision* col1 = ent1->getComponent<ComponentCollision>(components::COMPONENT_COLLISION);
			
			sf::Vector2f pos1 = render1->getPosition();
			sf::Vector2u size1 = render1->getTileSize();
			
			for (int j = i + 1; j < it->second.size(); ++j)
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
					if (col1->getFlag(collisionType::SOLID) &&
						col2->getFlag(collisionType::SOLID))
					{
						render1->resetToOldPosition();
						render2->resetToOldPosition();
					}

					if (ent1->componentKey[components::COMPONENT_HEALTH] == true)
						HealthCollision(ent1, ent2);
				}
			}
		}
	}
}

/*void CollisionSystem::runSystem(std::vector<Entity*> entityList)
{		
	for (int i = 0; i < entityList.size(); ++i)
	{	
		std::array<bool, components::SIZE> cKeyi = entityList.at(i)->componentKey;
		
		if (cKeyi[components::COMPONENT_RENDER] == true &&
			cKeyi[components::COMPONENT_COLLISION] == true)
		{	
			Entity* ent_i = entityList.at(i);
			ComponentRender* render_i = ent_i->getComponent<ComponentRender>(components::COMPONENT_RENDER);
			ComponentCollision* col_i = ent_i->getComponent<ComponentCollision>(components::COMPONENT_COLLISION);

			sf::Vector2f pos_i = render_i->getPosition();
			sf::Vector2u size_i = render_i->getTileSize();

			//check for collisions with other entities
			for (int j = i + 1; j < entityList.size(); ++j)
			{
				std::array<bool, components::SIZE> cKeyj = entityList.at(i)->componentKey;

				if (cKeyj[components::COMPONENT_RENDER] == true &&
					cKeyj[components::COMPONENT_COLLISION] == true &&
					j != i)
				{
					Entity* ent_j = entityList.at(j);
					ComponentRender* render_j = ent_j->getComponent<ComponentRender>(components::COMPONENT_RENDER);
					ComponentCollision* col_j = ent_j->getComponent<ComponentCollision>(components::COMPONENT_COLLISION);
					
					sf::Vector2f pos_j = render_j->getPosition();
					sf::Vector2u size_j = render_j->getTileSize();

					//AABB
					if (pos_i.x < pos_j.x + size_j.x &&
						pos_i.x + size_i.x > pos_j.x &&
						pos_i.y < pos_j.y + size_j.y &&
						pos_i.y + size_i.y > pos_j.y)
					{
						//Collision action
						if (col_i->getFlag(collisionType::SOLID) &&
							col_j->getFlag(collisionType::SOLID))
						{
							render_i->resetToOldPosition();
							render_j->resetToOldPosition();
						}

						if (cKeyi[components::COMPONENT_HEALTH] == true)
							HealthCollision(ent_i, ent_j);
					}
				}
			}
		}
	}
}*/
