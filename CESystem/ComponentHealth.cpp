#include "ComponentHealth.h"


ComponentHealth::ComponentHealth(int health)
	: Component(components::COMPONENT_HEALTH)
{
	this->health = health;
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