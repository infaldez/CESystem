#include <SFML/Graphics.hpp>
#include <iostream>

#include "RenderSystem.h"
#include "MovementSystem.h"
#include "CollisionSystem.h"
#include "InputSystem.h"
#include "MouseInput.h"

#include "componentMouseInput.h"
#include "ComponentHealth.h"
#include "ComponentPosition.h"

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
	Entity* block = new Entity;
	Entity* block2 = new Entity;

	player->addComponent(new ComponentRender("texture1.bmp", sf::Vector2u(32.0, 32.0), sf::Vector2u(32.0, 32.0)));
	player->addComponent(new ComponentPosition(sf::Vector2f(0.0, 0.0)));
	player->addComponent(new ComponentAABB(sf::Vector2f(32.0, 32.0), sf::Vector2f(0.0, 0.0)));
	player->addComponent(new ComponentMovement(0, 0));
	player->addComponent(new ComponentPlayerInput());
	player->addComponent(new ComponentCollision());
	player->getComponent<ComponentCollision>(components::COMPONENT_COLLISION)->setFlag(collisionType::SOLID, true);
	player->addComponent(new componentMouseInput());

	player->getComponent<ComponentPlayerInput>(components::COMPONENT_INPUT)->setInput(sf::Keyboard::A, actions::moveActions::MOVE_LEFT);
	player->getComponent<ComponentPlayerInput>(components::COMPONENT_INPUT)->setInput(sf::Keyboard::D, actions::moveActions::MOVE_RIGHT);
	player->getComponent<ComponentPlayerInput>(components::COMPONENT_INPUT)->setInput(sf::Keyboard::W, actions::moveActions::MOVE_UP);
	player->getComponent<ComponentPlayerInput>(components::COMPONENT_INPUT)->setInput(sf::Keyboard::S, actions::moveActions::MOVE_DOWN);
	
	block->addComponent(new ComponentRender("texture1.bmp", sf::Vector2u(32.0, 32.0f), sf::Vector2u(32, 32)));
	//block->addComponent(new ComponentMovement(0, 0));
	block->addComponent(new ComponentPosition(sf::Vector2f(32.0f, 64.0f)));
	block->addComponent(new ComponentAABB(sf::Vector2f(32.0, 32.0), sf::Vector2f(0.0, 0.0)));
	block->addComponent(new ComponentCollision());
	block->addComponent(new ComponentHealth(10));
	block->getComponent<ComponentCollision>(components::COMPONENT_COLLISION)->setFlag(collisionType::SOLID, true);

	block2->addComponent(new ComponentRender("texture1.bmp", sf::Vector2u(32.0, 32.0f), sf::Vector2u(32, 32)));
	//block->addComponent(new ComponentMovement(0, 0));
	block2->addComponent(new ComponentPosition(sf::Vector2f(64, 64)));
	block2->addComponent(new ComponentAABB(sf::Vector2f(32.0, 32), sf::Vector2f(0.0, 0.0)));
	block2->addComponent(new ComponentCollision());
	block2->addComponent(new ComponentHealth(10));
	block2->getComponent<ComponentCollision>(components::COMPONENT_COLLISION)->setFlag(collisionType::SOLID, true);

	entityList.push_back(block2);
	entityList.push_back(block);
	entityList.push_back(player);
	
	// RANDOM BLOCKS FOR TESTING COLLISION
	
	for (int i = 0; i < 1000; ++i)
	{
		Entity* player2 = new Entity;
		player2->addComponent(new ComponentRender("texture1.bmp", sf::Vector2u(32, 32), sf::Vector2u(0, 0)));
		//player2->addComponent(new ComponentMovement(1, 0));
		player2->addComponent(new ComponentPosition(sf::Vector2f(rand() % 800, rand() % 800 + 100)));
		player2->addComponent(new ComponentAABB(sf::Vector2f(32.0, 32.0), sf::Vector2f(0.0, 0.0)));
		player2->addComponent(new ComponentCollision);
		player2->addComponent(new ComponentHealth(10));
		player2->getComponent<ComponentCollision>(components::COMPONENT_COLLISION)->setFlag(collisionType::SOLID, true);

		entityList.push_back(player2);
	}
	

	/*
	Loop
	*/
	bool running = true;
	bool pause = false;
	float lastFrameTime = clock();
	float deltaTime = 0.0;
	
	float fpsClockStart = clock();
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
			float currentFrameTime = clock();
			float elapsed = currentFrameTime - lastFrameTime;
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

			
			for (std::vector<Entity*>::iterator it = entityList.begin(); it != entityList.end();)
			{
				if ((*it)->componentKey[components::DELETE] == true) {
					it = entityList.erase(it);
				}
				else { ++it; }
			}

			float fpsClock = clock();
			fps++;
			if (fpsClock - fpsClockStart >= 1000)
			{
				fpsClockStart = clock();
				std::cout << fps << std::endl;
				//std::cout << entityList.size() << std::endl;
				fps = 0;
			}
		}

	}
	entityList.clear();

	return 0;
}