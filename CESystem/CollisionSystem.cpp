#include "CollisionSystem.h"

#include <SFML\Graphics.hpp>
#include "EntityPlayer.h"

#include "InputSystem.h"

#include <iostream>

CollisionSystem::CollisionSystem()
{
}


CollisionSystem::~CollisionSystem()
{
}

/*
	TODO:
	- Split this to smaller functions
	- Better collision detection
	PROBLEMS:
	- Slow
	- Only works with two moving entities
*/
void CollisionSystem::runSystem(std::vector<Entity*> entityList)
{	
	for (int i = 0; i < entityList.size(); ++i)
	{	
		//check if componentKey matches with RENDER and COLLISION
		if (entityList.at(i)->componentKey[components::id::COMPONENT_RENDER] && entityList.at(i)->componentKey[components::id::COMPONENT_COLLISION])
		{	
			ComponentRender* render_i = NULL;
			ComponentMovement* movement_i = NULL;
			//Loop the and assign the components for loop i
			for (int j = 0; j < entityList.at(i)->getComponents().size(); ++j)
			{	
				//std::cout << "looking for i" << std::endl;
				if (entityList.at(i)->getComponents().at(j)->getComponentId() == components::id::COMPONENT_RENDER)
					render_i = ((ComponentRender*)entityList.at(i)->getComponents().at(j));
				if (entityList.at(i)->getComponents().at(j)->getComponentId() == components::id::COMPONENT_MOVEMENT)
					movement_i = ((ComponentMovement*)entityList.at(i)->getComponents().at(j));
			}

			//check for collisions with other entities
			for (int j = i + 1; j < entityList.size(); ++j)
			{
				ComponentRender* render_j = NULL;
				ComponentMovement* movement_j = NULL;
				if (entityList.at(j)->componentKey[components::id::COMPONENT_RENDER] && entityList.at(j)->componentKey[components::id::COMPONENT_COLLISION])
				{
					//Loop the and assign the components for loop j
					for (int j = 0; j < entityList.at(i)->getComponents().size(); ++j)
					{
						//std::cout << "looking for j" << std::endl;
						if (entityList.at(i)->getComponents().at(j)->getComponentId() == components::id::COMPONENT_RENDER)
							render_j = ((ComponentRender*)entityList.at(i)->getComponents().at(j));
						if (entityList.at(i)->getComponents().at(j)->getComponentId() == components::id::COMPONENT_MOVEMENT)
							movement_j = ((ComponentMovement*)entityList.at(i)->getComponents().at(j));
					}

					//stop the colliding entities
					if (render_i->getShape().getGlobalBounds().intersects(render_j->getShape().getGlobalBounds()))
					{
						std::cout << "stop" << std::endl;
						movement_i->setSpeed(0);
						movement_j->setSpeed(0);
					}
				}
			}
		}
	}
}


