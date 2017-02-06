#pragma once

#include "Component.h"

#include <SFML/Graphics.hpp>

class ComponentAABB : public Component
{
public:
	ComponentAABB(sf::Vector2f, sf::Vector2f extents);
	~ComponentAABB();

	sf::Vector2f position;
	sf::Vector2f extents;

	void setPosition(sf::Vector2f position);
	void setExtents(sf::Vector2f extents);
	sf::Vector2f getPosition() const;
	sf::Vector2f getExtents() const;

	sf::Vector2f min() const;
	sf::Vector2f max() const;


};

