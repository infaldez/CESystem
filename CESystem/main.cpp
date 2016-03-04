#include <SFML/Graphics.hpp>
#include <iostream>

#include "EntityPlayer.h"
#include "RenderSystem.h"
#include "MovementSystem.h"
#include "CollisionSystem.h"

#include <math.h>

int main()
{
	std::vector<Entity*> entityList;

	sf::RenderWindow window(sf::VideoMode(800, 800), "Component Enitity System");
	window.setFramerateLimit(60);

	RenderSystem renderSystem(window);
	MovementSystem movementSystem;
	CollisionSystem collisionSystem;

	for (int i = 0; i < 800; i++)
	{
		EntityPlayer* player = new EntityPlayer;
		player->render->setPosition(sf::Vector2f(i, i));
		player->movement->setRotation(i);
		player->movement->setSpeed(1);
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
		//collisionSystem.runSystem(entityList);
		renderSystem.runSystem(entityList);
		window.display();
	}

	return 0;
}