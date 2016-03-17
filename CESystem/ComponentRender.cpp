#include "ComponentRender.h"


ComponentRender::ComponentRender(bool(&ckey)[components::SIZE])
{
	cid = components::id::COMPONENT_RENDER;
	ckey[components::id::COMPONENT_RENDER] = true;
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