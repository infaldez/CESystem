#include "ComponentRender.h"
#include <iostream>

ComponentRender::ComponentRender(std::string tileset, sf::Vector2u tileSize, sf::Vector2u tilePosition)
	: Component(components::COMPONENT_RENDER)
{
	this->tileset = tileset;
	this->tileSize = tileSize;
	this->tilePosition = tilePosition;
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