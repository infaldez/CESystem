#pragma once

#include "Loop.h"

class GameMode : public Loop
{
public:
	GameMode(sf::RenderWindow& window);
	~GameMode();

	void run();
};

