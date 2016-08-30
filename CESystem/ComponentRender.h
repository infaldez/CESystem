#pragma once

#include "Component.h"
#include <SFML/Graphics.hpp>

class ComponentRender : public Component
{
private:
	std::string tileset;
	sf::Vector2u tileSize;
	sf::Vector2u tilePosition;
	sf::Vector2f position;
	sf::Vector2f oldPosition;
	
public:
	ComponentRender(std::string tileset, sf::Vector2u tileSize, sf::Vector2u tilePosition, sf::Vector2f position);
	ComponentRender(bool(&ckey)[components::SIZE]);
	~ComponentRender();

	std::string getTileset();
	sf::Vector2u getTileSize();
	sf::Vector2u getTilePosition();
	sf::Vector2f getPosition();
	float getPositionX();
	float getPositionY();

	void setPosition(sf::Vector2f position);
	void setTileSize(sf::Vector2u tileSize);
	void setTileset(std::string tileset);
	void setTilePosition(sf::Vector2u tilePosition);
	void resetToOldPosition();

};