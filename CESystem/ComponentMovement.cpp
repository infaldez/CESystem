#include "ComponentMovement.h"
#include "Component.h"

ComponentMovement::ComponentMovement(bool(&ckey)[components::SIZE])
{
	cid = components::id::COMPONENT_MOVEMENT;
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


int ComponentMovement::getRotation()
{
	return rotation;
}


int ComponentMovement::getSpeed()
{
	return speed;
}