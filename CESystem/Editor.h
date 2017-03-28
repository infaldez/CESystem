#pragma once

#include <functional>
#include <memory>
#include <SFML/Graphics.hpp>

enum leftCLickState
{
	CREATE_SOLID,
	CREATE_PASSABLE,
	CREATE_PLAYER,
	CREATE_DAMAGEWALL,

	NOTHING
};

#define GSIZE = 32;

class LeftClick
{
public:
	leftCLickState state;
	sf::Vector2f mPos;
	int& layer;
	sf::Vector2u tilePos;

	LeftClick(int& lr) : layer(lr) , state(NOTHING), mPos(sf::Vector2f(0,0)), tilePos(sf::Vector2f(0,0)){};
	~LeftClick(){};
};

class RightClick
{
public:


	RightClick(){};
	~RightClick(){};
};

class Editor
{
private:
	//LeftClick leftclick;
	//RightClick rightclick;
public:
	Editor();
	~Editor();
};

