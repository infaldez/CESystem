#include "componentDamage.h"


componentDamage::componentDamage(int dmg, bool destroyOnImpact) : Component(components::COMPONENT_DAMAGE)
{
	this->_dmg = dmg;
	this->_destroyOnImpact = destroyOnImpact;
}


componentDamage::~componentDamage()
{
}


void componentDamage::setDamage(int dmg)
{
	this->_dmg = dmg;
}

int componentDamage::getDamage()
{
	return _dmg;
}

bool componentDamage::destroyOnImpact()
{
	return _destroyOnImpact;
}

void componentDamage::addAllyGroup(std::string ally)
{
	_allyGroups.push_back(ally);
}

std::vector<std::string> componentDamage::getAllyGroups()
{
	return _allyGroups;
}

bool componentDamage::inGroup(std::string g)
{
	for (auto group : _allyGroups)
	{
		if (group == g)
			return true;
	}
	return false;
}