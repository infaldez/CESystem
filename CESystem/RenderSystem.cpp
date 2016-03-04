#include "RenderSystem.h"

#include "Entity.h"
#include "Component.h"
#include "EntityPlayer.h"

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
		if (entityList.at(i)->componentKey[COMPONENT_RENDER])
		{
			sf::CircleShape image = ((EntityPlayer*)entityList.at(i))->render->getShape();
			window->draw(image);
		}
	}
}