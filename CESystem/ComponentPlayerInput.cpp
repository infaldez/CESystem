#include "ComponentPlayerInput.h"

#include <iostream>

ComponentPlayerInput::ComponentPlayerInput(bool(&ckey)[components::SIZE])
{
	cid = components::id::COMPONENT_INPUT;
	ckey[components::id::COMPONENT_INPUT] = true;
}


ComponentPlayerInput::~ComponentPlayerInput()
{
}


void ComponentPlayerInput::setInput(sf::Keyboard::Key key, actions::moveActions action)
{
	inputMap[key] = action;
}


actions::moveActions ComponentPlayerInput::getAction()
{	
	for (std::map<sf::Keyboard::Key, actions::moveActions>::iterator i = inputMap.begin(); i != inputMap.end(); ++i)
	{
		if (sf::Keyboard::isKeyPressed(i->first))
			return i->second;
	}
	return actions::NONE;
}