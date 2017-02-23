#include "ComponentAABB.h"


ComponentAABB::ComponentAABB(sf::Vector2f extents, sf::Vector2f offset)
	: Component(components::COMPONENT_AABB)
{
	this->_offsetPosition = offset;
	this->_extents = extents;
}


ComponentAABB::~ComponentAABB()
{
}


void ComponentAABB::setOffsetPosition(sf::Vector2f offset)
{
	this->_offsetPosition = offset;
}


void ComponentAABB::setExtents(sf::Vector2f extents)
{
	this->_extents = extents;
}


sf::Vector2f ComponentAABB::getOffsetPosition() const
{
	return _offsetPosition;
}


sf::Vector2f ComponentAABB::getExtents() const
{
	return _extents;
}


sf::Vector2f ComponentAABB::getPosition(sf::Vector2f position)
{
	return position + _offsetPosition;
}


sf::Vector2f ComponentAABB::min(sf::Vector2f position)
{
	return position + _offsetPosition;
}


sf::Vector2f ComponentAABB::max(sf::Vector2f position)
{
	return position + _offsetPosition + _extents;
}
