#include "stdafx.h"
#include "Match.h"
#include "Board.h"
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
	ChessConsoleView view{ board };

	Color whosTurn = Color::WHITE;

	while (state == MatchState::ONGOING)
	{
		view.print();

		int positions[4]{ 0, 0, 0, 0 };
		bool success = false;
		do
		{
			if (whosTurn == Color::WHITE)
				std::cout << "WHITEs turn:";
			else
				std::cout << "BLACKs turn:";

			std::string input;
			std::getline(std::cin, input);
			success = parseInput(input, positions);

		} while (!success);

		// positons stores start (x,y) in 0,1 and end (x,y) in 2,3
		board.movePiece(positions[0], positions[1], positions[2], positions[3]);
		whosTurn = whosTurn == Color::WHITE ? Color::BLACK : Color::WHITE;
	}
}

bool Match::parseInput(const std::string input, int* positions)
{
	if (input.length() < 5)
		return false;

	positions[0] = input[0] - 'a';
	positions[1] = input[1] - '1';
	positions[2] = input[3] - 'a';
	positions[3] = input[4] - '1';

	for (int i = 0; i < 4; i++)
	{
		if (positions[i] < 0 || positions[i] > 7)
		{
			return false;
		}
	}
	
	return true;
}