#include "CollisionSystem.h"

#include <SFML\Graphics.hpp>
#include "EntityPlayer.h"

CollisionSystem::CollisionSystem()
{
}


CollisionSystem::~CollisionSystem()
{
}

void CollisionSystem::runSystem(std::vector<Entity*> &entityList)
{
	for (int i = 0; i < entityList.size(); i++)
	{
		if (entityList.at(i)->componentKey[COMPONENT_RENDER] && entityList.at(i)->componentKey[COMPONENT_COLLISION])
		{
			for (int j = i+1; j < entityList.size(); j++)
			{
				//if (j == i) { j + 1; }
				if (entityList.at(j)->componentKey[COMPONENT_RENDER] && entityList.at(j)->componentKey[COMPONENT_COLLISION])
				{
					if (((EntityPlayer*)entityList.at(i))->render->getShape().getGlobalBounds().intersects(((EntityPlayer*)entityList.at(j))->render->getShape().getGlobalBounds()))
					{
						((EntityPlayer*)entityList.at(i))->movement->setSpeed(0);
						((EntityPlayer*)entityList.at(j))->movement->setSpeed(0);
					}			
				}
			}
		}
	}
}


