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


void ActionMove::move(Entity* entity, std::map<sf::Keyboard::Key, actions::moveActions> inputs, bool keys[])
{	
	ComponentMovement* movement = entity->getComponent<ComponentMovement>(components::COMPONENT_MOVEMENT);
	int rotation = 0;
	float speed = 0;
	bool actions[actions::COUNT] = { false };

	for (std::map<sf::Keyboard::Key, actions::moveActions>::iterator i = inputs.begin(); i != inputs.end(); ++i)
	{
		if (keys[i->first] == true)
			actions[i->second] = true;
	}
	
	if (actions[actions::MOVE_RIGHT]){
		rotation = 90;
		speed = 4;
	}
	if (actions[actions::MOVE_LEFT]){
		rotation = 270;
		speed = 4;
	}
	if (actions[actions::MOVE_DOWN]){
		rotation = 180;
		speed = 4;
	}
	if (actions[actions::MOVE_UP]){
		rotation = 0;
		speed = 4;
	}
	if (actions[actions::MOVE_UP] && actions[actions::MOVE_RIGHT]){
		rotation = 45;
		speed = 4;
	}
	if (actions[actions::MOVE_RIGHT] && actions[actions::MOVE_DOWN]){
		rotation = 135;
		speed = 4;
	}
	if (actions[actions::MOVE_DOWN] && actions[actions::MOVE_LEFT]){
		rotation = 225;
		speed = 4;
	}
	if (actions[actions::MOVE_LEFT] && actions[actions::MOVE_UP]){
		rotation = 315;
		speed = 4;
	}
		
	movement->setRotation(rotation);
	movement->setSpeed(speed);

}