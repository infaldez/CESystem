#include "ComponentPosition.h"

ComponentPosition::ComponentPosition(sf::Vector2f position)
	: Component(components::COMPONENT_POSITION)
{
	this->position = position;
	this->previousPosition = position;
	original = position;
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


sf::Vector2f ComponentPosition::getOriginalPosition()
{
	return original;
}

void ComponentPosition::setNewPosition(sf::Vector2f position)
{
	this->position = position;
}

void ComponentPosition::setPosition(sf::Vector2f position)
{
	this->previousPosition = this->position;
	this->position = position;
}