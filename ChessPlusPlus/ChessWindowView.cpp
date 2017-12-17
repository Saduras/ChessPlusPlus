#include "stdafx.h"
#include "ChessWindowView.h"
#include <map>

using namespace sf;

const int pieceSize = 100;

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

ChessWindowView::ChessWindowView(Game *game)
{
	this->game = game; 
}

ChessWindowView::~ChessWindowView()
{
}

void ChessWindowView::loadSprites()
{
	pieceTexture.loadFromFile("images/pieces.png");
	boardTexture.loadFromFile("images/board.png");

	boardSprite = Sprite{ boardTexture };

	Board board = game->getBoard();

	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			Piece *piece = board.getPieceAt(Position{ x, y });
			if (piece)
			{
				Sprite s{ pieceTexture };
				s.setTextureRect(spriteMap[piece->toShortString()]);
				s.setPosition(x * pieceSize, 700 - y * pieceSize);
				pieceSprites.push_back(s);
			}
		}
	}
}

void ChessWindowView::handleEvent(Event event)
{
	Vector2i pos = Mouse::getPosition(window);
	if (event.type == Event::Closed)
		window.close();

	// drag and drop
	if (event.key.code == Mouse::Left)
	{
		if (event.type == Event::MouseButtonPressed)
			for (int i = 0; i < pieceSprites.size(); i++)
			{
				if (pieceSprites[i].getGlobalBounds().contains(pos.x, pos.y))
				{
					dragSprite = &pieceSprites[i];
					dx = pos.x - dragSprite->getPosition().x;
					dy = pos.y - dragSprite->getPosition().y;
				}
			}

		if (event.type == Event::MouseButtonReleased)
		{
			Vector2f pos = dragSprite->getPosition() + Vector2f(pieceSize / 2, pieceSize / 2);
			dragSprite->setPosition(pieceSize * static_cast<int>(pos.x / pieceSize), pieceSize * static_cast<int>(pos.y / pieceSize));
			dragSprite = nullptr;
		}
	}

	if (dragSprite)
		dragSprite->setPosition(pos.x - dx, pos.y - dy);
}

void ChessWindowView::run()
{
	loadSprites();
	window.setFramerateLimit(30);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			handleEvent(event);
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

}
