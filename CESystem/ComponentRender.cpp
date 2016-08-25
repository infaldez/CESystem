#include "ComponentRender.h"
#include <iostream>

ComponentRender::ComponentRender(bool(&ckey)[components::SIZE]) 
{
	ckey[components::id::COMPONENT_RENDER] = true;
	
	tileset = "texture.bmp";
	tileSize = sf::Vector2u(0, 0);
	tilePosition = sf::Vector2u(0, 0);
	position = sf::Vector2f(0, 0);
}


ComponentRender::~ComponentRender()
{
}


std::string ComponentRender::getTileset()
{
	return tileset;
}


sf::Vector2u ComponentRender::getTileSize()
{
	return tileSize;
}


sf::Vector2u ComponentRender::getTilePosition()
{
	return tilePosition;
}


sf::Vector2f ComponentRender::getPosition()
{
	return position;
}


float ComponentRender::getPositionX()
{
	return position.x;
}


float ComponentRender::getPositionY()
{
	return position.y;
}


void ComponentRender::setPosition(sf::Vector2f position)
{
	this->position = position;
}


void ComponentRender::setTileSize(sf::Vector2u tileSize)
{
	this->tileSize = tileSize;
}


void ComponentRender::setTileset(std::string tileset)
{
	this->tileset = tileset;
}


void ComponentRender::setTilePosition(sf::Vector2u tilePosition)
{
	this->tilePosition = tilePosition;
}