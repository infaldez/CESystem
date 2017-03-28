#pragma once

#include "Component.h"

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
	}
private:
	bool _flags[collisionType::COUNT];

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
};

