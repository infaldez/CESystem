#include "RenderSystem.h"

#include "Entity.h"
#include "Component.h"
#include "ComponentRender.h"
#include "EntityPlayer.h"

#include <iostream>


RenderSystem::RenderSystem(sf::RenderWindow& window)
{
	this->window = &window;
	verticles.setPrimitiveType(sf::Quads);
}


RenderSystem::~RenderSystem()
{
}


void RenderSystem::runSystem(std::vector<Entity*> entityList)
{
	for (int i = 0; i < entityList.size(); i++)
	{
		if (entityList.at(i)->componentKey[components::id::COMPONENT_RENDER])
		{	
			//sf::Texture texture = entityList.at(i)->getComponentRender().getTexture();
			//sf::VertexArray va = entityList.at(i)->getComponentRender().getVerticles();
			
			sf::Vertex ver = entityList.at(i)->getComponentRender().getVertex();
			sf::Texture tex = entityList.at(i)->getComponentRender().getTexture();

			verticles.append(ver);		

			window->draw(verticles, &tex);

		}
	}
}