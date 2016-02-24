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

void MovementSystem::runSystem(std::vector<Entity*> &entityList)
{
	for (int i = 0; i < entityList.size(); i++)
	{
		if (entityList.at(i)->componentKey[COMPONENT_RENDER] && entityList.at(i)->componentKey[COMPONENT_MOVEMENT])
		{	
			int rotation = ((EntityPlayer*)entityList.at(i))->movement->getRotation();
			float speed = ((EntityPlayer*)entityList.at(i))->movement->getSpeed();
			sf::CircleShape shape = ((EntityPlayer*)entityList.at(i))->render->getShape();
			
			//std::cout << shape.getPosition().x << std::endl;

			this->scale = countScale(rotation);
			this->velocity = countVelocity(this->scale, speed);

			((EntityPlayer*)entityList.at(i))->render->setPosition(newPosition(shape.getPosition(), velocity));
		}
	}
}

sf::Vector2f MovementSystem::countScale(int rotation)
{
	float radians = (rotation - 90)* 3.14 / 180; // change angle to radians

	float scale_x = cos(radians); //scale x
	float scale_y = sin(radians); //scale y

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