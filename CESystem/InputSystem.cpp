#include "InputSystem.h"

#include <iostream>

#include "Actions.h"
#include "ActionMove.h"
#include "EntityPlayer.h"
#include <map>

InputSystem::InputSystem(Loop& game) : _game(game)
{
}


InputSystem::~InputSystem()
{
}


void InputSystem::runSystem(std::vector<std::unique_ptr<Entity>>& entityList, bool keys[], float dt)
{
	for (std::size_t i = 0; i != entityList.size(); i++)
	{
		std::array<bool, components::SIZE> cKey = entityList.at(i)->componentKey;
		if (cKey[components::id::COMPONENT_INPUT] == true)
		{	
			Entity* entity = entityList.at(i).get();
			std::map<sf::Keyboard::Key, actions::moveActions> inputs = entityList.at(i)->getComponent<ComponentPlayerInput>(components::COMPONENT_INPUT)->getInputMap();
					
			actionMove.move(entity, inputs, keys, dt);
		}
	}
}