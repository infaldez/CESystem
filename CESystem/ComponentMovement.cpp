#include "ComponentMovement.h"
#include "Component.h"

#include <iostream>

ComponentMovement::ComponentMovement(float speed, float rotation)
{
	cId = components::COMPONENT_MOVEMENT;
	
	this->speed = speed;
	this->rotation = rotation;
}


ComponentMovement::ComponentMovement(bool(&ckey)[components::SIZE])
{
	cId = components::COMPONENT_MOVEMENT;
	ckey[components::id::COMPONENT_MOVEMENT] = true;
	rotation = 0;
	speed = 0;
}


ComponentMovement::~ComponentMovement()
{
}


void ComponentMovement::setRotation(float rotation)
{
	this->rotation = rotation;
}


void ComponentMovement::setSpeed(float speed)
{
	this->speed = speed;
}


float ComponentMovement::getRotation()
{
	return rotation;
}


float ComponentMovement::getSpeed()
{
	return speed;
}