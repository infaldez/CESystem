#include "RenderSystem.h"

#include "Entity.h"
#include "Component.h"
#include "ComponentRender.h"
#include "ComponentPosition.h"
#include "EntityPlayer.h"

#include <iostream>
#include <string>


class DrawEntity : public sf::Drawable, public sf::Transformable
{
	sf::Texture m_tileset;
	sf::VertexArray m_vertices;
	bool read = true;

public:
	bool load(std::string tileset, sf::Vector2u tileSize, sf::Vector2u tilePosition, sf::Vector2f drawPosition, int i)
	{
		//read the tileset from file
		if (read) {
			if (!m_tileset.loadFromFile(tileset))
				return false;
			read = false;
		}

		//resize the vertexArray
		m_vertices.setPrimitiveType(sf::Quads);
		m_vertices.resize((i + 1) * 4);

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


void RenderSystem::runSystem(std::vector<std::unique_ptr<Entity>>& entityList, std::vector<std::string> tilesets)
{
	for (auto ts : tilesets)
	{
		DrawEntity drawEntity;
		int entityCount = 0;
		for (auto& ent : entityList)
		{
			std::array<bool, components::SIZE> cKey = ent->componentKey;
			if (cKey[components::id::COMPONENT_RENDER] == true &&
				cKey[components::id::COMPONENT_POSITION] == true)
			{
				ComponentRender* cRender = ent->getComponent<ComponentRender>(components::COMPONENT_RENDER);
				ComponentPosition* cPos = ent->getComponent<ComponentPosition>(components::COMPONENT_POSITION);
				std::string tileset = cRender->getTileset();
				if (ts == tileset)
				{
					drawEntity.load(tileset, cRender->getTileSize(), cRender->getTilePosition(), cPos->getPosition(), entityCount);

					entityCount++;
				}
			}
		}
		sf::Transform t;
		window->draw(drawEntity, t);
	}
	
}