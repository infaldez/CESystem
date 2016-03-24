#pragma once

#include "Component.h"
#include <SFML/Graphics.hpp>

class ComponentRender : public Component
{
private:
	sf::Vertex vertex;
	sf::Texture texture;

public:
	ComponentRender(bool(&ckey)[components::SIZE]);
	~ComponentRender();

	void setPosition(sf::Vector2f position);
	float getPositionX();
	float getPositionY();
	sf::Vector2f getPosition();
	sf::Vertex getVertex();
	void setTexCoords(sf::Vector2f coords);
	sf::Texture getTexture();
};