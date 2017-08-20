#pragma once

#include "Component.h"
#include <map>

class ComponentInventory : public Component
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Component>(*this);
		ar & _inventory;
	}
private:
	std::map<std::string, int> _inventory;

public:
	ComponentInventory();
	~ComponentInventory();

	void addItem(std::string, int amount = 1);
	void removeItem(std::string, int amount = 1);
	int getAmount(std::string);
};

