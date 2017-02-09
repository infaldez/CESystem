#pragma once

#include "Component.h"

#include <SFML/Graphics.hpp>

class ComponentAABB : public Component
{
private:
	sf::Vector2f extents;
	sf::Vector2f offsetPosition;

public:
	ComponentAABB(sf::Vector2f extents, sf::Vector2f offset);
	~ComponentAABB();

	void setOffsetPosition(sf::Vector2f offset);
	void setExtents(sf::Vector2f extents);

	sf::Vector2f getOffsetPosition() const;
	sf::Vector2f getExtents() const;
	sf::Vector2f getPosition(sf::Vector2f position);
	sf::Vector2f min(sf::Vector2f position);
	sf::Vector2f max(sf::Vector2f position);
};

