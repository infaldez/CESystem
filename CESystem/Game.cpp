#include "Game.h"

Game::Game() : editorMode(EditorMode(window)), gameMode(GameMode(window))
{
	window.create(sf::VideoMode(1920, 1080), "Component Entity System");
	running = true;
	this->gameLoop = &editorMode;
	StaticGameState::gameState = EDITOR;
}


Game::~Game()
{
}


void Game::run()
{
	while (running)
	{
		switch (StaticGameState::gameState)
		{
		case GameState::EDITOR:
			gameLoop = &editorMode;
			break;
		case GameState::GAME:
			gameLoop = &gameMode;
			break;
		}
		
		gameLoop->run();
	}
}