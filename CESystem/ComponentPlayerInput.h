#pragma once

#include <map>
#include <SFML\Window.hpp>
#include <string>

#include "Component.h"
#include "Actions.h"

class ComponentPlayerInput : public Component
{
private:
	std::map <sf::Keyboard::Key, actions::moveActions> inputMap;

public:
	ComponentPlayerInput(bool(&ckey)[components::SIZE]);
	~ComponentPlayerInput();

	void setInput(sf::Keyboard::Key key, actions::moveActions action);
	actions::moveActions getAction();
};

