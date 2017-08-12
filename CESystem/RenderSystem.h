#pragma once

#include <vector>
#include <memory>
#include <SFML\Graphics.hpp>

#include "Entity.h"
#include "ComponentRender.h"
#include "Game.h"

class DrawEntity : public sf::Drawable, public sf::Transformable
{
	sf::Texture m_tileset;
	sf::VertexArray m_vertices;
	bool read = true;

public:
	void clear();
	bool load(std::string tileset, sf::Vector2u tileSize, sf::Vector2u texSize, sf::Vector2u tilePosition, sf::Vector2f drawPosition, bool repeated);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void loadgrid();

	DrawEntity(){};
	~DrawEntity(){};
};

class RenderSystem
{
private:
	std::map<std::string, sf::View>& _views;

	bool readT = true;
	sf::Text _text;
	sf::Font _font;
	float _dt;
	sf::RenderWindow* window;
	DrawEntity drawEntity;
	DrawEntity grid;

	void createRTexture(std::vector<std::unique_ptr<Entity>>& entityList, std::vector<std::string> tilesets);

public:
	void runSystem(std::vector<std::unique_ptr<Entity>>& entityList, std::vector<std::string> tilesets);

	RenderSystem(sf::RenderWindow& window, std::map<std::string, sf::View>& views);
	~RenderSystem();
};

