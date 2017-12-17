// ChessPlusPlus.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ChessPlusPlus.h"
#include "Match.h"
#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	//Match match{};
	//match.start();

	//system("pause");

	Texture t1;
	t1.loadFromFile("images/pieces.png");

	Sprite s{ t1 };

	RenderWindow window{ VideoMode{ 800, 800 }, "ChessPlusPlus" };
	window.setFramerateLimit(30);
	
	bool isMove = false;
	int dx = 0;
	int dy = 0;
	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			Vector2i pos = Mouse::getPosition(window);
			if (event.type == Event::Closed)
				window.close();

			// drag and drop
			if (event.key.code == Mouse::Left)
			{
				if (event.type == Event::MouseButtonPressed && s.getGlobalBounds().contains(pos.x, pos.y))
				{
					isMove = true;
					dx = pos.x - s.getPosition().x;
					dy = pos.y - s.getPosition().y;
				}

				if (event.type == Event::MouseButtonReleased)
					isMove = false;
			}

			if (isMove)
				s.setPosition(pos.x - dx, pos.y - dy);
		}

		// draw
		window.clear();
		window.draw(s);
		window.display();
	}

	return 0;
}

