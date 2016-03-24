#include "ComponentRender.h"


ComponentRender::ComponentRender(bool(&ckey)[components::SIZE]) 
{
	ckey[components::id::COMPONENT_RENDER] = true;

	vertex.position = sf::Vector2f(100, 100);
	vertex.texCoords = sf::Vector2f(50, 50);

	if (!texture.loadFromFile("textures.bmp"))
	{
		//error
	}
}


ComponentRender::~ComponentRender()
{
}


void ComponentRender::setPosition(sf::Vector2f position)
{
	vertex.position = position;
}


float ComponentRender::getPositionX()
{
	return vertex.position.x;
}


float ComponentRender::getPositionY()
{
	return vertex.position.y;
}


sf::Vector2f ComponentRender::getPosition()
{
	return vertex.position;
}


sf::Vertex ComponentRender::getVertex()
{
	return vertex;
}


void ComponentRender::setTexCoords(sf::Vector2f coords)
{
	vertex.texCoords = coords;
}


sf::Texture ComponentRender::getTexture()
{
	return texture;
}

