#include "MouseInput.h"
#include "componentDamage.h"

#include <iostream>
#include "ComponentEvent.h"
#include "Events.h"

MouseInput::MouseInput()
{
	this->time = 0;
}


MouseInput::~MouseInput()
{
}


void MouseInput::runSystem(std::vector<std::unique_ptr<Entity>>& entityList, sf::Vector2i mousePosition, float time)
{
	for (std::size_t i = 0; i != entityList.size(); ++i)
	{
		std::array<bool, components::SIZE> cKey = entityList.at(i)->componentKey;
		if (cKey[components::COMPONENT_MOUSEINPUT] == true &&
			cKey[components::COMPONENT_RENDER] == true)
		{
			sf::Vector2i mPos = sf::Vector2i(mousePosition.x, mousePosition.y);
			
			if (time - this->time >= 200)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					ComponentRender* render = entityList.at(i)->getComponent<ComponentRender>(components::COMPONENT_RENDER);
					ComponentPosition* position = entityList.at(i)->getComponent<ComponentPosition>(components::COMPONENT_POSITION);
					sf::Vector2f rPos = position->getPosition();
					float rotation = atan2f(rPos.y - mPos.y, rPos.x - mPos.x) * 180.f / 3.14f;

					auto click = std::make_unique<Entity>();
					click->addComponent(std::make_unique<ComponentRender>("texture1.bmp", sf::Vector2u(32, 32), sf::Vector2u(64, 64)));
					click->addComponent(std::make_unique<ComponentPosition>(sf::Vector2f(rPos.x + 16, rPos.y + 16)));
					click->addComponent(std::make_unique<ComponentAABB>(sf::Vector2f(32.0, 32.0), sf::Vector2f(0.0, 0.0)));
					click->addComponent(std::make_unique<ComponentCollision>());
					click->addComponent(std::make_unique<ComponentMovement>(10, rotation - 90));
					click->addComponent(std::make_unique<componentDamage>(10));
					click->addComponent(std::make_unique<ComponentEvent>());
					click->getComponent<ComponentEvent>(components::COMPONENT_EVENT)->addLocalCollisionEvent(causeDamage);

					click->getComponent<ComponentCollision>(components::COMPONENT_COLLISION)->setFlag(collisionType::SOLID, false);
					entityList.push_back(std::move(click));
					this->time = time;
				}
			}
		}
	}
}