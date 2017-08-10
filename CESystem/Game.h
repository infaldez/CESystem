#pragma once

#include <SFML/Graphics.hpp>

#include <functional>
#include <memory>
#include "Editor.h"
#include <iostream>

enum GameState {
	GAME,
	EDITOR
};


class GameMode : public Loop
{
	void run()  { std::cout << "game" << std::endl; }
};

class Game
{
private:

public:

	EditorMode editorMode;
	GameMode gameMode;

	Loop* gameState;


	Game();
	~Game();

	void run();

};

