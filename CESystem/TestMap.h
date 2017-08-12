#pragma once

#include "Map.h"
class Game;

class TestMap : public Map
{
private:
	std::map<std::string, sf::View>& _views;
public:
	TestMap(std::string name, std::map<std::string, sf::View>& views);
	~TestMap();

	virtual void createMap();

};

