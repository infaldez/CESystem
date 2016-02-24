#include "ComponentRender.h"


ComponentRender::ComponentRender(bool(&ckey)[SIZE])
{
	ckey[COMPONENT_RENDER] = true;
	positionX = 10;
	positionY = 10;
	shape.setRadius(30);
	shape.setPosition(positionX, positionY);
	shape.setFillColor(sf::Color::Blue);
}


ComponentRender::~ComponentRender()
{
}


void ComponentRender::setPosition(int x, int y)
{
	positionX = x;
	positionY = y;
}


int ComponentRender::getPositionX()
{
	return positionX;
}


int ComponentRender::getPositionY()
{
	return positionY;
}


sf::CircleShape ComponentRender::getShape()
{
	return shape;
}