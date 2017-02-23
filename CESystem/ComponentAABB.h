#pragma once

#include "Component.h"

#include <SFML/Graphics.hpp>

class ComponentAABB : public Component
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Component>(*this);
		ar & _extents.x & _extents.y;
		ar & _offsetPosition.x & _offsetPosition.y;
	}
private:
	sf::Vector2f _extents;
	sf::Vector2f _offsetPosition;

public:
	ComponentAABB(sf::Vector2f extents, sf::Vector2f offset);
	ComponentAABB(){}
	~ComponentAABB();

	void setOffsetPosition(sf::Vector2f offset);
	void setExtents(sf::Vector2f extents);

	sf::Vector2f getOffsetPosition() const;
	sf::Vector2f getExtents() const;
	sf::Vector2f getPosition(sf::Vector2f position);
	sf::Vector2f min(sf::Vector2f position);
	sf::Vector2f max(sf::Vector2f position);
};

