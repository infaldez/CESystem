#include "MovementSystem.h"

#include <math.h>

#include "ComponentMovement.h"
#include "ComponentRender.h"
#include "ComponentPosition.h"

#include <iostream>

MovementSystem::MovementSystem()
{
}


MovementSystem::~MovementSystem()
{
}


void MovementSystem::runSystem(std::vector<std::unique_ptr<Entity>>& entityList)
{
	for (auto& ent : entityList)
	{
		std::array<bool, components::SIZE> cKey = ent->componentKey;
		if (cKey[components::COMPONENT_POSITION] == true && 
			cKey[components::COMPONENT_MOVEMENT] == true)
		{	
			ComponentMovement* cMovement = ent->getComponent<ComponentMovement>(components::COMPONENT_MOVEMENT);
			ComponentPosition* cPosition = ent->getComponent<ComponentPosition>(components::COMPONENT_POSITION);
		
			cPosition->setPosition(getNewPosition(cPosition->getPosition(), cMovement->getVelocity()));
		}
	}
}


sf::Vector2f MovementSystem::getNewPosition(sf::Vector2f position, sf::Vector2f velocity)
{
	position.x += velocity.x;
	position.y += velocity.y;

	return sf::Vector2f(position.x, position.y);
}