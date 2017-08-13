#include "Editor.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <memory>
#include <math.h>
#include <functional>
#include <time.h>



#include "Actions.h"

#include "TestMap.h"
#include "states.h"
#include "EntityCreator.h"


EditorMode::EditorMode(sf::RenderWindow& window) : Loop(window)
{

	lastFrameTime = clock();
	fpsClockStart = clock();

	//window.create(sf::VideoMode(1920, 1080), "Component Entity System");

	sf::View mapView = sf::View(sf::FloatRect(0, 0, 1920, 1080 * 0.65));
	sf::View menuView = sf::View(sf::FloatRect(960, 1024, 1920, 1080 * 0.35));
	mapView.setViewport(sf::FloatRect(0, 0, 1, 0.65));
	mapView.zoom(0.5);
	menuView.setViewport(sf::FloatRect(0, 0.65, 1, 0.35));

	views.insert(std::pair<std::string, sf::View>("mapView", mapView));
	views.insert(std::pair<std::string, sf::View>("menuView", menuView));
	
	window.setFramerateLimit(90);

	menu = sf::FloatRect(0, 1080 * 0.65, 1920, 1080 * 0.35);
	tileEditor = sf::FloatRect(0, 0, 1920, 1080 * 0.65);

	tilesets =
	{
		"completeSet.png",
	};

	renderSystem = RenderSystem(window, views);
	movementSystem = MovementSystem();
	collisionSystem = CollisionSystem();
	inputSystem = InputSystem(views);
	mouseInput = MouseInput(views);

	map = std::make_unique<TestMap>("test", views);
	map->_entityList.clear();
	map->createMap();
}


EditorMode::~EditorMode()
{
	map->_entityList.clear();
}

void EditorMode::run()
{
	// Sound test
	/*sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("beat.wav"))
	return -1;
	sf::Sound beat;
	beat.setBuffer(buffer);
	beat.setLoop(true);
	beat.play();*/

	/*
	Loop
	*/
	
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
				window.setView(views.find("menuView")->second);
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
				sf::Vector2i mouseWorldPos = (sf::Vector2i)window.mapPixelToCoords(mousePosition);
				mouseInput.eventClick(map->_entityList, mouseWorldPos);
			}
			else if (tileEditor.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
			{
				window.setView(views.find("mapView")->second);
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
				sf::Vector2i mouseWorldPos = (sf::Vector2i)window.mapPixelToCoords(mousePosition);
				mouseInput.editorClick(map->_entityList, mouseWorldPos);
			}
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				StaticGameState::gameState = GAME;
				map->saveMap();
			}
		}
	}

	if (!pause)
	{
		/*float currentFrameTime = clock();
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
		}*/

		//sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		//sf::Vector2i mouseWorldPos = (sf::Vector2i)window.mapPixelToCoords(mousePosition);
		//inputSystem.runSystem(map->_entityList, keys, currentFrameTime);
		//mouseInput.runSystem(map->_entityList, mouseWorldPos, currentFrameTime);

		/*while (deltaTime >= 16)
		{
			//movementSystem.runSystem(map->_entityList);
			//collisionSystem.runSystem(map->_entityList);
			deltaTime -= 16;
		}*/
		/*for (auto& e : map->_entityList)
		{
			if (e->componentKey[components::COMPONENT_EVENT] == true)
			{
				Entity* ent = e.get();
				e->getComponent<ComponentEvent>(components::COMPONENT_EVENT)->runTimedEvent(ent, currentFrameTime);
			}
		}*/
	
		renderSystem.runSystem(map->_entityList, tilesets);

		map->_entityManager.deleteEntities();

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