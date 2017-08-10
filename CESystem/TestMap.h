#pragma once

#include "Map.h"
class Game;

class TestMap : public Map
{
private:
	Loop* _game;
public:
	TestMap(std::string name, Loop* game);
	~TestMap();

	virtual void createMap();

};

