#include "componentDamage.h"


componentDamage::componentDamage(int dmg)
{
	cId = components::COMPONENT_DAMAGE;

	this->dmg = dmg;
}


componentDamage::~componentDamage()
{
}


void componentDamage::setDamage(int dmg)
{
	this->dmg = dmg;
}

int componentDamage::getDamage()
{
	return dmg;
}