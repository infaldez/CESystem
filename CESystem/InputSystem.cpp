#include "InputSystem.h"

#include <iostream>

#include "Actions.h"
#include "ActionMove.h"
#include "EntityPlayer.h"

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
		if (entityList.at(i)->componentKey[components::id::COMPONENT_INPUT])
		{	
			for (int j = 0; j < entityList.at(i)->getComponents().size(); ++j)
			{
				if (entityList.at(i)->getComponents().at(j)->getComponentId() == components::id::COMPONENT_INPUT)
				{
					std::vector<Component*> comps = entityList.at(i)->getComponents();
					actions::moveActions act = ((ComponentPlayerInput*)entityList.at(i)->getComponents().at(j))->getAction();
					
					actionMove.move(comps, act);
				}
			}
		}
	}
}