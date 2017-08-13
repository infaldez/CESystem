#include "GameMode.h"


GameMode::GameMode(sf::RenderWindow& window) : Loop(window)
{
}


GameMode::~GameMode()
{
}

void GameMode::run()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed){
			window.close();
			running = false;
		}
		if (event.type == sf::Event::LostFocus)
			pause = true;
		if (event.type == sf::Event::GainedFocus)
			pause = false;
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				StaticGameState::gameState = EDITOR;
			}
		}
	}
}