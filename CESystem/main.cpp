#include <SFML/Graphics.hpp>
#include <iostream>

#include "EntityPlayer.h"
#include "RenderSystem.h"
#include "MovementSystem.h"


int main()
{
	std::vector<Entity*> entityList;

	sf::RenderWindow window(sf::VideoMode(800, 800), "Component Enitity System");
	window.setFramerateLimit(60);

	RenderSystem renderSystem(window);
	MovementSystem movementSystem;

	for (int i = 0; i < 800; i++)
	{
		EntityPlayer* player = new EntityPlayer;
		player->render->setPosition(sf::Vector2f(i, i));
		player->movement->setRotation(180);
		player->movement->setSpeed(1*(1+(i*0.01)));
		entityList.push_back(player);
	}

	/*
	The Loop
	*/
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		movementSystem.runSystem(entityList);
		renderSystem.runSystem(entityList);
		window.display();
	}

	return 0;
}