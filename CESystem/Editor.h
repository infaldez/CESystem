#pragma once

#include <functional>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Loop.h"
#include <map>
#include "RenderSystem.h"
#include "MovementSystem.h"
#include "CollisionSystem.h"
#include "InputSystem.h"
#include "MouseInput.h"
#include "TestMap.h"

class EditorMode : public Loop
{
private:
	std::unique_ptr<TestMap> map;
	//std::vector<std::unique_ptr<Entity>>& entityList;

	RenderSystem renderSystem;
	MovementSystem movementSystem;
	CollisionSystem collisionSystem;
	InputSystem inputSystem;
	MouseInput mouseInput;

	//sf::RenderWindow window;
	sf::FloatRect menu, tileEditor;

	std::map<std::string, sf::View> views;
	std::vector<std::string> tilesets;

public:
	void run();

	EditorMode(sf::RenderWindow& window);
	~EditorMode();
};



