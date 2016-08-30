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
	sf::Vector2i mPos = sf::Vector2i(mousePosition.x, mousePosition.y);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		Entity* click = new Entity;
		click->addComponent(new ComponentRender("texture1.bmp", sf::Vector2u(64, 64), sf::Vector2u(64, 64), mPos));
		click->addComponent(new ComponentCollision());
		entityList.push_back(click);
	}
}