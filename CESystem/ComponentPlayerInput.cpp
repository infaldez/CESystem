#include "ComponentPlayerInput.h"

#include <iostream>


ComponentPlayerInput::ComponentPlayerInput() {
	cId = components::COMPONENT_INPUT;
}


ComponentPlayerInput::ComponentPlayerInput(bool(&ckey)[components::SIZE])
{
	cId = components::COMPONENT_INPUT;
	ckey[components::id::COMPONENT_INPUT] = true;
}


ComponentPlayerInput::~ComponentPlayerInput()
{
}


void ComponentPlayerInput::setInput(sf::Keyboard::Key key, actions::moveActions action)
{
	inputMap[key] = action;
}


std::map<sf::Keyboard::Key, actions::moveActions> ComponentPlayerInput::getInputMap()
{		
	return inputMap;
}