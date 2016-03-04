#include "ComponentRender.h"


ComponentRender::ComponentRender(bool(&ckey)[SIZE])
{
	ckey[COMPONENT_RENDER] = true;
	shape.setPosition(0, 0);
	shape.setRadius(30);
	shape.setOrigin(30,30);
	shape.setFillColor(sf::Color::Blue);
}


ComponentRender::~ComponentRender()
{
}


void ComponentRender::setPosition(sf::Vector2f position)
{
	shape.setPosition(position);
}


float ComponentRender::getPositionX()
{
	return shape.getPosition().x;
}


float ComponentRender::getPositionY()
{
	return shape.getPosition().y;
}


sf::CircleShape ComponentRender::getShape()
{
	return shape;
}