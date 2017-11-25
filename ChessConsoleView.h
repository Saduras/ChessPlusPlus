#pragma once

#include "stdafx.h"
#include "Board.h"

class ChessConsoleView
{
public:
	explicit ChessConsoleView(Board &board);

	void print();

private:
	Board board;
};