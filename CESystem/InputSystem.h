#pragma once

#include <vector>

#include "Entity.h"
#include "ComponentPlayerInput.h"
#include "ComponentRender.h"
#include "ComponentCollision.h"
#include "ComponentMovement.h"

class InputSystem
{
public:
	void runSystem(std::vector<Entity*> &entityList);

	InputSystem();
	~InputSystem();
};


class SystemEntity
{
public:
	ComponentRender* render;
	ComponentMovement* movement;
	ComponentCollision* collision;
	ComponentPlayerInput* playerInput;
};