#pragma once

#include "Map.h"
class Game;

class TestMap : public Map
{
private:
	Game* _game;
public:
	TestMap(std::string name, Game* game);
	~TestMap();

	virtual void createMap();

};

