#pragma once

#include "Component.h"

class componentMouseInput : public Component
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Component>(*this);
	}
public:
	componentMouseInput();
	~componentMouseInput();
};