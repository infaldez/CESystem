#include "MovementSystem.h"

#include <math.h>
#include "EntityPlayer.h"

#include "InputSystem.h"

#include <iostream>

MovementSystem::MovementSystem()
{
}


MovementSystem::~MovementSystem()
{
}

/*
	TODO:
	Split this to smaller functions
*/
void MovementSystem::runSystem(std::vector<Entity*> &entityList)
{
	for (int i = 0; i < entityList.size(); i++)
	{
		if (entityList.at(i)->componentKey[components::id::COMPONENT_RENDER] && entityList.at(i)->componentKey[components::id::COMPONENT_MOVEMENT])
		{	
			ComponentRender* render = NULL;
			ComponentMovement* movement = NULL;

			for (int j = 0; j < entityList.at(i)->getComponents().size(); ++j)
			{
				if (entityList.at(i)->getComponents().at(j)->getComponentId() == components::id::COMPONENT_RENDER)
					render = ((ComponentRender*)entityList.at(i)->getComponents().at(j));	
				if (entityList.at(i)->getComponents().at(j)->getComponentId() == components::id::COMPONENT_MOVEMENT)
					movement = ((ComponentMovement*)entityList.at(i)->getComponents().at(j));
					
				if (render != NULL && movement != NULL)
				{	
					int rotation = movement->getRotation();
					float speed = movement->getSpeed();
					sf::CircleShape shape = render->getShape();

					this->scale = countScale(rotation);
					this->velocity = countVelocity(this->scale, speed);

					render->setPosition(newPosition(shape.getPosition(), velocity));
				}
			}
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