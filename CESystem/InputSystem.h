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
	void runSystem(std::vector<Entity*> entityList);

	InputSystem();
	~InputSystem();
};