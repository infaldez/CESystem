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

/*
	TODO:
	- Better and faster collision detection
	- What happens on collision
	PROBLEMS:
	- Slow
	- Inaccurate
	- Only works when two moving entities collide
*/

void CollisionSystem::runSystem(std::vector<Entity*> entityList)
{	
	for (int i = 0; i < entityList.size(); ++i)
	{	
		//check if componentKey matches with RENDER and COLLISION
		if (entityList.at(i)->componentKey[components::id::COMPONENT_RENDER] && entityList.at(i)->componentKey[components::id::COMPONENT_COLLISION])
		{	
			ComponentRender render_i = entityList.at(i)->getComponentRender();
			ComponentMovement movement_i = entityList.at(i)->getComponentMovement();

			//check for collisions with other entities
			for (int j = i + 1; j < entityList.size(); ++j)
			{

				if (entityList.at(j)->componentKey[components::id::COMPONENT_RENDER] && entityList.at(j)->componentKey[components::id::COMPONENT_COLLISION])
				{
					ComponentRender render_j = entityList.at(j)->getComponentRender();
					ComponentMovement movement_j = entityList.at(j)->getComponentMovement();

					//stop the colliding entities
					/*if (render_i.getShape().getGlobalBounds().intersects(render_j.getShape().getGlobalBounds()))
					{
						movement_i.setSpeed(0);
						movement_j.setSpeed(0);

						entityList.at(i)->setComponentMovement(movement_i);
						entityList.at(j)->setComponentMovement(movement_j);
					}*/
				}
			}
		}
	}
}


