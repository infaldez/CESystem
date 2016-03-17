#include "RenderSystem.h"

#include "Entity.h"
#include "Component.h"
#include "ComponentRender.h"
#include "EntityPlayer.h"

#include "InputSystem.h"

#include <iostream>


RenderSystem::RenderSystem(sf::RenderWindow& window)
{
	this->window = &window;
}


RenderSystem::~RenderSystem()
{
}


void RenderSystem::runSystem(std::vector<Entity*> &entityList)
{
	for (int i = 0; i < entityList.size(); i++)
	{
		if (entityList.at(i)->componentKey[components::id::COMPONENT_RENDER])
		{		
			for (int j = 0; j<entityList.at(i)->getComponents().size(); ++j)
			{
				if (entityList.at(i)->getComponents().at(j)->getComponentId() == components::id::COMPONENT_RENDER)
				{
					sf::CircleShape image = ((ComponentRender*)entityList.at(i)->getComponents().at(j))->getShape();
					window->draw(image);
				}
			}
		}
	}
}