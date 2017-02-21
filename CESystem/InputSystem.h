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
public:
	void runSystem(std::vector<std::unique_ptr<Entity>>& entityList, bool keys[], std::clock_t dt);

	InputSystem();
	~InputSystem();
};