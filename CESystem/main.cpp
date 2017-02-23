#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
#include <fstream>
#include <boost/archive/binary_iarchive.hpp>;
#include <boost/archive/binary_oarchive.hpp>;
#include <boost/serialization/vector.hpp>
#include <boost/serialization/unique_ptr.hpp>
#include <boost/serialization/map.hpp>

class EntityManager
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar.register_type(static_cast<ComponentPosition*>(NULL));
		ar.register_type(static_cast<ComponentRender*>(NULL));
		ar.register_type(static_cast<ComponentEvent*>(NULL));
		ar.register_type(static_cast<ComponentPlayerInput*>(NULL));
		ar.register_type(static_cast<ComponentMovement*>(NULL));
		ar.register_type(static_cast<componentMouseInput*>(NULL));
		ar.register_type(static_cast<ComponentHealth*>(NULL));
		ar.register_type(static_cast<componentDamage*>(NULL));
		ar.register_type(static_cast<ComponentCollision*>(NULL));
		ar.register_type(static_cast<ComponentAABB*>(NULL));

		ar.register_type(static_cast<MoveBlock*>(NULL));
		ar.register_type(static_cast<DoDamage*>(NULL));

		ar & _entityList;
	}
public:
	EntityManager(){}
	~EntityManager(){}
	std::vector<std::unique_ptr<Entity>> _entityList;

	void add(std::unique_ptr<Entity>& Ent)
	{
		_entityList.push_back(std::move(Ent));
	}

	void deleteEntities()
	{
		for (std::vector<std::unique_ptr<Entity>>::iterator it = _entityList.begin(); it != _entityList.end();)
		{
			if ((*it)->componentKey[components::DELETE] == true) {
				it = _entityList.erase(it);
			}
			else { ++it; }
		}
	}

};

namespace IOManager
{
	void save(std::string name, EntityManager& em)
	{
		// Save entityList to file
		std::ofstream ofs(name, std::fstream::binary);
		boost::archive::binary_oarchive oa(ofs);
		oa << em;
	}

	void load(std::string name, EntityManager& em)
	{
		// Load entityList from file
		std::ifstream ifs(name, std::fstream::binary);
		boost::archive::binary_iarchive ia(ifs);
		ia >> em;
	}
};

int main()
{
	EntityManager entityManager;
	std::vector<std::unique_ptr<Entity>>& entityList = entityManager._entityList;

	std::vector<std::string> tilesets =
	{
		"BGuy.png",
		"texture1.bmp",
		"textures.bmp",
		"NGuy.png"
	};

	// Sound test
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("beat.wav"))
		return -1;
	sf::Sound beat;
	beat.setBuffer(buffer);
	beat.setLoop(true);
	beat.play();

	sf::RenderWindow window(sf::VideoMode(800, 800), "Component Entity System");
	sf::View view(sf::FloatRect(0, 0, 800, 800));
	//window.setFramerateLimit(60);

	RenderSystem renderSystem(window);
	MovementSystem movementSystem;
	CollisionSystem collisionSystem;
	InputSystem inputSystem;
	MouseInput mouseInput;

	auto player = std::make_unique<Entity>();
	auto block = std::make_unique<Entity>();
	auto block2 = std::make_unique<Entity>();
	auto ground = std::make_unique<Entity>();

	player->addComponent(std::make_unique<ComponentRender>("NGuy.png", sf::Vector2u(128, 128), sf::Vector2u(0, 0), sf::Vector2u(64, 64), false));
	player->addComponent(std::make_unique<ComponentPosition>(sf::Vector2f(0.0, 0.0)));
	player->addComponent(std::make_unique<ComponentAABB>(sf::Vector2f(32.0, 16.0), sf::Vector2f(48.0, 96.0)));
	player->addComponent(std::make_unique<ComponentMovement>(0, 0));
	player->addComponent(std::make_unique<ComponentPlayerInput>());
	player->addComponent(std::make_unique<ComponentCollision>());
	player->getComponent<ComponentCollision>(components::COMPONENT_COLLISION)->setFlag(collisionType::SOLID, true);
	player->addComponent(std::make_unique<componentMouseInput>());
	player->addTag("player");

	player->getComponent<ComponentPlayerInput>(components::COMPONENT_INPUT)->setInput(sf::Keyboard::A, actions::moveActions::MOVE_LEFT);
	player->getComponent<ComponentPlayerInput>(components::COMPONENT_INPUT)->setInput(sf::Keyboard::D, actions::moveActions::MOVE_RIGHT);
	player->getComponent<ComponentPlayerInput>(components::COMPONENT_INPUT)->setInput(sf::Keyboard::W, actions::moveActions::MOVE_UP);
	player->getComponent<ComponentPlayerInput>(components::COMPONENT_INPUT)->setInput(sf::Keyboard::S, actions::moveActions::MOVE_DOWN);

	block->addComponent(std::make_unique<ComponentRender>("textures.bmp", sf::Vector2u(32, 32), sf::Vector2u(0, 0), sf::Vector2u(32, 32), false));
	block->addComponent(std::make_unique<ComponentPosition>(sf::Vector2f(32.0f, 64.0f)));
	block->addComponent(std::make_unique<ComponentAABB>(sf::Vector2f(32.0, 32.0), sf::Vector2f(0.0, 0.0)));
	block->addComponent(std::make_unique<ComponentCollision>());
	block->addComponent(std::make_unique<ComponentHealth>(10));
	block->getComponent<ComponentCollision>(components::COMPONENT_COLLISION)->setFlag(collisionType::SOLID, true);
	block->addTag("block");

	block2->addComponent(std::make_unique<ComponentRender>("texture1.bmp", sf::Vector2u(32, 32), sf::Vector2u(32, 32), sf::Vector2u(32, 32), false));
	block2->addComponent(std::make_unique<ComponentPosition>(sf::Vector2f(64, 32)));
	block2->addComponent(std::make_unique<ComponentAABB>(sf::Vector2f(32, 32), sf::Vector2f(0.0, 0.0)));
	block2->addComponent(std::make_unique<ComponentCollision>());
	block2->addComponent(std::make_unique<ComponentHealth>(10));
	block2->getComponent<ComponentCollision>(components::COMPONENT_COLLISION)->setFlag(collisionType::SOLID, true);
	block2->addComponent(std::make_unique<ComponentEvent>());
	block2->getComponent<ComponentEvent>(components::COMPONENT_EVENT)->addGlobalCollisionEvent(std::make_unique<MoveBlock>("block", sf::Vector2f(20, 20)));


	ground->addComponent(std::make_unique<ComponentRender>("texture1.bmp", sf::Vector2u(128, 128), sf::Vector2u(0, 64), sf::Vector2u(64, 64), true));
	ground->addComponent(std::make_unique<ComponentPosition>(sf::Vector2f(0, 0)));
	ground->addComponent(std::make_unique<ComponentEvent>());
	ground->addTag("ground");

	entityManager.add(ground);
	entityManager.add(player);
	entityManager.add(block);
	entityManager.add(block2);

	// RANDOM BLOCKS FOR TESTING COLLISION AND PERFORMANCE
	for (int i = 0; i < 800; ++i)
	{
		auto random = std::make_unique<Entity>();
		random->addComponent(std::make_unique<ComponentRender>("texture1.bmp", sf::Vector2u(32, 32), sf::Vector2u(64, 64), sf::Vector2u(32, 32), false));
		//random->addComponent(std::make_unique<ComponentMovement>(1, 0));
		random->addComponent(std::make_unique<ComponentPosition>(sf::Vector2f(rand() % 5000, rand() % 5000 + 100)));
		random->addComponent(std::make_unique<ComponentAABB>(sf::Vector2f(32.0, 32.0), sf::Vector2f(0.0, 0.0)));
		random->addComponent(std::make_unique<ComponentCollision>());
		random->addComponent(std::make_unique<ComponentHealth>(10));
		random->getComponent<ComponentCollision>(components::COMPONENT_COLLISION)->setFlag(collisionType::SOLID, true);

		entityList.push_back(std::move(random));
	}


	IOManager::save("entityList", entityManager);

	entityList.clear();

	IOManager::load("entityList", entityManager);

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
				inputSystem.runSystem(entityList, keys, currentFrameTime);
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
				sf::Vector2i mouseWorldPos = (sf::Vector2i)window.mapPixelToCoords(mousePosition);
				mouseInput.runSystem(entityList, mouseWorldPos, currentFrameTime);
				movementSystem.runSystem(entityList);
				collisionSystem.runSystem(entityList);

				for (auto& ent : entityList)
				{
					if (ent->hasTag("player"))
					{
						view.setCenter(ent->getComponent<ComponentPosition>(components::COMPONENT_POSITION)->getPosition());
						window.setView(view);
					}
				}

				deltaTime -= 16;
			}

			window.clear();
			renderSystem.runSystem(entityList, tilesets, deltaTime);
			window.display();

			entityManager.deleteEntities();

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