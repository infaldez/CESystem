#include "MouseInput.h"
#include "EntityNonPlayer.h"

#include <iostream>

MouseInput::MouseInput()
{
	this->time = 0;
}


MouseInput::~MouseInput()
{
}


void MouseInput::runSystem(std::vector<Entity*>& entityList, sf::Vector2i mousePosition, double time)
{
	sf::Vector2f mPos = sf::Vector2f(mousePosition.x, mousePosition.y);
	
	if (time - this->time >= 100)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			Entity* click = new Entity;
			click->addComponent(new ComponentRender("texture1.bmp", sf::Vector2u(64, 64), sf::Vector2u(64, 64), mPos));
			click->addComponent(new ComponentCollision());
			entityList.push_back(click);		
			this->time = time;
		}
	}
}