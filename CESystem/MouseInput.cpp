#include "MouseInput.h"
#include "EntityNonPlayer.h"

#include <iostream>

MouseInput::MouseInput()
{
}


MouseInput::~MouseInput()
{
}

void MouseInput::runSystem(std::vector<Entity*>& entityList, sf::Vector2i mousePosition)
{

	sf::Vector2f mPos = sf::Vector2f(mousePosition.x, mousePosition.y);
	//for (int i = 0; i < entityList.size(); i++)
	//{
	//	if (entityList.at(i)->componentKey[components::id::COMPONENT_MOUSEINPUT] == true)
	//	{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				Entity* click = new Entity;
				click->addComponent(new ComponentRender("texture1.bmp", sf::Vector2u(64, 64), sf::Vector2u(32, 32), mPos));
				click->addComponent(new ComponentCollision());
				entityList.push_back(click);
			}
	//	}
	//}
}