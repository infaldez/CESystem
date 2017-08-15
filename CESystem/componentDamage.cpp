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