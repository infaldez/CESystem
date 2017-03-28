#include "Map.h"
#include "IOmanager.h"

Map::Map(std::string name) : _entityManager(EntityManager()), _entityList(_entityManager._entityList), _name(name)
{
}


Map::~Map()
{
}

void Map::loadMap()
{
	IOmanager::load(_name, _entityManager);
}

void Map::saveMap()
{
	IOmanager::save(_name, _entityManager);
}