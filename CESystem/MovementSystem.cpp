#include "MovementSystem.h"

#include <math.h>
#include "EntityPlayer.h"

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
		if (entityList.at(i)->componentKey[components::id::COMPONENT_RENDER] == true && entityList.at(i)->componentKey[components::id::COMPONENT_MOVEMENT] == true)
		{	
			ComponentRender* render = entityList.at(i)->getComponent<ComponentRender>(components::COMPONENT_RENDER);
			ComponentMovement* movement = entityList.at(i)->getComponent<ComponentMovement>(components::COMPONENT_MOVEMENT);
		
			float rotation = movement->getRotation();
			float speed = movement->getSpeed();

			this->scale = countScale(rotation);
			this->velocity = countVelocity(this->scale, speed);

			render->setPosition(newPosition(render->getPosition(), velocity));

		}
	}
}


sf::Vector2f MovementSystem::countScale(int rotation)
{
	float radians = (rotation - 90)* 3.14 / 180;

	float scale_x = cos(radians);
	float scale_y = sin(radians); 

	return sf::Vector2f(scale_x, scale_y);
}


sf::Vector2f MovementSystem::countVelocity(sf::Vector2f scale, float speed)
{
	float velocity_x = scale.x * speed;
	float velocity_y = scale.y * speed;

	return sf::Vector2f(velocity_x, velocity_y);
}


sf::Vector2f MovementSystem::newPosition(sf::Vector2f position, sf::Vector2f velocity)
{
	position.x += velocity.x;
	position.y += velocity.y;

	return sf::Vector2f(position.x, position.y);
}