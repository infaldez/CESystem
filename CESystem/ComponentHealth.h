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
	}
private:
	int _health;

public:
	ComponentHealth(int health);
	ComponentHealth(){}
	~ComponentHealth();

	void setHealth(int health);
	int getHealth();
};