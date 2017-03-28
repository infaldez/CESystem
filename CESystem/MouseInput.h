#pragma once

#include "Entity.h"
#include "Game.h"

class MouseInput
{
private:
	double time;
	Game& _game;
	LeftClick& _leftC;
public:
	void runSystem(std::vector<std::unique_ptr<Entity>>& entityList, sf::Vector2i mousePosition, float time);
	void eventClick(std::vector<std::unique_ptr<Entity>>& entityList, sf::Vector2i mousePosition);
	void editorClick(std::vector<std::unique_ptr<Entity>>& entityList, sf::Vector2i mousePosition);

	MouseInput(Game& game, LeftClick& leftC);
	~MouseInput();
};