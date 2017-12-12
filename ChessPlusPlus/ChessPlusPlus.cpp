// ChessPlusPlus.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ChessPlusPlus.h"
#include "Match.h"
#include <SFML/Graphics.hpp>

int main()
{
	//Match match{};
	//match.start();

	//system("pause");

	sf::Texture t1;
	t1.loadFromFile("images/board.png");

	sf::Sprite s{ t1 };

	sf::RenderWindow window{ sf::VideoMode{ 800, 800 }, "ChessPlusPlus" };
	window.setFramerateLimit(30);
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(s);
		window.display();
	}

	return 0;
}

