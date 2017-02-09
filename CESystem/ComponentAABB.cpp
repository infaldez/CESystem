#include "ComponentAABB.h"


ComponentAABB::ComponentAABB(sf::Vector2f extents, sf::Vector2f offset)
	: Component(components::COMPONENT_AABB)
{
	this->offsetPosition = offset;
	this->extents = extents;
}


ComponentAABB::~ComponentAABB()
{
}


void ComponentAABB::setOffsetPosition(sf::Vector2f offset)
{
	this->offsetPosition = offset;
}


void ComponentAABB::setExtents(sf::Vector2f extents)
{
	this->extents = extents;
}


sf::Vector2f ComponentAABB::getOffsetPosition() const
{
	return offsetPosition;
}


sf::Vector2f ComponentAABB::getExtents() const
{
	return extents;
}


sf::Vector2f ComponentAABB::getPosition(sf::Vector2f position)
{
	return position + offsetPosition;
}


sf::Vector2f ComponentAABB::min(sf::Vector2f position)
{
	return position + offsetPosition;
}


sf::Vector2f ComponentAABB::max(sf::Vector2f position)
{
	return position + offsetPosition + extents;
}
