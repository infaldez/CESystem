#include "CollisionSystem.h"

#include <SFML\Graphics.hpp>
#include "EntityPlayer.h"

#include <iostream>

CollisionSystem::CollisionSystem()
{
}


CollisionSystem::~CollisionSystem()
{
}


void CollisionSystem::runSystem(std::vector<Entity*> entityList)
{	
	for (int i = 0; i < entityList.size(); ++i)
	{	
		if (entityList.at(i)->componentKey[components::id::COMPONENT_RENDER] == true && entityList.at(i)->componentKey[components::id::COMPONENT_COLLISION] == true)
		{	
			ComponentRender* render_i = entityList.at(i)->getComponent<ComponentRender>(components::COMPONENT_RENDER);
			ComponentMovement* movement_i = entityList.at(i)->getComponent<ComponentMovement>(components::COMPONENT_MOVEMENT);

			//check for collisions with other entities
			for (int j = i + 1; j < entityList.size(); ++j)
			{
				if (entityList.at(j)->componentKey[components::id::COMPONENT_RENDER] == true && entityList.at(j)->componentKey[components::id::COMPONENT_COLLISION] == true)
				{
					ComponentRender* render_j = entityList.at(j)->getComponent<ComponentRender>(components::COMPONENT_RENDER);
					ComponentMovement* movement_j = entityList.at(j)->getComponent<ComponentMovement>(components::COMPONENT_MOVEMENT);

					//check collision AABB
					if (render_i->getPositionX() < render_j->getPositionX() + render_j->getTileSize().x &&
						render_i->getPositionX() + render_i->getTileSize().x > render_j->getPositionX() &&
						render_i->getPositionY() < render_j->getPositionY() + render_j->getTileSize().y &&
						render_i->getPositionY() + render_i->getTileSize().y > render_j->getPositionY())
					{
						//Collision
						render_i->resetToOldPosition();
						render_j->resetToOldPosition();
					}
				}
			}
		}
	}
}


