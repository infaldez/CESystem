#pragma once

#include "Actions.h"
#include "Component.h"
#include <vector>

class ActionMove
{
public:
	ActionMove();
	~ActionMove();

	void move(std::vector<Component*> comps, actions::moveActions act);
};

