#include "ComponentHealth.h"


ComponentHealth::ComponentHealth(int health)
{
	this->health = health;
	cId = components::COMPONENT_HEALTH;
}


ComponentHealth::~ComponentHealth()
{
}


void ComponentHealth::setHealth(int health)
{
	this->health = health;
}


int ComponentHealth::getHealth()
{
	return health;
}