#include "Game.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <memory>
#include <math.h>
#include <functional>
#include <time.h>

#include "RenderSystem.h"
#include "MovementSystem.h"
#include "CollisionSystem.h"
#include "InputSystem.h"
#include "MouseInput.h"

#include "Actions.h"

#include "TestMap.h"
#include "states.h"
#include "Editor.h"
#include "EntityCreator.h"
Game::Game() : leftA(this->layer)
{
}


Game::~Game()
{
}

void Game::run()
{
	std::vector<std::string> tilesets =
	{
		"completeSet.png",
	};

	// Sound test
	/*sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("beat.wav"))
	return -1;
	sf::Sound beat;
	beat.setBuffer(buffer);
	beat.setLoop(true);
	beat.play();*/

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Component Entity System");
	mapview = sf::View(sf::FloatRect(0, 0, 1920, 1080 * 0.65));
	menuView = sf::View(sf::FloatRect(960, 1024, 1920, 1080 * 0.35));
	mapview.setViewport(sf::FloatRect(0, 0, 1, 0.65));
	mapview.zoom(0.5);
	menuView.setViewport(sf::FloatRect(0, 0.65, 1, 0.35));
	window.setFramerateLimit(90);

	sf::FloatRect menu(0, 1080 * 0.65, 1920, 1080 * 0.35);
	sf::FloatRect tileEditor(0, 0, 1920, 1080 * 0.65);

	RenderSystem renderSystem(window, *this);
	MovementSystem movementSystem;
	CollisionSystem collisionSystem;
	InputSystem inputSystem(*this);
	MouseInput mouseInput(*this, leftA);

	TestMap map("test", this);
	//map.loadMap();
	std::vector<std::unique_ptr<Entity>>& entityList = map._entityList;
	entityList.clear();
	map.createMap();

	/*
	Loop
	*/
	float lastFrameTime = clock();
	float fpsClockStart = clock();

	loopstate.run();

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
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (menu.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
				{
					window.setView(menuView);
					sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
					sf::Vector2i mouseWorldPos = (sf::Vector2i)window.mapPixelToCoords(mousePosition);
					mouseInput.eventClick(entityList, mouseWorldPos);
				}
				else if (tileEditor.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
				{
					window.setView(mapview);
					sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
					sf::Vector2i mouseWorldPos = (sf::Vector2i)window.mapPixelToCoords(mousePosition);
					mouseInput.editorClick(entityList, mouseWorldPos);
				}
			}
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

			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			sf::Vector2i mouseWorldPos = (sf::Vector2i)window.mapPixelToCoords(mousePosition);
			inputSystem.runSystem(entityList, keys, currentFrameTime);
			mouseInput.runSystem(entityList, mouseWorldPos, currentFrameTime);

			while (deltaTime >= 16)
			{
				movementSystem.runSystem(entityList);
				collisionSystem.runSystem(entityList);
				deltaTime -= 16;
			}
			for (auto& e : entityList)
			{
				if (e->componentKey[components::COMPONENT_EVENT] == true)
				{
					Entity* ent = e.get();
					e->getComponent<ComponentEvent>(components::COMPONENT_EVENT)->runTimedEvent(ent, currentFrameTime);
				}
			}

			renderSystem.runSystem(entityList, tilesets);

			map._entityManager.deleteEntities();

			float fpsClock = clock();
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
}
