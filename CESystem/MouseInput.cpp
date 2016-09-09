#include "MouseInput.h"
#include "componentDamage.h"

#include <iostream>

MouseInput::MouseInput()
{
	this->time = 0;
}


MouseInput::~MouseInput()
{
}


void MouseInput::runSystem(std::vector<Entity*>& entityList, sf::Vector2i mousePosition, float time)
{
	for (int i = 0; i < entityList.size(); i++)
	{
		std::array<bool, components::SIZE> cKey = entityList.at(i)->componentKey;
		if (cKey[components::COMPONENT_MOUSEINPUT] == true &&
			cKey[components::COMPONENT_RENDER] == true)
		{
			sf::Vector2f mPos = sf::Vector2f(mousePosition.x, mousePosition.y);
			
			if (time - this->time >= 200)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					ComponentRender* render = entityList.at(i)->getComponent<ComponentRender>(components::COMPONENT_RENDER);
					sf::Vector2f rPos = render->getPosition();
					float rotation = atan2f(rPos.y - mPos.y, rPos.x - mPos.x) * 180 / 3.14;

					Entity* click = new Entity;
					click->addComponent(new ComponentRender("texture1.bmp", sf::Vector2u(32, 32), sf::Vector2u(64, 64), sf::Vector2f(rPos.x + 16, rPos.y + 16)));
					click->addComponent(new ComponentCollision());
					click->addComponent(new ComponentMovement(30, rotation - 90));
					click->addComponent(new componentDamage(1));

					click->getComponent<ComponentCollision>(components::COMPONENT_COLLISION)->setFlag(collisionType::SOLID, false);
					entityList.push_back(click);
					this->time = time;
				}
			}
		}
	}
}