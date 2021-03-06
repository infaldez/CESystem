#include "ComponentPlayerInput.h"

#include <iostream>


ComponentPlayerInput::ComponentPlayerInput()
	: Component(components::COMPONENT_INPUT)
{
}


ComponentPlayerInput::~ComponentPlayerInput()
{
}


void ComponentPlayerInput::setInput(sf::Keyboard::Key key, actions::moveActions action)
{
	_inputMap[key] = action;
}


std::map<sf::Keyboard::Key, actions::moveActions> ComponentPlayerInput::getInputMap()
{		
	return _inputMap;
}