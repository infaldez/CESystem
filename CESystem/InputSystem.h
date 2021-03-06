#pragma once

#include <vector>

#include "Entity.h"
#include "ComponentPlayerInput.h"
#include "ComponentRender.h"
#include "ComponentCollision.h"
#include "ComponentMovement.h"
#include "ActionMove.h"

class InputSystem
{
private:
	ActionMove actionMove;
	std::map<std::string, sf::View>* _views;
public:
	void runSystem(std::vector<std::unique_ptr<Entity>>& entityList, bool keys[], float elapsed);

	InputSystem(std::map<std::string, sf::View>& views);
	~InputSystem();
	InputSystem() {};
};