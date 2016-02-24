#include "RenderSystem.h"
#include "Entity.h"
#include "Component.h"
#include "EntityPlayer.h"


RenderSystem::RenderSystem(sf::RenderWindow& window)
{
	this->window = &window;
}


RenderSystem::~RenderSystem()
{
}


void RenderSystem::AddEntity(Entity *entity)
{

}


void RenderSystem::RunSystem()
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