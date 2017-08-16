#pragma once

#include "Loop.h"
#include "RenderSystem.h"
#include "MovementSystem.h"
#include "CollisionSystem.h"
#include "InputSystem.h"
#include "MouseInput.h"
#include "AnimationSystem.h"
#include "TestMap.h"
#include "DebugMap.h"

class GameMode : public Loop
{
private:
	bool init = false;
	float currentFrameTime = 0;
	float elapsed = 0;

	std::unique_ptr<DebugMap> map;

	RenderSystem renderSystem;
	MovementSystem movementSystem;
	CollisionSystem collisionSystem;
	InputSystem inputSystem;
	MouseInput mouseInput;
	AnimationSystem animationSystem;


	std::map<std::string, sf::View> views;
	std::vector<std::string> tilesets;
public:
	GameMode(sf::RenderWindow& window);
	~GameMode();

	void run();
};

