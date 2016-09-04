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
#include <time.h>

int main()
{
	std::vector<Entity*> entityList;

	sf::RenderWindow window(sf::VideoMode(800, 800), "Component Entity System");
	//window.setFramerateLimit(60);

	RenderSystem renderSystem(window);
	MovementSystem movementSystem;
	CollisionSystem collisionSystem;
	InputSystem inputSystem;
	MouseInput mouseInput;
	
	Entity* player = new Entity;

	player->addComponent(new ComponentRender("texture1.bmp", sf::Vector2u(64, 64), sf::Vector2u(32, 32), sf::Vector2f(0, 0)));
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
		player2->addComponent(new ComponentRender("texture1.bmp", sf::Vector2u(64, 64), sf::Vector2u(0, 0), sf::Vector2i(i, 120)));
		player2->addComponent(new ComponentMovement(3, 0));
		entityList.push_back(player2);
	}*/
	
	/*
	Loop
	*/
	bool running = true;
	bool pause = false;
	double lastFrameTime = clock();
	double deltaTime = 0.0;
	
	double fpsClockStart = clock();
	int fps = 0;

	//loop start
	while (running)
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
		}

		if (!pause)
		{
			double currentFrameTime = clock();
			double elapsed = currentFrameTime - lastFrameTime;
			lastFrameTime = currentFrameTime;
			deltaTime += elapsed;

			//read inputs and register pressed keys in keys[]
			bool keys[sf::Keyboard::KeyCount] = { false };
			for (int keyI = sf::Keyboard::Unknown; keyI != sf::Keyboard::KeyCount; keyI++)
			{
				sf::Keyboard::Key key = static_cast<sf::Keyboard::Key>(keyI);

				if (sf::Keyboard::isKeyPressed(key)){
					keys[key] = true;
				}
			}

			while (deltaTime >= 16)
			{
				inputSystem.runSystem(entityList, keys);
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
				mouseInput.runSystem(entityList, mousePosition, currentFrameTime);
				movementSystem.runSystem(entityList);
				collisionSystem.runSystem(entityList);
				
				deltaTime -= 16;
			}

			window.clear();
			renderSystem.runSystem(entityList);
			window.display();

			double fpsClock = clock();
			fps++;
			if (fpsClock - fpsClockStart >= 1000)
			{
				fpsClockStart = clock();
				//std::cout << fps << std::endl;
				fps = 0;
			}
		}

	}

	return 0;
}