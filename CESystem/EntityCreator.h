#pragma once
#include <memory>

#include "Entity.h"

namespace entitycreator
{
	std::unique_ptr<Entity> createPassable(sf::Vector2f position, sf::Vector2u tile, int layer = 0);
	std::unique_ptr<Entity> createSolid(sf::Vector2f position, sf::Vector2u tile, sf::Vector2f aabb, int layer = 0);
	std::unique_ptr<Entity> createSolid(sf::Vector2f position, sf::Vector2u tilePos, int layer = 0);

	std::unique_ptr<Entity> createItem(sf::Vector2f position, int layer = 0);
	std::unique_ptr<Entity> player(sf::Vector2f position, int layer = 0);
	std::unique_ptr<Entity> enemy(sf::Vector2f position, int layer = 0);
	std::unique_ptr<Entity> damagewall(sf::Vector2f position, int layer = 0);
}

