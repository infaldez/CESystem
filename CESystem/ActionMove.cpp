#include "ActionMove.h"

#include "Entity.h"
#include "ComponentRender.h"
#include "ComponentMovement.h"
#include "MovementSystem.h"

#include <iostream>

#define SPEED 5.0f

ActionMove::ActionMove()
{
}


ActionMove::~ActionMove()
{
}


void ActionMove::move(Entity* entity, std::map<sf::Keyboard::Key, actions::moveActions> inputs, bool keys[])
{	
	ComponentMovement* movement = entity->getComponent<ComponentMovement>(components::COMPONENT_MOVEMENT);
	float rotation = 0.0f;
	float speed = 0.0f;
	bool actions[actions::COUNT] = { false };

	for (std::map<sf::Keyboard::Key, actions::moveActions>::iterator i = inputs.begin(); i != inputs.end(); ++i)
	{
		if (keys[i->first] == true)
			actions[i->second] = true;
	}
	
	if (actions[actions::MOVE_RIGHT]){
		rotation = 90.0f;
		speed = SPEED;
	}
	if (actions[actions::MOVE_LEFT]){
		rotation = 270.0f;
		speed = SPEED;
	}
	if (actions[actions::MOVE_DOWN]){
		rotation = 180.0f;
		speed = SPEED;
	}
	if (actions[actions::MOVE_UP]){
		rotation = 0.0f;
		speed = SPEED;
	}
	if (actions[actions::MOVE_UP] && actions[actions::MOVE_RIGHT]){
		rotation = 45.0f;
		speed = SPEED;
	}
	if (actions[actions::MOVE_RIGHT] && actions[actions::MOVE_DOWN]){
		rotation = 135.0f;
		speed = SPEED;
	}
	if (actions[actions::MOVE_DOWN] && actions[actions::MOVE_LEFT]){
		rotation = 225.0f;
		speed = SPEED;
	}
	if (actions[actions::MOVE_LEFT] && actions[actions::MOVE_UP]){
		rotation = 315.0f;
		speed = SPEED;
	}
		
	movement->setRotation(rotation);
	movement->setSpeed(speed);

}