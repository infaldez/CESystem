#include "ComponentMovement.h"
#include "Component.h"

ComponentMovement::ComponentMovement(bool(&ckey)[components::SIZE])
{
	ckey[components::id::COMPONENT_MOVEMENT] = true;
	rotation = 0;
	speed = 0;
}


ComponentMovement::~ComponentMovement()
{
}


void ComponentMovement::setRotation(int rotation)
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