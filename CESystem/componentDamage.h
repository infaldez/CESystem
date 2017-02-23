#pragma once

#include "Component.h"

class componentDamage : public Component
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Component>(*this);
		ar & _dmg;
	}
private: 
	int _dmg;

public:
	componentDamage(int dmg);
	componentDamage(){}
	~componentDamage();

	int getDamage();
	void setDamage(int dmg);
};

