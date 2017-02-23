#include "ComponentHealth.h"


ComponentHealth::ComponentHealth(int health)
	: Component(components::COMPONENT_HEALTH)
{
	this->_health = health;
}


ComponentHealth::~ComponentHealth()
{
}


void ComponentHealth::setHealth(int health)
{
	this->_health = health;
}


int ComponentHealth::getHealth()
{
	return _health;
}