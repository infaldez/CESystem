#pragma once

#include "Component.h"
#include <string>
#include <vector>

enum collisionType{
	SOLID,

	COUNT
};

class ComponentCollision : public Component
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Component>(*this);
		ar & _flags;
		ar & _groups;
	}
private:
	bool _flags[collisionType::COUNT];

	/*
		If entity has group it will only collide within that group.
		All other entities with collision will be ignored
	*/
	std::vector<std::string> _groups;

public:
	ComponentCollision(){}
	ComponentCollision(bool solid);
	~ComponentCollision();

	void setFlag(collisionType cType, bool state) {
		_flags[cType] = state;
	}

	bool getFlag(collisionType cType) {
		return _flags[cType];
	}

	void addGroup(std::string group)
	{
		_groups.push_back(group);
	}

	std::vector<std::string> getGroups()
	{
		return _groups;
	}

	bool inGroup(std::string group)
	{
		for (auto g : _groups)
		{
			if (g == group)
				return true;
		}
		return false;
	}

	bool belongsToGroup()
	{
		return _groups.size() > 0;
	}
};

