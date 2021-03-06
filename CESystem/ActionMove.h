#pragma once

#include "Actions.h"
#include "Component.h"
#include "Entity.h"
#include <vector>

class ActionMove
{
private:
	float _dt;
public:
	ActionMove();
	~ActionMove();

	void move(Entity* entity, std::map<sf::Keyboard::Key, actions::moveActions> inputs, bool keys[], float elapsed);
};

