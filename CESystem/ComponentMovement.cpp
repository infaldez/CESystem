#include "ComponentMovement.h"
#include "Component.h"

#include <iostream>

ComponentMovement::ComponentMovement(float speed, float rotation)
	: Component(components::COMPONENT_MOVEMENT)
{
	this->setRotation(rotation);
	this->setSpeed(speed);
}


ComponentMovement::~ComponentMovement()
{
}


void ComponentMovement::setRotation(float rotation)
{
	this->rotation = rotation;
	this->_setVelocity(this->rotation, this->speed);
}


void ComponentMovement::setSpeed(float speed)
{
	this->speed = speed;
	this->_setVelocity(this->rotation, this->speed);
}

void ComponentMovement::setVelocity(sf::Vector2f velocity)
{
	this->velocity = velocity;
}

/*
	Setting velocity also set scale
*/
void ComponentMovement::_setVelocity(float rotation, float speed)
{
	// Set scale
	float radians = (rotation - 90) * 3.14159265359 / 180;
	this->scale = sf::Vector2f(cos(radians), sin(radians));

	// Set velocity
	this->velocity = sf::Vector2f(this->scale.x * speed, this->scale.y * speed);
}



float ComponentMovement::getRotation()
{
	return rotation;
}


float ComponentMovement::getSpeed()
{
	return speed;
}


sf::Vector2f ComponentMovement::getVelocity()
{
	return velocity;
}


sf::Vector2f ComponentMovement::getScale()
{
	return scale;
}