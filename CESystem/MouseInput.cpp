#include "MouseInput.h"
#include "componentDamage.h"

#include <iostream>
#include "ComponentEvent.h"
#include "Events.h"
#include "Game.h"
#include "states.h"
#include "EntityCreator.h"

#include "Loop.h"

MouseInput::MouseInput(std::map<std::string, sf::View>& views)
{
	this->_views = &views;
	this->time = 0;
}


MouseInput::~MouseInput()
{
}


void MouseInput::runSystem(std::vector<std::unique_ptr<Entity>>& entityList, sf::Vector2i mousePosition, float time)
{
	this->time += time;
	for (std::size_t i = 0; i != entityList.size(); ++i)
	{
		std::array<bool, components::SIZE> cKey = entityList.at(i)->componentKey;
		if (cKey[components::COMPONENT_MOUSEINPUT] == true &&
			cKey[components::COMPONENT_RENDER] == true)
		{
			sf::Vector2i mPos = sf::Vector2i(mousePosition.x, mousePosition.y);

			if (this->time >= 200)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					ComponentPosition* position = entityList.at(i)->getComponent<ComponentPosition>(components::COMPONENT_POSITION);
					sf::Vector2f rPos = position->getPosition();
					float rotation = atan2f(rPos.y - mPos.y, rPos.x - mPos.x) * 180.f / 3.14f;

					auto click = std::make_unique<Entity>();
					click->addComponent(std::make_unique<ComponentRender>("completeSet.png", sf::Vector2u(32, 32), sf::Vector2u(64, 64), sf::Vector2u(32, 32), false));
					click->addComponent(std::make_unique<ComponentPosition>(sf::Vector2f(rPos.x + 16, rPos.y + 16)));
					click->addComponent(std::make_unique<ComponentAABB>(sf::Vector2f(32.0, 32.0), sf::Vector2f(0.0, 0.0)));
					click->addComponent(std::make_unique<ComponentCollision>(false));
					click->addComponent(std::make_unique<ComponentMovement>(10, rotation - 90));
					click->addComponent(std::make_unique<componentDamage>(10, true));
					click->addComponent(std::make_unique<ComponentEvent>());
					auto e = click->getComponent<ComponentEvent>(components::COMPONENT_EVENT);
					e->addCollisionEvent(std::make_unique<DoDamage>());

					click->getComponent<componentDamage>(components::COMPONENT_DAMAGE)->addAllyGroup("ally");

					click->getComponent<ComponentCollision>(components::COMPONENT_COLLISION)->setFlag(collisionType::SOLID, false);
					entityList.push_back(std::move(click));
					this->time = 0;
				}
			}
		}
		/*if (cKey[components::COMPONENT_EVENT])
		{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		Entity* ent = entityList.at(i).get();

		auto e = ent->getComponent<ComponentEvent>(components::COMPONENT_EVENT);
		e->runClickEvent(ent, mousePosition);
		}
		}*/
	}

}

void MouseInput::eventClick(std::vector<std::unique_ptr<Entity>>& entityList, sf::Vector2i mousePosition)
{
	for (std::size_t i = 0; i != entityList.size(); ++i)
	{
		std::array<bool, components::SIZE> cKey = entityList.at(i)->componentKey;

		if (cKey[components::COMPONENT_EVENT])
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				Entity* ent = entityList.at(i).get();

				auto e = ent->getComponent<ComponentEvent>(components::COMPONENT_EVENT);
				e->runClickEvent(ent, mousePosition);
			}
		}
	}
}

void MouseInput::editorClick(std::vector<std::unique_ptr<Entity>>& entityList, sf::Vector2i mousePosition)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		switch (LeftClick::state)
		{
		case CREATE_SOLID:
			entityList.push_back(entitycreator::createSolid(sf::Vector2f(mousePosition), LeftClick::tilePos, LeftClick::layer));
			break;
		case CREATE_PASSABLE:
			entityList.push_back(entitycreator::createPassable(sf::Vector2f(mousePosition), LeftClick::tilePos, LeftClick::layer));
			break;
		case CREATE_PLAYER:
			entityList.push_back(entitycreator::player(sf::Vector2f(mousePosition), LeftClick::layer));
			break;
		case CREATE_DAMAGEWALL:
			entityList.push_back(entitycreator::damagewall(sf::Vector2f(mousePosition), LeftClick::layer));
			break;
		case CREATE_ENEMY:
			entityList.push_back(entitycreator::enemy(sf::Vector2f(mousePosition), LeftClick::layer));
			break;
		case CREATE_ITEM:
			entityList.push_back(entitycreator::createItem(sf::Vector2f(mousePosition), LeftClick::layer));
			break;
		default:
			break;
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		for (auto& ent : entityList)
		{
			if (ent->componentKey[components::COMPONENT_POSITION] == true)
			{
			
				sf::Vector2i pos = (sf::Vector2i)ent->getComponent<ComponentPosition>(components::COMPONENT_POSITION)->getPosition();

				if (pos.x/32 == mousePosition.x/32 && pos.y/32 == mousePosition.y/32)
				{
					ent->componentKey[components::DELETE] = true;
				}
					
			}			
		}
	}
}
