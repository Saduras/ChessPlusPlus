#include "stdafx.h"
#include "Match.h"
#include "ChessConsoleView.h"
#include "Piece.h"
#include <iostream>
#include <string>

void Match::start()
{
	if (state != MatchState::UNSTARTED)
	{
		return;
	}

	state = MatchState::ONGOING;
	Board board{};
	board.setupWithDefault();
	ChessConsoleView view{ board };

	Color currentPlayerColor = Color::WHITE;

	while (state == MatchState::ONGOING)
	{
		view.print();

		Position positions[2]{ Position{0, 0}, Position{0, 0} };
		bool success = false;
		do
		{
			if (currentPlayerColor == Color::WHITE)
				std::cout << "WHITEs turn:";
			else
				std::cout << "BLACKs turn:";

			std::string input;
			std::getline(std::cin, input);
			success = parseInput(input, positions);

		} while (!success || !board.isValidMove(positions[0], positions[1], currentPlayerColor));

		board.movePiece(positions[0], positions[1]);
		currentPlayerColor = (currentPlayerColor == Color::WHITE) ? Color::BLACK : Color::WHITE;
	}
}

bool Match::parseInput(const std::string input, Position* positions)
{
	if (input.length() < 5)
		return false;

	positions[0] = { input[0] - 'a', input[1] - '1' };
	positions[1] = { input[3] - 'a', input[4] - '1' };
	
	return Position::isOnBoard( positions[0] ) && Position::isOnBoard( positions[1] );
}