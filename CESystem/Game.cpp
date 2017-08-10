#include "Game.h"


Game::Game()
{
	this->gameState = &editorMode;
}


Game::~Game()
{
}


void Game::run()
{
	gameState->run();
}
