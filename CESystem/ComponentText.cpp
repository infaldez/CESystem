#include "ComponentText.h"


void ComponentText::setText(std::string text)
{
	_text = text;
}

void ComponentText::setFont(std::string font)
{
	_font = font;
}

std::string ComponentText::getText()
{
	return _text;
}

std::string ComponentText::getFont()
{
	return _font;
}

ComponentText::ComponentText(std::string text, std::string font)
	: Component(components::COMPONENT_TEXT) 
{
	_text = text;
	_font = font;
}


ComponentText::~ComponentText()
{
}
