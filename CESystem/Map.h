#pragma once

#include "IOmanager.h"

class Map
{
private:
	std::string _name;
	
public:
	EntityManager _entityManager;
	std::vector<std::unique_ptr<Entity>>& _entityList;
	virtual void createMap() = 0;
	void loadMap();
	void saveMap();

	Map(std::string name);
	virtual ~Map();
};

