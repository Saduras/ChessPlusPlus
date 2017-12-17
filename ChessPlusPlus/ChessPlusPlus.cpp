// ChessPlusPlus.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ChessPlusPlus.h"
#include "Match.h"
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>

using namespace sf;

int main()
{
	//Match match{};
	//match.start();

	//system("pause");

	Texture pieceTexture{};
	Texture boardTexture{};
	pieceTexture.loadFromFile("images/pieces.png");
	boardTexture.loadFromFile("images/board.png");

	std::map<std::string, IntRect> spriteMap{
		{ "K", IntRect{ 0  ,0,   100,100 } },
		{ "k", IntRect{ 0  ,100, 100,100 } },
		{ "Q", IntRect{ 100,0,   100,100 } },
		{ "q", IntRect{ 100,100, 100,100 } },
		{ "B", IntRect{ 200,0,   100,100 } },
		{ "b", IntRect{ 200,100, 100,100 } },
		{ "N", IntRect{ 300,0,   100,100 } },
		{ "n", IntRect{ 300,100, 100,100 } },
		{ "R", IntRect{ 400,0,   100,100 } },
		{ "r", IntRect{ 400,100, 100,100 } },
		{ "P", IntRect{ 500,0,   100,100 } },
		{ "p", IntRect{ 500,100, 100,100 } }
	};

	Sprite boardSprite{ boardTexture };
	std::vector<Sprite> pieceSprites{};

	Board board{};
	board.setupWithDefault();

	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			Piece *piece = board.getPieceAt(Position{ x, y });
			if (piece)
			{
				Sprite s{ pieceTexture };
				s.setTextureRect(spriteMap[piece->toShortString()]);
				s.setPosition(x * 100, 700 - y * 100);
				pieceSprites.push_back(s);
			}
		}
	}

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
			/*if (event.key.code == Mouse::Left)
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
				s.setPosition(pos.x - dx, pos.y - dy);*/
		}

		// draw
		window.clear();
		window.draw(boardSprite);
		for (Sprite s : pieceSprites)
		{
			window.draw(s);
		}
		window.display();
	}

	return 0;
}

