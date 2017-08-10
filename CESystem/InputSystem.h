#pragma once

#include <vector>

#include "Entity.h"
#include "ComponentPlayerInput.h"
#include "ComponentRender.h"
#include "ComponentCollision.h"
#include "ComponentMovement.h"
#include "ActionMove.h"
#include "Game.h"

class InputSystem
{
private:
	ActionMove actionMove;
	Loop& _game;
public:
	void runSystem(std::vector<std::unique_ptr<Entity>>& entityList, bool keys[], float dt);

	InputSystem(Loop& game);
	~InputSystem();
};