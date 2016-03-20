#include "ActionMove.h"

#include "ComponentRender.h"
#include "ComponentMovement.h"

ActionMove::ActionMove()
{
}


ActionMove::~ActionMove()
{
}


void ActionMove::move(std::vector<Component*> comps, actions::moveActions act)
{	
	for (int i = 0; i < comps.size(); ++i)
	{
		if (comps.at(i)->getComponentId() == components::id::COMPONENT_MOVEMENT)
		{
			ComponentMovement* comp = ((ComponentMovement*)comps.at(i));
			switch (act)
			{
			case actions::NONE:
				break;
			case actions::MOVE_RIGHT:
				comp->setRotation(90);
				break;
			case actions::MOVE_LEFT:
				comp->setRotation(-90);
				break;
			case actions::MOVE_UP:
				comp->setRotation(0);
				break;
			case actions::MOVE_DOWN:
				comp->setRotation(180);
				break;
			default:
				break;
			}
		}
	}
}