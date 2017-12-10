#include "stdafx.h"
#include "CppUnitTest.h"
#include "Queen.h"
#include "Board.h"
#include "TestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ChessPlusPlusTests
{
	TEST_CLASS(QueenTests)
	{
	public:

		TEST_METHOD(QueenFreeBoardTest)
		{
			// Arrange
			Board board{};
			Queen *piece = new Queen{ Color::WHITE };
			Position pos{ 3,3 };
			board.placePieceAt(piece, pos);

			// Act
			auto validPositions = piece->getMovesFor(pos, board);

			// Assert
			TestUtils::AssertPositions(validPositions, {
				0,0,0,1,0,0,0,1,
				1,0,0,1,0,0,1,0,
				0,1,0,1,0,1,0,0,
				0,0,1,1,1,0,0,0,
				1,1,1,0,1,1,1,1,
				0,0,1,1,1,0,0,0,
				0,1,0,1,0,1,0,0,
				1,0,0,1,0,0,1,0,
			});
		}

		TEST_METHOD(QueenCornerTest)
		{
			// Arrange
			Board board{};
			Queen *piece = new Queen{ Color::WHITE };
			Position pos{ 7,7 };
			board.placePieceAt(piece, pos);

			// Act
			auto validPositions = piece->getMovesFor(pos, board);

			// Assert
			TestUtils::AssertPositions(validPositions, {
				1,1,1,1,1,1,1,0,
				0,0,0,0,0,0,1,1,
				0,0,0,0,0,1,0,1,
				0,0,0,0,1,0,0,1,
				0,0,0,1,0,0,0,1,
				0,0,1,0,0,0,0,1,
				0,1,0,0,0,0,0,1,
				1,0,0,0,0,0,0,1,
			});
		}

		TEST_METHOD(QueenAttackTest)
		{
			// Arrange
			Board board{};
			Queen *whitePiece = new Queen{ Color::WHITE };
			Position whitePos{ 3,3 };
			Queen *blackPiece = new Queen{ Color::BLACK };
			Position blackPos{ 4,4 };
			board.placePieceAt(whitePiece, whitePos);
			board.placePieceAt(blackPiece, blackPos);

			// Act
			auto validPositions = whitePiece->getMovesFor(whitePos, board);

			// Assert
			TestUtils::AssertPositions(validPositions, {
				0,0,0,1,0,0,0,0,
				1,0,0,1,0,0,0,0,
				0,1,0,1,0,0,0,0,
				0,0,1,1,1,0,0,0,
				1,1,1,0,1,1,1,1,
				0,0,1,1,1,0,0,0,
				0,1,0,1,0,1,0,0,
				1,0,0,1,0,0,1,0,
			});
		}

		TEST_METHOD(QueenBlockTest)
		{
			// Arrange
			Board board{};
			Queen *whitePiece = new Queen{ Color::WHITE };
			Position whitePos{ 3,3 };
			Queen *otherPiece = new Queen{ Color::WHITE };
			Position otherPos{ 4,4 };
			board.placePieceAt(whitePiece, whitePos);
			board.placePieceAt(otherPiece, otherPos);

			// Act
			auto validPositions = whitePiece->getMovesFor(whitePos, board);

			// Assert
			TestUtils::AssertPositions(validPositions, {
				0,0,0,1,0,0,0,0,
				1,0,0,1,0,0,0,0,
				0,1,0,1,0,0,0,0,
				0,0,1,1,0,0,0,0,
				1,1,1,0,1,1,1,1,
				0,0,1,1,1,0,0,0,
				0,1,0,1,0,1,0,0,
				1,0,0,1,0,0,1,0,
			});
		}
	};
}