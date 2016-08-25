
#include <SFML/Graphics.hpp>
#include <iostream>

#include "EntityPlayer.h"
#include "EntityNonPlayer.h"

#include "RenderSystem.h"
#include "MovementSystem.h"
#include "CollisionSystem.h"
#include "InputSystem.h"
#include "MouseInput.h"

#include "Actions.h"

#include <math.h>

int main()
{
	std::vector<Entity*> entityList;

	sf::RenderWindow window(sf::VideoMode(800, 800), "Component Entity System");
	window.setFramerateLimit(60);

	RenderSystem renderSystem(window);
	MovementSystem movementSystem;
	CollisionSystem collisionSystem;
	InputSystem inputSystem;
	MouseInput mouseInput;
	
	for (int i = 0; i < 1000; ++i)
	{
		EntityNonPlayer* player2 = new EntityNonPlayer;
		player2->render.setTileset("texture1.bmp");
		player2->render.setTileSize(sf::Vector2u(64, 64));
		player2->render.setTilePosition(sf::Vector2u(64, i%64));
		player2->render.setPosition(sf::Vector2f(i, 700));
		
		player2->movement.setRotation(0);
		player2->movement.setSpeed(4);

		entityList.push_back(player2);
	}
	
	EntityPlayer* player = new EntityPlayer;
	player->render.setTileset("texture1.bmp");
	player->render.setTileSize(sf::Vector2u(64, 64));
	player->render.setTilePosition(sf::Vector2u(0, 64));
	player->render.setPosition(sf::Vector2f(100, 100));

	player->movement.setRotation(0);
	player->movement.setSpeed(0);

	player->playerInput.setInput(sf::Keyboard::D, actions::moveActions::MOVE_RIGHT);
	player->playerInput.setInput(sf::Keyboard::A, actions::moveActions::MOVE_LEFT);
	player->playerInput.setInput(sf::Keyboard::W, actions::moveActions::MOVE_UP);
	player->playerInput.setInput(sf::Keyboard::S, actions::moveActions::MOVE_DOWN);

	entityList.push_back(player);
	
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
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		mouseInput.runSystem(entityList, mousePosition);
		movementSystem.runSystem(entityList);
		//collisionSystem.runSystem(entityList);
		renderSystem.runSystem(entityList);
		
		window.display();
	}

	return 0;
}