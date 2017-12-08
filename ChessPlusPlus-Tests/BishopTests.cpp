#include "stdafx.h"
#include "CppUnitTest.h"
#include "Bishop.h"
#include "Board.h"
#include "TestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ChessPlusPlusTests
{
	TEST_CLASS(BishopTests)
	{
	public:
		
		TEST_METHOD(ValidMovesTest)
		{
			// Arrange
			Board board{};
			Bishop *piece = new Bishop{ Color::WHITE };
			Position pos{ 3,3 };
			board.placePieceAt(piece, pos);

			// Act
			auto validPositions = piece->getMovesFor(pos, board);

			// Assert
			TestUtils::AssertPositions(validPositions, {
				0,0,0,0,0,0,0,1,
				1,0,0,0,0,0,1,0,
				0,1,0,0,0,1,0,0,
				0,0,1,0,1,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,1,0,1,0,0,0,
				0,1,0,0,0,1,0,0,
				1,0,0,0,0,0,1,0,
			});
		}

	};
}