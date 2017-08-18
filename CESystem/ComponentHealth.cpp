#include "ComponentHealth.h"
#include <time.h>

ComponentHealth::ComponentHealth(int health, int invTime)
	: Component(components::COMPONENT_HEALTH)
{
	this->_health = health;
	this->_invulrenabilityTime = invTime;
	this->_LastDmgTime = 0;
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

void ComponentHealth::setInvulrenabilityTime(int time)
{
	this->_invulrenabilityTime = time;
}

int ComponentHealth::getInvulrenabilityTime()
{
	return this->_invulrenabilityTime;
}

int ComponentHealth::getLastDmgTime()
{
	return this->_LastDmgTime;
}

int ComponentHealth::setLastDmgTime()
{
	this->_LastDmgTime = clock();
}

void ComponentHealth::doDmg(int dmg)
{	
	if (clock() - _LastDmgTime > _invulrenabilityTime)
	{
		_health -= dmg;
		_LastDmgTime = clock();
	}
		
}