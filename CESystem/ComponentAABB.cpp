#include "ComponentAABB.h"


ComponentAABB::ComponentAABB(sf::Vector2f position, sf::Vector2f extents)
	: Component(components::COMPONENT_AABB)
{
	this->position = position;
	this->extents = extents;
}


ComponentAABB::~ComponentAABB()
{
}


void ComponentAABB::setPosition(sf::Vector2f position)
{
	this->position = position;
}


void ComponentAABB::setExtents(sf::Vector2f extents)
{
	this->extents = extents;
}


sf::Vector2f ComponentAABB::getPosition() const
{
	return position;
}


sf::Vector2f ComponentAABB::getExtents() const
{
	return extents;
}


sf::Vector2f ComponentAABB::min() const
{
	return position - extents;
}


sf::Vector2f ComponentAABB::max() const
{
	return position + extents;
}