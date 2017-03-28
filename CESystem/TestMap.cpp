#include "TestMap.h"
#include "ComponentText.h"

#include "MenuButton.h"
#include "Events.h"
#include "EntityCreator.h"
#include "Game.h"
#include "states.h"
#include "Editor.h"


TestMap::TestMap(std::string name, Game* game) 
	: Map(name), _game(game)
{
}


TestMap::~TestMap()
{
}

void TestMap::createMap()
{
	//SELECT PASSABLE
	LeftClick* lclick = &_game->leftA;
	for (int x = 0, y = 0; y < 14; ++x)
	{
		auto button = std::make_unique<Entity>();
		button->addComponent(std::make_unique<ComponentRender>("completeSet.png", sf::Vector2u(32, 32), sf::Vector2u(32 * x, 32 * y), sf::Vector2u(32, 32), true));
		button->addComponent(std::make_unique<ComponentPosition>(sf::Vector2f(960 + 32 * x, 1024 +  32 * y)));
		button->addComponent(std::make_unique<ComponentEvent>());
		button->addComponent(std::make_unique<ComponentAABB>(sf::Vector2f(32.0, 32.0), sf::Vector2f(0.0, 0.0)));
		ComponentEvent* e = button->getComponent<ComponentEvent>(components::COMPONENT_EVENT);

		e->addClickEvent(std::make_unique<Click<bool>>([x, y, lclick]()->bool
		{
			lclick->state = CREATE_PASSABLE;
			lclick->tilePos = sf::Vector2u(32 * x, 32 * y);
			return true;
		}));
		button->setSave(false);
		_entityManager.add(button);

		if (x == 32)
		{
			y++;
			x = -1;
		}			
	}
	// SELECT SOLIDS
	for (int x = 0, y = 14; y < 32; ++x)
	{
		auto button = std::make_unique<Entity>();
		button->addComponent(std::make_unique<ComponentRender>("completeSet.png", sf::Vector2u(32, 32), sf::Vector2u(32 * x, 32 * y), sf::Vector2u(32, 32), true));
		button->addComponent(std::make_unique<ComponentPosition>(sf::Vector2f(960 + 32 * x, 1024 + 32 * y)));
		button->addComponent(std::make_unique<ComponentEvent>());
		button->addComponent(std::make_unique<ComponentAABB>(sf::Vector2f(32.0, 32.0), sf::Vector2f(0.0, 0.0)));
		ComponentEvent* e = button->getComponent<ComponentEvent>(components::COMPONENT_EVENT);

		e->addClickEvent(std::make_unique<Click<bool>>([x, y, lclick]()->bool
		{
			lclick->state = CREATE_SOLID;
			lclick->tilePos = sf::Vector2u(32 * x, 32 * y);
			return true;
		}));
		button->setSave(false);
		_entityManager.add(button);

		if (x == 32)
		{
			y++;
			x = -1;
		}
	}


	/*// SAVE BUTTON
	auto button = std::make_unique<Entity>();
	button->addComponent(std::make_unique<ComponentText>("Save", "arial.ttf"));
	button->addComponent(std::make_unique<ComponentPosition>(sf::Vector2f(1000, 1050)));
	button->addComponent(std::make_unique<ComponentEvent>());
	button->addComponent(std::make_unique<ComponentAABB>(sf::Vector2f(64.0, 30.0), sf::Vector2f(0.0, 0.0)));
	auto e = button->getComponent<ComponentEvent>(components::COMPONENT_EVENT);
	e->addClickEvent(std::make_unique<Save>("test", _entityManager));

	button->setSave(false);
	_entityManager.add(button);*/


	// PLAYER BUTTON
	auto button = std::make_unique<Entity>();
	button->addComponent(std::make_unique<ComponentRender>("completeSet.png", sf::Vector2u(64, 64), sf::Vector2u(0, 32 * 26), sf::Vector2u(64, 64), false));
	button->addComponent(std::make_unique<ComponentPosition>(sf::Vector2f(960 + 32 * 20, 1024)));
	button->addComponent(std::make_unique<ComponentEvent>());
	button->addComponent(std::make_unique<ComponentAABB>(sf::Vector2f(64.0, 64.0), sf::Vector2f(0.0, 0.0)));
	auto e = button->getComponent<ComponentEvent>(components::COMPONENT_EVENT);
	e->addClickEvent(std::make_unique<Click<bool>>([lclick]()->bool
	{
		lclick->state = CREATE_PLAYER;
		return true;
	}));
	button->setSave(false);
	_entityManager.add(button);

	// DAMAGE WALL BUTTON
	button = std::make_unique<Entity>();
	button->addComponent(std::make_unique<ComponentRender>("completeSet.png", sf::Vector2u(32, 32), sf::Vector2u(32 * 2, 32 * 17), sf::Vector2u(32, 32), false));
	button->addComponent(std::make_unique<ComponentPosition>(sf::Vector2f(960 + 32 * 22, 1024)));
	button->addComponent(std::make_unique<ComponentEvent>());
	button->addComponent(std::make_unique<ComponentAABB>(sf::Vector2f(32, 32), sf::Vector2f(0.0, 0.0)));
	e = button->getComponent<ComponentEvent>(components::COMPONENT_EVENT);
	e->addClickEvent(std::make_unique<Click<bool>>([lclick]()->bool
	{
		lclick->state = CREATE_DAMAGEWALL;
		return true;
	}));

	button->setSave(false);
	_entityManager.add(button);

	// LAYER + BUTTON
	button = std::make_unique<Entity>();
	button->addComponent(std::make_unique<ComponentText>("Layer +", "arial.ttf"));
	button->addComponent(std::make_unique<ComponentPosition>(sf::Vector2f(1100, 1050)));
	button->addComponent(std::make_unique<ComponentEvent>());
	button->addComponent(std::make_unique<ComponentAABB>(sf::Vector2f(50.0, 30.0), sf::Vector2f(0.0, 0.0)));
	e = button->getComponent<ComponentEvent>(components::COMPONENT_EVENT);
	e->addClickEvent(std::make_unique<Click<bool>>([lclick]() -> bool
	{
		lclick->layer += 1;
		return true;
	}));

	button->setSave(false);
	_entityManager.add(button);

	button = std::make_unique<Entity>();
	button->addComponent(std::make_unique<ComponentText>("Layer -", "arial.ttf"));
	button->addComponent(std::make_unique<ComponentPosition>(sf::Vector2f(1200, 1050)));
	button->addComponent(std::make_unique<ComponentEvent>());
	button->addComponent(std::make_unique<ComponentAABB>(sf::Vector2f(50.0, 30.0), sf::Vector2f(0.0, 0.0)));
	e = button->getComponent<ComponentEvent>(components::COMPONENT_EVENT);
	e->addClickEvent(std::make_unique<Click<bool>>([lclick]() -> bool
	{
		lclick->layer -= 1;
		return true;
	}));

	button->setSave(false);
	_entityManager.add(button);

	//NEXT Button
	auto nbutton = std::make_unique<Entity>();
	nbutton->addComponent(std::make_unique<ComponentRender>("completeSet.png", sf::Vector2u(32, 32), sf::Vector2u(32 * 31, 32 * 30), sf::Vector2u(32, 32), false));
	nbutton->addComponent(std::make_unique<ComponentPosition>(sf::Vector2f(960 + 32 * 59, 1024)));
	nbutton->addComponent(std::make_unique<ComponentEvent>());
	nbutton->addComponent(std::make_unique<ComponentAABB>(sf::Vector2f(32, 32), sf::Vector2f(0.0, 0.0)));
	auto en = nbutton->getComponent<ComponentEvent>(components::COMPONENT_EVENT);
	ComponentPosition* npos = nbutton->getComponent<ComponentPosition>(components::COMPONENT_POSITION);
	sf::View& menu = _game->menuView;
	//BACK BUTTON
	auto bbutton = std::make_unique<Entity>();
	bbutton->addComponent(std::make_unique<ComponentRender>("completeSet.png", sf::Vector2u(32, 32), sf::Vector2u(32 * 31, 32 * 31), sf::Vector2u(32, 32), false));
	bbutton->addComponent(std::make_unique<ComponentPosition>(sf::Vector2f(960 + 32 * 58, 1024)));
	bbutton->addComponent(std::make_unique<ComponentEvent>());
	bbutton->addComponent(std::make_unique<ComponentAABB>(sf::Vector2f(32, 32), sf::Vector2f(0.0, 0.0)));
	auto eb = bbutton->getComponent<ComponentEvent>(components::COMPONENT_EVENT);
	ComponentPosition *bpos = bbutton->getComponent<ComponentPosition>(components::COMPONENT_POSITION);
	//BACK BUTTON EVENT
	eb->addClickEvent(std::make_unique<Click<bool>>([bpos, npos, &menu]()->bool
	{
		menu.move(0, -32 * 8);
		bpos->setPosition(sf::Vector2f(bpos->getPosition().x, bpos->getPosition().y - 32 * 8));
		npos->setPosition(sf::Vector2f(npos->getPosition().x, npos->getPosition().y - 32 * 8));
		return true;
	}));
	//NEXT BUTTON EVENT
	en->addClickEvent(std::make_unique<Click<bool>>([bpos, npos, &menu]()->bool
	{
		menu.move(0, 32 * 8);
		npos->setPosition(sf::Vector2f(npos->getPosition().x, npos->getPosition().y + 32 * 8));
		bpos->setPosition(sf::Vector2f(bpos->getPosition().x, bpos->getPosition().y + 32 * 8));
		return true;
	}));

	nbutton->setSave(false);
	_entityManager.add(nbutton);

	bbutton->setSave(false);
	_entityManager.add(bbutton);
}
