#include "ComponentRender.h"

ComponentRender::ComponentRender(std::string tileset, sf::Vector2u tileSize, sf::Vector2u tilePosition, sf::Vector2u texSize, bool repeat)
	: Component(components::COMPONENT_RENDER)
{
	_tileset = tileset;
	_tileSize = tileSize;
	_tilePosition = tilePosition;
	_texSize = texSize;
	_repeat = repeat;
	_layer = 0;
}


ComponentRender::~ComponentRender()
{
}


std::string ComponentRender::getTileset()
{
	return _tileset;
}


sf::Vector2u ComponentRender::getTileSize()
{
	return _tileSize;
}


sf::Vector2u ComponentRender::getTilePosition()
{
	return _tilePosition;
}


sf::Vector2u ComponentRender::getTexSize()
{
	return _texSize;
}

int ComponentRender::getLayer()
{
	return _layer;
}

void ComponentRender::setLayer(int layer)
{
	_layer = layer;
}

bool ComponentRender::repeated()
{
	return _repeat;
}

void ComponentRender::setTileSize(sf::Vector2u tileSize)
{
	_tileSize = tileSize;
}


void ComponentRender::setTileset(std::string tileset)
{
	_tileset = tileset;
}


void ComponentRender::setTilePosition(sf::Vector2u tilePosition)
{
	_tilePosition = tilePosition;
}

void ComponentRender::setTexSize(sf::Vector2u texSize)
{
	_texSize = texSize;
}
