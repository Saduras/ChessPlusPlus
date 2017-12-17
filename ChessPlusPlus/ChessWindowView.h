#pragma once
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <vector>

class ChessWindowView
{
public:
	ChessWindowView(Game* game);
	~ChessWindowView();

	void run();

private:
	Game *game;

	sf::Texture pieceTexture{};
	sf::Texture boardTexture{};

	sf::Sprite boardSprite{};
	std::vector<sf::Sprite> pieceSprites{};
	sf::RenderWindow window{ sf::VideoMode{ 800, 800 }, "ChessPlusPlus" };
	sf::Sprite *dragSprite = nullptr;
	int dx = 0;
	int dy = 0;

	void loadSprites();
	void handleEvent(sf::Event event);
};

