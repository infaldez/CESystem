#include "componentDamage.h"


componentDamage::componentDamage(int dmg) : Component(components::COMPONENT_DAMAGE)
{
	this->_dmg = dmg;
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