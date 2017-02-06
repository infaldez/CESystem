#include "ComponentPosition.h"


ComponentPosition::ComponentPosition(sf::Vector2f position)
	: Component(components::COMPONENT_POSITION)
{
	this->position = position;
}


ComponentPosition::~ComponentPosition()
{
}


sf::Vector2f ComponentPosition::getPosition()
{
	return position;
}


sf::Vector2f ComponentPosition::getPreviousPosition()
{
	return previousPosition;
}

void ComponentPosition::setPosition(sf::Vector2f position)
{
	this->previousPosition = this->position;
	this->position = position;
}