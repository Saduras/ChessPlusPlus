#include "stdafx.h"
#include "ChessConsoleView.h"
#include <string>

ChessConsoleView::ChessConsoleView(Board &board)
{
	this->board = board;
}

void ChessConsoleView::print()
{
	std::string *output = new std::string{};
	output->reserve(2*8*8);

	for (int y = 7; y >= 0; y--)
	{
		*output += " " + std::to_string(y + 1) + "|";
		for (int x = 0; x < 8; x++)
		{
			Piece *piece = board.getPieceAt(Position{ x, y });

			if (piece)
			{
				*output += piece->toShortString();
			}
			else
			{
				// draw checker pattern on empty fields
				*output += ((x + y) % 2 == 1) ? " " : "*";
			}
		}
		*output += "\n";
	}
	*output += "   --------\n";
	*output += "   ";
	for (int x = 0; x < 8; x++)
	{
		*output += 'a' + x;
	}
	*output += "\n";

	std::cout << *output;

	delete output;
}