#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "RenderSystem.h"
#include "MovementSystem.h"
#include "CollisionSystem.h"
#include "InputSystem.h"
#include "MouseInput.h"

#include "componentMouseInput.h"
#include "ComponentHealth.h"
#include "ComponentPosition.h"
#include "ComponentEvent.h"

#include <functional>
#include "Events.h"
#include "Actions.h"

#include <math.h>
#include <time.h>

int main()
{
	std::vector<std::unique_ptr<Entity>> entityList;
	std::vector<std::string> tilesets =
	{
		"textures.bmp",
		"texture1.bmp"
	};

	sf::RenderWindow window(sf::VideoMode(800, 800), "Component Entity System");
	sf::View view(sf::FloatRect(0, 0, 800, 800));
	//view.setViewport(sf::FloatRect(0, 0, 1, 1));
	
	//window.setFramerateLimit(60);

	RenderSystem renderSystem(window);
	MovementSystem movementSystem;
	CollisionSystem collisionSystem;
	InputSystem inputSystem;
	MouseInput mouseInput;
	
	auto &player = std::make_unique<Entity>();
	auto block = std::make_unique<Entity>();
	auto block2 = std::make_unique<Entity>();

	player->addComponent(std::make_unique<ComponentRender>("textures.bmp", sf::Vector2u(32, 32), sf::Vector2u(10, 10)));
	player->addComponent(std::make_unique<ComponentPosition>(sf::Vector2f(0.0, 0.0)));
	player->addComponent(std::make_unique<ComponentAABB>(sf::Vector2f(32.0, 32.0), sf::Vector2f(0.0, 0.0)));
	player->addComponent(std::make_unique<ComponentMovement>(0, 0));
	player->addComponent(std::make_unique<ComponentPlayerInput>());
	player->addComponent(std::make_unique<ComponentCollision>());
	player->getComponent<ComponentCollision>(components::COMPONENT_COLLISION)->setFlag(collisionType::SOLID, true);
	player->addComponent(std::make_unique<componentMouseInput>());

	player->getComponent<ComponentPlayerInput>(components::COMPONENT_INPUT)->setInput(sf::Keyboard::A, actions::moveActions::MOVE_LEFT);
	player->getComponent<ComponentPlayerInput>(components::COMPONENT_INPUT)->setInput(sf::Keyboard::D, actions::moveActions::MOVE_RIGHT);
	player->getComponent<ComponentPlayerInput>(components::COMPONENT_INPUT)->setInput(sf::Keyboard::W, actions::moveActions::MOVE_UP);
	player->getComponent<ComponentPlayerInput>(components::COMPONENT_INPUT)->setInput(sf::Keyboard::S, actions::moveActions::MOVE_DOWN);
	
	block->addComponent(std::make_unique<ComponentRender>("textures.bmp", sf::Vector2u(32, 32), sf::Vector2u(32, 32)));
	block->addComponent(std::make_unique<ComponentPosition>(sf::Vector2f(32.0f, 64.0f)));
	block->addComponent(std::make_unique<ComponentAABB>(sf::Vector2f(32.0, 32.0), sf::Vector2f(0.0, 0.0)));
	block->addComponent(std::make_unique<ComponentCollision>());
	block->addComponent(std::make_unique<ComponentHealth>(10));
	block->getComponent<ComponentCollision>(components::COMPONENT_COLLISION)->setFlag(collisionType::SOLID, true);
	block->addTag("block");

	block2->addComponent(std::make_unique<ComponentRender>("texture1.bmp", sf::Vector2u(32, 32), sf::Vector2u(32, 32)));
	block2->addComponent(std::make_unique<ComponentPosition>(sf::Vector2f(64, 64)));
	block2->addComponent(std::make_unique<ComponentAABB>(sf::Vector2f(32, 32), sf::Vector2f(0.0, 0.0)));
	block2->addComponent(std::make_unique<ComponentCollision>());
	block2->addComponent(std::make_unique<ComponentHealth>(10));
	block2->getComponent<ComponentCollision>(components::COMPONENT_COLLISION)->setFlag(collisionType::SOLID, true);
	block2->addComponent(std::make_unique<ComponentEvent>());
	block2->getComponent<ComponentEvent>(components::COMPONENT_EVENT)->addGlobalCollisionEvent(tagTest);
	
	entityList.push_back(std::move(block2));
	entityList.push_back(std::move(block));
	entityList.push_back(std::move(player));
	// Danger?, only for testing
	Entity* p = entityList.at(2).get();

	// RANDOM BLOCKS FOR TESTING COLLISION AND PERFORMANCE
	/*for (int i = 0; i < 1000; ++i)
	{
		auto random = std::make_unique<Entity>();
		random->addComponent(std::make_unique<ComponentRender>("texture1.bmp", sf::Vector2u(32, 32), sf::Vector2u(0, 0)));
		//random->addComponent(std::make_unique<ComponentMovement>(1, 0));
		random->addComponent(std::make_unique<ComponentPosition>(sf::Vector2f(rand() % 5000, rand() % 5000 + 100)));
		random->addComponent(std::make_unique<ComponentAABB>(sf::Vector2f(32.0, 32.0), sf::Vector2f(0.0, 0.0)));
		random->addComponent(std::make_unique<ComponentCollision>());
		random->addComponent(std::make_unique<ComponentHealth>(10));
		random->getComponent<ComponentCollision>(components::COMPONENT_COLLISION)->setFlag(collisionType::SOLID, true);

		entityList.push_back(std::move(random));
	}*/

	/*
	Loop
	*/
	bool running = true;
	bool pause = false;
	std::clock_t lastFrameTime = clock();
	float deltaTime = 0.0;
	
	std::clock_t fpsClockStart = clock();
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
			std::clock_t currentFrameTime = clock();
			std::clock_t elapsed = currentFrameTime - lastFrameTime;
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
			// Danger?, only for testing
			view.setCenter(p->getComponent<ComponentPosition>(components::COMPONENT_POSITION)->getPosition());
			window.setView(view);

			window.clear();
			renderSystem.runSystem(entityList, tilesets);
			window.display();
			
			for (std::vector<std::unique_ptr<Entity>>::iterator it = entityList.begin(); it != entityList.end();)
			{
				if ((*it)->componentKey[components::DELETE] == true) {
					it = entityList.erase(it);
				}
				else { ++it; }
			}

			std::clock_t fpsClock = clock();
			fps++;
			if (fpsClock - fpsClockStart >= 1000)
			{
				fpsClockStart = clock();
				std::cout << fps << std::endl;
				fps = 0;
			}
		}

	}
	entityList.clear();

	return 0;
	
}