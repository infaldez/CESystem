
#include <SFML/Graphics.hpp>
#include <iostream>

#include "EntityPlayer.h"
#include "EntityNonPlayer.h"

#include "RenderSystem.h"
#include "MovementSystem.h"
#include "CollisionSystem.h"
#include "InputSystem.h"

#include "Actions.h"

#include <math.h>

int main()
{
	std::vector<Entity*> entityList;

	sf::RenderWindow window(sf::VideoMode(800, 800), "Component Enitity System");
	window.setFramerateLimit(60);

	RenderSystem renderSystem(window);
	MovementSystem movementSystem;
	CollisionSystem collisionSystem;
	InputSystem inputSystem;
	
	EntityPlayer* player = new EntityPlayer;
	player->render->setPosition(sf::Vector2f(300, 700));
	player->movement->setRotation(0);
	player->movement->setSpeed(1);

	player->playerInput->setInput(sf::Keyboard::A, actions::moveActions::MOVE_LEFT);
	player->playerInput->setInput(sf::Keyboard::D, actions::moveActions::MOVE_RIGHT);
	player->playerInput->setInput(sf::Keyboard::W, actions::moveActions::MOVE_UP);
	player->playerInput->setInput(sf::Keyboard::S, actions::moveActions::MOVE_DOWN);

	entityList.push_back(player);

	for (int i = 0; i < 100; ++i)
	{
		EntityNonPlayer* nonP = new EntityNonPlayer;
		nonP->render->setPosition(sf::Vector2f(i*5, i*3));
		entityList.push_back(nonP);
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
		
		inputSystem.runSystem(entityList);
		movementSystem.runSystem(entityList);
		//collisionSystem.runSystem(entityList);
		renderSystem.runSystem(entityList);
		window.display();
	}

	return 0;
}