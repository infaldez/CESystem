#pragma once

#include "Component.h"
#include <SFML/Graphics.hpp>

class ComponentRender : public Component
{
private:
	std::string tileset;
	sf::Vector2u tileSize;
	sf::Vector2u tilePosition;
	sf::Vector2i position;
	sf::Vector2i oldPosition;
	
public:
	ComponentRender(std::string tileset, sf::Vector2u tileSize, sf::Vector2u tilePosition, sf::Vector2i position);
	ComponentRender(bool(&ckey)[components::SIZE]);
	~ComponentRender();

	std::string getTileset();
	sf::Vector2u getTileSize();
	sf::Vector2u getTilePosition();
	sf::Vector2i getPosition();
	int getPositionX();
	int getPositionY();

	void setPosition(sf::Vector2i position);
	void setTileSize(sf::Vector2u tileSize);
	void setTileset(std::string tileset);
	void setTilePosition(sf::Vector2u tilePosition);
	void resetToOldPosition();

};