#pragma once

#include <SFML/Graphics.hpp>

#include <functional>
#include <memory>
#include "Editor.h"
class Loop
{
public:
	virtual void runSystems(){}
	virtual void run()
	{
			runSystems();
	}
};

class EditorLoop : public Loop
{
	virtual void runSystems(){ }
};

class Game
{
private:
	bool running = true;
	bool pause = false;
	float deltaTime = 0.0;
	int fps = 0;
	int layer = 0;
public:

	EditorLoop loopstate;

	sf::View mapview;
	sf::View menuView;
	LeftClick leftA;

	Game();
	~Game();

	void run();

};

