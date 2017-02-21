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
	bool load(std::string tileset, sf::Vector2u tileSize, sf::Vector2u texSize, sf::Vector2u tilePosition, sf::Vector2f drawPosition, int curQuad, bool repeated)
	{
		//read the tileset from file
		if (read) {
			if (!m_tileset.loadFromFile(tileset))
				return false;
			read = false;
		}

		m_tileset.setRepeated(true);

		//resize the vertexArray
		m_vertices.setPrimitiveType(sf::Quads);
		int repeatx = tileSize.x / texSize.x;
		int repeaty = tileSize.y / texSize.y;
		m_vertices.resize(m_vertices.getVertexCount() + (4 * repeatx * repeaty));

		if (repeated)
		{
			for (int i = 0, q = 0; i < repeatx; ++i)
			{
				for (int j = 0; j < repeaty; ++j)
				{
					//assign a pointer to current tile's first quad
					sf::Vertex *quad = &m_vertices[m_vertices.getVertexCount() - (4 * repeatx * repeaty) + q];

					//define the corners
					quad[0].position = sf::Vector2f(drawPosition.x + (texSize.x * i), drawPosition.y + (texSize.y * j));
					quad[1].position = sf::Vector2f(drawPosition.x + (tileSize.x / repeatx) + (texSize.x * i), drawPosition.y + (texSize.y * j));
					quad[2].position = sf::Vector2f(drawPosition.x + (tileSize.x / repeatx) + (texSize.x * i), drawPosition.y + (tileSize.y / repeaty) + (texSize.y * j));
					quad[3].position = sf::Vector2f(drawPosition.x + (texSize.x * i), drawPosition.y + (tileSize.y / repeaty) + (texSize.y * j));

					//define texture coordinates
					quad[0].texCoords = sf::Vector2f(tilePosition.x, tilePosition.y);
					quad[1].texCoords = sf::Vector2f(tilePosition.x + texSize.x, tilePosition.y);
					quad[2].texCoords = sf::Vector2f(tilePosition.x + texSize.x, tilePosition.y + texSize.y);
					quad[3].texCoords = sf::Vector2f(tilePosition.x, tilePosition.y + texSize.y);
					q += 4;
				}
			}
		}
		else
		{
			sf::Vertex *quad = &m_vertices[m_vertices.getVertexCount() - 4];

			//define the corners
			quad[0].position = sf::Vector2f(drawPosition.x, drawPosition.y);
			quad[1].position = sf::Vector2f(drawPosition.x + tileSize.x, drawPosition.y);
			quad[2].position = sf::Vector2f(drawPosition.x + tileSize.x, drawPosition.y + tileSize.y);
			quad[3].position = sf::Vector2f(drawPosition.x, drawPosition.y + tileSize.y);

			//define texture coordinates
			quad[0].texCoords = sf::Vector2f(tilePosition.x, tilePosition.y);
			quad[1].texCoords = sf::Vector2f(tilePosition.x + texSize.x, tilePosition.y);
			quad[2].texCoords = sf::Vector2f(tilePosition.x + texSize.x, tilePosition.y + texSize.y);
			quad[3].texCoords = sf::Vector2f(tilePosition.x, tilePosition.y + texSize.y);
		}

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


void RenderSystem::runSystem(std::vector<std::unique_ptr<Entity>>& entityList, std::vector<std::string> tilesets, std::clock_t dt)
{
	_dt = dt;
	for (auto ts : tilesets)
	{
		DrawEntity drawEntity;
		int currentQuad = 0;
		for (auto& ent : entityList)
		{
			std::array<bool, components::SIZE> cKey = ent->componentKey;
			if (cKey[components::id::COMPONENT_RENDER] == true &&
				cKey[components::id::COMPONENT_POSITION] == true)
			{
				ComponentRender* cRender = ent->getComponent<ComponentRender>(components::COMPONENT_RENDER);
				ComponentPosition* cPos = ent->getComponent<ComponentPosition>(components::COMPONENT_POSITION);
				std::string tileset = cRender->getTileset();
				bool repeated = cRender->repeated();

				if (ts == tileset)
				{
					drawEntity.load(tileset, cRender->getTileSize(), cRender->getTexSize(), cRender->getTilePosition(), cPos->getPosition(), currentQuad, repeated);

					currentQuad++;
				}
			}
		}
		sf::Transform t;
		window->draw(drawEntity, t);
	}

}