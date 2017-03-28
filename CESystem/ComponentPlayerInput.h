#pragma once

#include <map>
#include <SFML\Window.hpp>
#include <string>

#include "Component.h"
#include "Actions.h"
#include <boost/serialization/map.hpp>

class ComponentPlayerInput : public Component
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Component>(*this);
		ar & _inputMap;
	}
private:
	std::map <sf::Keyboard::Key, actions::moveActions> _inputMap;

public:
	ComponentPlayerInput();
	~ComponentPlayerInput();

	void setInput(sf::Keyboard::Key key, actions::moveActions action);
	std::map<sf::Keyboard::Key, actions::moveActions> getInputMap();
};

