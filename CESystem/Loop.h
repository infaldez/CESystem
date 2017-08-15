#pragma once

#include <SFML/Graphics.hpp>
#include "Enums.h"

class StaticGameState {
public:
	static GameState gameState;
};

enum leftCLickState
{
	CREATE_SOLID,
	CREATE_PASSABLE,
	CREATE_PLAYER,
	CREATE_DAMAGEWALL,
	CREATE_ENEMY,

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
	sf::RenderWindow& window;

	bool running = true;
	bool pause = false;
	bool resume = false;

	float deltaTime = 0.0;
	int fps = 0;

	float lastFrameTime;
	float fpsClockStart;

	Loop(sf::RenderWindow& window);

	virtual void runSystems() {};
	virtual void run() {};
};