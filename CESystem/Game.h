#pragma once

#include <SFML/Graphics.hpp>

#include <functional>
#include <memory>
#include "Editor.h"
#include "GameMode.h"
#include <iostream>

#include "Enums.h"




class Game
{
private:
	bool running;
public:
	sf::RenderWindow window;

	EditorMode editorMode;
	GameMode gameMode;

	Loop* gameLoop;

	Game();
	~Game();

	void run();
};

