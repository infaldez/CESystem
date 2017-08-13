#pragma once

#include "Loop.h"
#include "RenderSystem.h"
#include "MovementSystem.h"
#include "CollisionSystem.h"
#include "InputSystem.h"
#include "MouseInput.h"
#include "TestMap.h"
#include "DebugMap.h"

class GameMode : public Loop
{
private:
	std::unique_ptr<DebugMap> map;

	RenderSystem renderSystem;
	MovementSystem movementSystem;
	CollisionSystem collisionSystem;
	InputSystem inputSystem;
	MouseInput mouseInput;

	std::map<std::string, sf::View> views;
	std::vector<std::string> tilesets;
public:
	GameMode(sf::RenderWindow& window);
	~GameMode();

	void run();
};

