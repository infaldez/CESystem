#pragma once

#include "Component.h"
#include <SFML/Graphics.hpp>

class ComponentRender : public Component
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Component>(*this);
		ar & _tileset;
		ar & _tileSize.x & _tileSize.y;
		ar & _tilePosition.y & _tilePosition.y;
		ar & _texSize.x & _texSize.y;
		ar & _repeat;
	}

private:
	std::string _tileset;
	sf::Vector2u _tileSize;
	sf::Vector2u _tilePosition;
	sf::Vector2u _texSize;
	bool _repeat;

public:
	ComponentRender(){};
	ComponentRender(std::string tileset, sf::Vector2u tileSize, sf::Vector2u tilePosition, sf::Vector2u texSize, bool repeat);
	~ComponentRender();

	std::string getTileset();
	sf::Vector2u getTileSize();
	sf::Vector2u getTilePosition();
	sf::Vector2u getTexSize();
	bool repeated();

	void setTileSize(sf::Vector2u tileSize);
	void setTileset(std::string tileset);
	void setTilePosition(sf::Vector2u tilePosition);
	void setTexSize(sf::Vector2u texSize);
};