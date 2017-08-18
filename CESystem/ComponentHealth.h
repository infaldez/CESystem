#pragma once

#include "Component.h"

class ComponentHealth : public Component
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Component>(*this);
		ar & _health;
		ar & _invulrenabilityTime;
		ar & _LastDmgTime;
	}
private:
	int _health;
	int _invulrenabilityTime;
	int _LastDmgTime;

public:
	ComponentHealth(int health, int _invulrenabilityTime);
	ComponentHealth(){}
	~ComponentHealth();

	void setHealth(int health);
	void setInvulrenabilityTime(int time);
	int getInvulrenabilityTime();
	int getHealth();
	int getLastDmgTime();
	int setLastDmgTime();
	void doDmg(int dmg);
};