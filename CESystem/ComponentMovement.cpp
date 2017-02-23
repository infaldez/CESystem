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
	this->_rotation = rotation;
	this->_setVelocity(this->_rotation, this->_speed);
}


void ComponentMovement::setSpeed(float speed)
{
	this->_speed = speed;
	this->_setVelocity(this->_rotation, this->_speed);
}

void ComponentMovement::setVelocity(sf::Vector2f velocity)
{
	this->_velocity = velocity;
}

/*
	Setting velocity also set scale
*/
void ComponentMovement::_setVelocity(float rotation, float speed)
{
	// Set scale
	float radians = (rotation - 90) * 3.14159265359 / 180;
	this->_scale = sf::Vector2f(cos(radians), sin(radians));

	// Set velocity
	this->_velocity = sf::Vector2f(this->_scale.x * speed, this->_scale.y * speed);
}


float ComponentMovement::getRotation()
{
	return _rotation;
}


float ComponentMovement::getSpeed()
{
	return _speed;
}


sf::Vector2f ComponentMovement::getVelocity()
{
	return _velocity;
}


sf::Vector2f ComponentMovement::getScale()
{
	return _scale;
}