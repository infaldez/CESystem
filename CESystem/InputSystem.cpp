#include "InputSystem.h"

#include <iostream>

#include "Actions.h"
#include "ActionMove.h"
#include "EntityPlayer.h"
#include <map>

InputSystem::InputSystem()
{
}


InputSystem::~InputSystem()
{
}


void InputSystem::runSystem(std::vector<Entity*> entityList)
{
	for (int i = 0; i < entityList.size(); i++)
	{
		if (entityList.at(i)->componentKey[components::id::COMPONENT_INPUT] == true)
		{	
			Entity* entity = entityList.at(i);
			std::map<sf::Keyboard::Key, actions::moveActions> inputs = entityList.at(i)->getComponentPlayerInput().getInputMap();
					
			actionMove.move(entity, inputs);
		}
	}
}

