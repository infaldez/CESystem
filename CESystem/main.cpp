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
	
	Entity* player = new Entity;

	player->addComponent(new ComponentRender("texture1.bmp", sf::Vector2u(64, 64), sf::Vector2u(32, 32), sf::Vector2f(500, 500)));
	player->addComponent(new ComponentMovement(0, 0));
	player->addComponent(new ComponentPlayerInput());
	player->addComponent(new ComponentCollision());

	player->getComponent<ComponentPlayerInput>(components::COMPONENT_INPUT)->setInput(sf::Keyboard::A, actions::moveActions::MOVE_LEFT);
	player->getComponent<ComponentPlayerInput>(components::COMPONENT_INPUT)->setInput(sf::Keyboard::D, actions::moveActions::MOVE_RIGHT);
	player->getComponent<ComponentPlayerInput>(components::COMPONENT_INPUT)->setInput(sf::Keyboard::W, actions::moveActions::MOVE_UP);
	player->getComponent<ComponentPlayerInput>(components::COMPONENT_INPUT)->setInput(sf::Keyboard::S, actions::moveActions::MOVE_DOWN);

	entityList.push_back(player);

	/*for (int i = 0; i < 1000; i++)
	{
		EntityPlayer* player2 = new EntityPlayer;
		player2->addComponent(new ComponentRender("texture1.bmp", sf::Vector2u(64, 64), sf::Vector2u(0, 0), sf::Vector2f(i, 120)));
		player2->addComponent(new ComponentMovement(3, 0));
		entityList.push_back(player2);
	}*/
	
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
		collisionSystem.runSystem(entityList);
		renderSystem.runSystem(entityList);

		window.display();
	}

	return 0;
}