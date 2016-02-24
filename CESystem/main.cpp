#include <SFML/Graphics.hpp>
#include <iostream>

#include "EntityPlayer.h"
#include "RenderSystem.h"



int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	RenderSystem renderSystem(window);
	renderSystem.entityList.push_back(new EntityPlayer);

	/*
	The Loop
	*/
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		renderSystem.RunSystem();
		//window.draw(shape);
		window.display();
	}

	return 0;
}