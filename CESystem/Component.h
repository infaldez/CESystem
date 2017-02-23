#pragma once

#include <boost/serialization/access.hpp>

namespace components
{
	enum id{
		EMPTY = 0,
		COMPONENT_RENDER,
		COMPONENT_MOVEMENT,
		COMPONENT_COLLISION,
		COMPONENT_INPUT,
		COMPONENT_MOUSEINPUT,
		COMPONENT_HEALTH,
		COMPONENT_DAMAGE,
		COMPONENT_AABB,
		COMPONENT_POSITION,
		COMPONENT_EVENT,

		DELETE,
		SIZE
	};
}

class Component
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & cId;
	}

public:
	int cId;
	Component(){};
	Component(enum components::id cid);
	virtual ~Component();
};