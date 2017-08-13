#include "RenderSystem.h"

#include "Entity.h"
#include "Component.h"
#include "ComponentRender.h"
#include "ComponentPosition.h"
#include "EntityPlayer.h"

#include <iostream>
#include <string>
#include "ComponentText.h"

void DrawEntity::clear()
{
	m_vertices.clear();
}

/*
	DRAWENTITY
	*/
bool DrawEntity::load(std::string tileset, sf::Vector2u tileSize, sf::Vector2u texSize, sf::Vector2u tilePosition, sf::Vector2f drawPosition, bool repeated)
{
	//read the tileset from file
	if (read) {
		if (!m_tileset.loadFromFile(tileset))
			return false;
		read = false;
	}

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

void DrawEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &m_tileset;

	target.draw(m_vertices, states);
}

void DrawEntity::loadgrid()
{
	unsigned width = 32 * 150;
	unsigned height = 32 * 150;
	unsigned grid = 32;

	//resize the vertexArray
	m_vertices.clear();
	m_vertices.setPrimitiveType(sf::Lines);
	m_vertices.resize((300 * 2) + 4);

	//define the corners
	for (int x = 0, i = 0; x < height; x += grid, i += 2)
	{
		sf::Vertex* line = &m_vertices[i];

		line[0].position = sf::Vector2f(x, 0);
		line[1].position = sf::Vector2f(x, 5000);

		line[0].color = sf::Color::White;
		line[1].color = sf::Color::White;
		line[0].color.a = static_cast<sf::Uint8>(50);
		line[1].color.a = static_cast<sf::Uint8>(50);
	}
	
	for (int y = 0, i = 0; y < width; y += grid, i += 2)
	{
		sf::Vertex* line = &m_vertices[m_vertices.getVertexCount() - 300 + i];
		
		line[0].position = sf::Vector2f(0, y);
		line[1].position = sf::Vector2f(5000, y);

		line[0].color = sf::Color::White;
		line[1].color = sf::Color::White;
		line[0].color.a = static_cast<sf::Uint8>(50);
		line[1].color.a = static_cast<sf::Uint8>(50);
	}
}

/*
	RENDERSYSTEM
*/
RenderSystem::RenderSystem(sf::RenderWindow& window, std::map<std::string, sf::View>& views)
{
	_views = &views;
	this->window = &window;
}


RenderSystem::~RenderSystem()
{
}


void RenderSystem::createRTexture(std::vector<std::unique_ptr<Entity>>& entityList, std::vector<std::string> tilesets)
{
	// keep track of the highest layer assigned to any render
	int topLayer = 0;
	window->clear();
	drawEntity.clear();
	for (int layer = 0; layer <= topLayer; layer++)
	{
		for (auto ts : tilesets)
		{
			for (auto& ent : entityList)
			{
				std::array<bool, components::SIZE> cKey = ent->componentKey;
				/* DRAW TEXTURES */
				if (cKey[components::id::COMPONENT_RENDER] == true &&
					cKey[components::id::COMPONENT_POSITION] == true)
				{
					ComponentRender* cRender = ent->getComponent<ComponentRender>(components::COMPONENT_RENDER);
					if (cRender->getLayer() > topLayer)
						topLayer = cRender->getLayer();
					if (cRender->getLayer() != layer)
						continue;

					ComponentPosition* cPos = ent->getComponent<ComponentPosition>(components::COMPONENT_POSITION);
					std::string tileset = cRender->getTileset();
					bool repeated = cRender->repeated();

					if (ts == tileset)
					{
						drawEntity.load(tileset, cRender->getTileSize(), cRender->getTexSize(), cRender->getTilePosition(), cPos->getPosition(), repeated);
					}
				}
				/* DRAW TEXT */
				if (cKey[components::id::COMPONENT_TEXT] == true &&
					cKey[components::id::COMPONENT_POSITION] == true)
				{
					ComponentText* cText = ent->getComponent<ComponentText>(components::COMPONENT_TEXT);
					ComponentPosition* cPos = ent->getComponent<ComponentPosition>(components::COMPONENT_POSITION);

					if (readT)
						_font.loadFromFile(cText->getFont());
					readT = false;
					_text.setFont(_font);
					_text.setString(cText->getText());
					_text.setPosition(cPos->getPosition());
					//window->draw(_text);
				}
			}
		}
	}
	
}

void renderText()
{

}

void RenderSystem::runSystem(std::vector<std::unique_ptr<Entity>>& entityList, std::vector<std::string> tilesets)
{

	for (auto& ent : entityList)
	{
		if (ent->hasTag("player"))
		{
			sf::Vector2f pos = ent->getComponent<ComponentPosition>(components::COMPONENT_POSITION)->getPosition();

				_views->find("mapView")->second.setCenter(pos);
				window->setView(_views->find("mapView")->second);

		}
	}

	createRTexture(entityList, tilesets);
	/*
	_rtexture.display();
	window->clear(sf::Color(200, 150, 50));

	sf::Sprite scene(_rtexture.getTexture());
	window->setView(_game.menuView);
	window->draw(scene);
	window->setView(_game.mapview);
	window->draw(scene);*/
	grid.loadgrid();

	for (auto& view : *_views)
	{
		window->setView(view.second);
		window->draw(drawEntity);
		window->draw(grid);
	}

	window->display();
}