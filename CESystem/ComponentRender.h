#pragma once

#include "Component.h"
#include <SFML/Graphics.hpp>

class ComponentRender : public Component
{
private:
	std::string tileset;
	sf::Vector2u tileSize;
	sf::Vector2u tilePosition;
	
public:
	ComponentRender(std::string tileset, sf::Vector2u tileSize, sf::Vector2u tilePosition);
	~ComponentRender();

	std::string getTileset();
	sf::Vector2u getTileSize();
	sf::Vector2u getTilePosition();
	sf::Vector2f getPosition();
	sf::Vector2f getOldPosition();

	void setTileSize(sf::Vector2u tileSize);
	void setTileset(std::string tileset);
	void setTilePosition(sf::Vector2u tilePosition);

};