#pragma once

#include "Actions.h"
#include "Component.h"
#include "Entity.h"
#include <vector>

class ActionMove
{
private:
	std::clock_t _dt;
public:
	ActionMove();
	~ActionMove();

	void move(Entity* entity, std::map<sf::Keyboard::Key, actions::moveActions> inputs, bool keys[], std::clock_t dt);
};

