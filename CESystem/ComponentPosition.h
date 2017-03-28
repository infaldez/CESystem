#pragma once

#include "Component.h"

#include <SFML/Graphics.hpp>

class ComponentPosition : public Component
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Component>(*this);
		ar & position.x & position.y;
		ar & previousPosition.x;
		ar & previousPosition.y;
	}
private:
	sf::Vector2f original;

public:
	ComponentPosition(){};
	ComponentPosition(sf::Vector2f position);
	~ComponentPosition();

	sf::Vector2f position;
	sf::Vector2f previousPosition;

	void setPosition(sf::Vector2f position);
	void setNewPosition(sf::Vector2f position);

	sf::Vector2f getPosition();
	sf::Vector2f getPreviousPosition();
	sf::Vector2f getOriginalPosition();
};