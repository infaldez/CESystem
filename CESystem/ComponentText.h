#pragma once
#include "Component.h"
#include <string>
#include <SFML\Graphics\Font.hpp>

class ComponentText : public Component
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Component>(*this);
		ar & _text;
		ar & _font;
	}
private:
	std::string _text;
	std::string _font;

public:
	void setText(std::string text);
	void setFont(std::string font);

	std::string getText();
	std::string getFont();

	ComponentText(){};
	ComponentText(std::string text, std::string font);
	~ComponentText();
};

