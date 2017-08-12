#pragma once

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
	static leftCLickState state;
	static sf::Vector2f mPos;
	static int layer;
	static sf::Vector2u tilePos;

	LeftClick() {};
	~LeftClick() {};
};

class RightClick
{
public:
	RightClick(){};
	~RightClick(){};
};

class Loop
{
public:
	int layer = 0;
	bool running = true;
	bool pause = false;
	float deltaTime = 0.0;
	int fps = 0;

	//LeftClick leftA;
	sf::View mapview, menuView;

	Loop() {};

	virtual void runSystems() {};
	virtual void run() {};
};