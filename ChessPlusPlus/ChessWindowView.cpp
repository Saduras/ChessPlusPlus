#include "stdafx.h"
#include "ChessWindowView.h"
#include <map>
#include <functional>

using namespace sf;

const int pieceSize = 100;

static std::map<std::string, IntRect> spriteMap{
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
	delete dragSprite;
}

void ChessWindowView::loadTextures()
{
	pieceTexture.loadFromFile("images/pieces.png");
	boardTexture.loadFromFile("images/board.png");
}
void ChessWindowView::initSprites()
{
	boardSprite = Sprite{ boardTexture };

	Board *board = game->getBoard();

	pieceSprites.clear();
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			Piece *piece = board->getPieceAt(Position{ x, y });
			if (piece)
			{
				Sprite s{ pieceTexture };
				s.setTextureRect(spriteMap[piece->toShortString()]);
				s.setPosition(x * pieceSize, 700 - y * pieceSize);
				pieceSprites[piece] = s;
			}
		}
	}
}

void ChessWindowView::handleEvent(Event event)
{
	Vector2i mousePos = Mouse::getPosition(window);
	if (event.type == Event::Closed)
		window.close();

	if (game->getState() == GameState::CHECKMATE_WHITE || game->getState() == GameState::CHECKMATE_BLACK)
	{
		if (event.key.code == Keyboard::Return)
		{
			game->restart();
			initSprites();
		}
	}
	else
	{
		// drag and drop
		if (event.key.code == Mouse::Left)
		{
			if (event.type == Event::MouseButtonPressed)
				for (const auto& pair : pieceSprites)
				{
					auto sprite = pieceSprites[pair.first];
					if (sprite.getGlobalBounds().contains(mousePos.x, mousePos.y))
					{
						dragSprite = &pieceSprites[pair.first];
						dragStart = dragSprite->getPosition();
						dx = mousePos.x - dragStart.x;
						dy = mousePos.y - dragStart.y;
					}
				}

			if (event.type == Event::MouseButtonReleased)
			{
				const Vector2f pos = dragSprite->getPosition() + Vector2f(pieceSize / 2, pieceSize / 2);
				const Vector2f snapPos{ static_cast<float>(pieceSize * static_cast<int>(pos.x / pieceSize)),
					static_cast<float>(pieceSize * static_cast<int>(pos.y / pieceSize)) };

				const Position from{ static_cast<int>(dragStart.x / pieceSize),  static_cast<int>((700 - dragStart.y) / pieceSize) };
				const Position to{ static_cast<int>(snapPos.x / pieceSize),    static_cast<int>((700 - snapPos.y) / pieceSize) };
				std::cout << Position::toString(from) << " " << Position::toString(to) << std::endl;

				// Reset sprite positon. The actual moving happens in onMovePiece
				dragSprite->setPosition(dragStart);
				game->doMove(Move{ from, to });

				dragSprite = nullptr;
			}
		}

		if (dragSprite)
			dragSprite->setPosition(mousePos.x - dx, mousePos.y - dy);
	}
}

void ChessWindowView::run()
{
	auto rmvFnc = std::bind(&ChessWindowView::onRemovePiece, this, std::placeholders::_1);
	auto mvFnc = std::bind(&ChessWindowView::onMovePiece, this, std::placeholders::_1, std::placeholders::_2);
	game->setCallbacks(rmvFnc, mvFnc);

	loadTextures();
	initSprites();
	window.setFramerateLimit(30);

	while (window.isOpen())
	{
		if (game->getState() == GameState::CHECKMATE_WHITE)
			window.setTitle("Black wins!");
		if (game->getState() == GameState::CHECKMATE_BLACK)
			window.setTitle("White wins!");
		
		Event event;
		while (window.pollEvent(event))
		{
			handleEvent(event);
		}

		// draw
		window.clear();
		window.draw(boardSprite);
		for (const auto& pair : pieceSprites)
		{
			window.draw(pair.second);
		}
		window.display();
	}
}

void ChessWindowView::onRemovePiece(Piece *removedPiece)
{
	pieceSprites.erase(removedPiece);
}


void ChessWindowView::onMovePiece(Piece* movedPiece, Position newPos)
{
	pieceSprites[movedPiece].setPosition(newPos.x * pieceSize, 700 - newPos.y * pieceSize);
}