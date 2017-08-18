#pragma once

#include "Component.h"
#include <string>
#include <vector>

class componentDamage : public Component
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Component>(*this);
		ar & _dmg;
		ar & _destroyOnImpact;
		ar & _allyGroups;
	}
private: 
	int _dmg;
	bool _destroyOnImpact;
	std::vector<std::string> _allyGroups;

public:
	componentDamage(int dmg, bool destroyOnImpact);
	componentDamage(){}
	~componentDamage();

	int getDamage();
	void setDamage(int dmg);
	bool destroyOnImpact();
	void addAllyGroup(std::string ally);
	std::vector<std::string>  getAllyGroups();
	bool inGroup(std::string group);

};

