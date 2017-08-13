#include "GameMode.h"


GameMode::GameMode(sf::RenderWindow& window) : Loop(window)
{
	lastFrameTime = clock();
	fpsClockStart = clock();

	//window.create(sf::VideoMode(1920, 1080), "Component Entity System");

	sf::View mapView = sf::View(sf::FloatRect(0, 0, 1920, 1080));
	views.insert(std::pair<std::string, sf::View>("mapView", mapView));

	window.setFramerateLimit(90);

	tilesets =
	{
		"completeSet.png",
	};

	renderSystem = RenderSystem(window, views);
	movementSystem = MovementSystem();
	collisionSystem = CollisionSystem();
	inputSystem = InputSystem(views);
	mouseInput = MouseInput(views);

	map = std::make_unique<DebugMap>("test");
	map->_entityList.clear();
}


GameMode::~GameMode()
{
}

void GameMode::run()
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
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				StaticGameState::gameState = EDITOR;
				map->loadMap();
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
		inputSystem.runSystem(map->_entityList, keys, currentFrameTime);
		mouseInput.runSystem(map->_entityList, mouseWorldPos, currentFrameTime);

		while (deltaTime >= 16)
		{
			movementSystem.runSystem(map->_entityList);
			collisionSystem.runSystem(map->_entityList);
			deltaTime -= 16;
		}
		for (auto& e : map->_entityList)
		{
			if (e->componentKey[components::COMPONENT_EVENT] == true)
			{
				Entity* ent = e.get();
				e->getComponent<ComponentEvent>(components::COMPONENT_EVENT)->runTimedEvent(ent, currentFrameTime);
			}
		}

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