#include "ComponentRender.h"
#include <iostream>

ComponentRender::ComponentRender(std::string tileset, sf::Vector2u tileSize, sf::Vector2u tilePosition)
	: Component(components::COMPONENT_RENDER)
{
	this->tileset = tileset;
	this->tileSize = tileSize;
	this->tilePosition = tilePosition;
	//this->position = position;
	//this->oldPosition = position;
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


/*sf::Vector2f ComponentRender::getPosition()
{
	return position;
}

sf::Vector2f ComponentRender::getOldPosition()
{
	return oldPosition;
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
	oldPosition = this->position;
	this->position = position;
}*/


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


/*void ComponentRender::resetToOldPosition()
{
	position = oldPosition;
}*/