#include "ActionMove.h"

#include "Entity.h"
#include "ComponentRender.h"
#include "ComponentMovement.h"
#include "MovementSystem.h"

#include <iostream>

ActionMove::ActionMove()
{
}


ActionMove::~ActionMove()
{
}


void ActionMove::move(Entity* entity, std::map<sf::Keyboard::Key, actions::moveActions> inputs)
{	
	ComponentMovement* movement = entity->getComponent<ComponentMovement>(components::COMPONENT_MOVEMENT);
	ComponentRender* render = entity->getComponent<ComponentRender>(components::COMPONENT_RENDER);
	sf::Vector2f newPosition = render->getPosition();
	int rotation = 0;
	float speed = 0;

	MovementSystem movementSys;

	for (std::map<sf::Keyboard::Key, actions::moveActions>::iterator i = inputs.begin(); i != inputs.end(); ++i)
	{
		if (sf::Keyboard::isKeyPressed(i->first))
		{		
			switch (i->second)
			{
			default:
				break;
			case actions::MOVE_RIGHT:
				rotation = 90;
				speed = 4;
				newPosition = movementSys.newPosition(render->getPosition(), movementSys.countVelocity(movementSys.countScale(rotation), speed));
				break;
			case actions::MOVE_UP:
				rotation = 360;
				speed = 4;
				newPosition = movementSys.newPosition(render->getPosition(), movementSys.countVelocity(movementSys.countScale(rotation), speed));
				break;
			case actions::MOVE_LEFT:
				rotation = 270;
				speed = 4;
				newPosition = movementSys.newPosition(render->getPosition(), movementSys.countVelocity(movementSys.countScale(rotation), speed));
				break;
			case actions::MOVE_DOWN:
				rotation = 180;
				speed = 4;
				newPosition = movementSys.newPosition(render->getPosition(), movementSys.countVelocity(movementSys.countScale(rotation), speed));
				break;
			}	
			render->setPosition(newPosition);
		}	
	}
}









