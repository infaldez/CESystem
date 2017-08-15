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
		ar & _destroyOnImpact;
	}
private: 
	int _dmg;
	bool _destroyOnImpact;

public:
	componentDamage(int dmg, bool destroyOnImpact);
	componentDamage(){}
	~componentDamage();

	int getDamage();
	void setDamage(int dmg);
	bool destroyOnImpact();
};

