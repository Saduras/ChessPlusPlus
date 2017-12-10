#include "stdafx.h"
#include "CppUnitTest.h"
#include "Knight.h"
#include "Board.h"
#include "TestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ChessPlusPlusTests
{
	TEST_CLASS(KnightTests)
	{
	public:

		TEST_METHOD(KnightFreeBoardTest)
		{
			// Arrange
			Board board{};
			Knight *piece = new Knight{ Color::WHITE };
			Position pos{ 3,3 };
			board.placePieceAt(piece, pos);

			// Act
			auto validPositions = piece->getMovesFor(pos, board);

			// Assert
			TestUtils::AssertPositions(validPositions, {
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,1,0,1,0,0,0,
				0,1,0,0,0,1,0,0,
				0,0,0,0,0,0,0,0,
				0,1,0,0,0,1,0,0,
				0,0,1,0,1,0,0,0,
				0,0,0,0,0,0,0,0,
			});
		}

		TEST_METHOD(KnightCornerTest)
		{
			// Arrange
			Board board{};
			Knight *piece = new Knight{ Color::WHITE };
			Position pos{ 7,7 };
			board.placePieceAt(piece, pos);

			// Act
			auto validPositions = piece->getMovesFor(pos, board);

			// Assert
			TestUtils::AssertPositions(validPositions, {
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,1,0,0,
				0,0,0,0,0,0,1,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
			});
		}

		TEST_METHOD(KnightAttackTest)
		{
			// Arrange
			Board board{};
			Knight *whitePiece = new Knight{ Color::WHITE };
			Position whitePos{ 3,3 };
			Knight *blackPiece = new Knight{ Color::BLACK };
			Position blackPos{ 4,5 };
			board.placePieceAt(whitePiece, whitePos);
			board.placePieceAt(blackPiece, blackPos);

			// Act
			auto validPositions = whitePiece->getMovesFor(whitePos, board);

			// Assert
			TestUtils::AssertPositions(validPositions, {
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,1,0,1,0,0,0,
				0,1,0,0,0,1,0,0,
				0,0,0,0,0,0,0,0,
				0,1,0,0,0,1,0,0,
				0,0,1,0,1,0,0,0,
				0,0,0,0,0,0,0,0,
			});
		}

		TEST_METHOD(KnightBlockTest)
		{
			// Arrange
			Board board{};
			Knight *whitePiece = new Knight{ Color::WHITE };
			Position whitePos{ 3,3 };
			Knight *otherPiece = new Knight{ Color::WHITE };
			Position otherPos{ 4,5 };
			board.placePieceAt(whitePiece, whitePos);
			board.placePieceAt(otherPiece, otherPos);

			// Act
			auto validPositions = whitePiece->getMovesFor(whitePos, board);

			// Assert
			TestUtils::AssertPositions(validPositions, {
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,1,0,0,0,0,0,
				0,1,0,0,0,1,0,0,
				0,0,0,0,0,0,0,0,
				0,1,0,0,0,1,0,0,
				0,0,1,0,1,0,0,0,
				0,0,0,0,0,0,0,0,
			});
		}

		TEST_METHOD(KnightJumpTest)
		{
			// Arrange
			Board board{};
			Knight *whitePiece = new Knight{ Color::WHITE };
			Position whitePos{ 3,3 };
			board.placePieceAt(whitePiece, whitePos);
			board.placePieceAt(new Knight{ Color::WHITE }, Position{ 2,4 });
			board.placePieceAt(new Knight{ Color::WHITE }, Position{ 3,4 });
			board.placePieceAt(new Knight{ Color::WHITE }, Position{ 4,4 });
			board.placePieceAt(new Knight{ Color::WHITE }, Position{ 2,3 });
			board.placePieceAt(new Knight{ Color::WHITE }, Position{ 4,3 });
			board.placePieceAt(new Knight{ Color::WHITE }, Position{ 2,2 });
			board.placePieceAt(new Knight{ Color::WHITE }, Position{ 3,2 });
			board.placePieceAt(new Knight{ Color::WHITE }, Position{ 4,2 });

			// Act
			auto validPositions = whitePiece->getMovesFor(whitePos, board);

			// Assert
			TestUtils::AssertPositions(validPositions, {
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,1,0,1,0,0,0,
				0,1,0,0,0,1,0,0,
				0,0,0,0,0,0,0,0,
				0,1,0,0,0,1,0,0,
				0,0,1,0,1,0,0,0,
				0,0,0,0,0,0,0,0,
			});
		}
	};
}