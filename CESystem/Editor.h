#pragma once

#include <functional>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Loop.h"
#include <map>


class EditorMode : public Loop
{
private:
	sf::RenderWindow window;

	std::map<std::string, sf::View> views;
public:
	void run();

	EditorMode();
	~EditorMode();
};



