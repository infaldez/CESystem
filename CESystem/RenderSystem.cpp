#include "RenderSystem.h"

#include "Entity.h"
#include "Component.h"
#include "ComponentRender.h"
#include "EntityPlayer.h"

#include <iostream>
#include <string>

#define VERTICEARRAYSIZE 10000

class drawEntity : public sf::Drawable, public sf::Transformable
{
	sf::Texture m_tileset;
	sf::VertexArray m_vertices;
	bool read = true;

public:
	bool load(std::string tileset, sf::Vector2u tileSize, sf::Vector2u tilePosition, sf::Vector2f drawPosition, int i)
	{
		//read the tileset from file
		//TODO better handling of reading the tileset only once
		if (read) {
			if (!m_tileset.loadFromFile(tileset))
				return false;
			read = false;
		}

		//resize the vertexarray
		//TODO dynamic resizing based on the amount of render entities
		m_vertices.setPrimitiveType(sf::Quads);
		m_vertices.resize(VERTICEARRAYSIZE * 4);

		//assign a pointer to current tile's quad
		sf::Vertex *quad = &m_vertices[i * 4];

		//define the corners
		quad[0].position = sf::Vector2f(drawPosition.x, drawPosition.y);
		quad[1].position = sf::Vector2f(drawPosition.x + tileSize.x, drawPosition.y);
		quad[2].position = sf::Vector2f(drawPosition.x + tileSize.x, drawPosition.y + tileSize.y);
		quad[3].position = sf::Vector2f(drawPosition.x, drawPosition.y + tileSize.y);

		//define texture coordinates
		quad[0].texCoords = sf::Vector2f(tilePosition.x, tilePosition.y);
		quad[1].texCoords = sf::Vector2f(tilePosition.x + tileSize.x, tilePosition.y);
		quad[2].texCoords = sf::Vector2f(tilePosition.x + tileSize.x, tilePosition.y + tileSize.y);
		quad[3].texCoords = sf::Vector2f(tilePosition.x, tilePosition.y + tileSize.y);

		return true;
	}


	void draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = &m_tileset;

		target.draw(m_vertices, states);
	}
};


RenderSystem::RenderSystem(sf::RenderWindow& window)
{
	this->window = &window;
}


RenderSystem::~RenderSystem()
{
}


void RenderSystem::runSystem(std::vector<Entity*> entityList)
{
	drawEntity drawEntity;
	int entityCount = 0;

	for (int i = 0; i < entityList.size(); i++)
	{
		if (entityList.at(i)->componentKey[components::id::COMPONENT_RENDER] == true)
		{	
			ComponentRender* cRender = entityList.at(i)->getComponent<ComponentRender>(components::COMPONENT_RENDER);

			drawEntity.load(cRender->getTileset(), cRender->getTileSize(), cRender->getTilePosition(), cRender->getPosition(), entityCount);
			
			entityCount++;
		}
	}

	window->draw(drawEntity);
}


