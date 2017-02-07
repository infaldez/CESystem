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


void MovementSystem::runSystem(std::vector<Entity*> entityList)
{
	for (int i = 0; i < entityList.size(); i++)
	{
		std::array<bool, components::SIZE> cKey = entityList.at(i)->componentKey;
		if (cKey[components::COMPONENT_POSITION] == true && 
			cKey[components::COMPONENT_MOVEMENT] == true)
		{	
			ComponentMovement* cMovement = entityList.at(i)->getComponent<ComponentMovement>(components::COMPONENT_MOVEMENT);
			ComponentPosition* cPosition = entityList.at(i)->getComponent<ComponentPosition>(components::COMPONENT_POSITION);
		
			cPosition->setPosition(newPosition(cPosition->getPosition(), cMovement->getVelocity()));
		}
	}
}


sf::Vector2f MovementSystem::newPosition(sf::Vector2f position, sf::Vector2f velocity)
{
	position.x += velocity.x;
	position.y += velocity.y;

	return sf::Vector2f(position.x, position.y);
}