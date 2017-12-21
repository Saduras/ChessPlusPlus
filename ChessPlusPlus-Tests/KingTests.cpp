#include "stdafx.h"
#include "CppUnitTest.h"
#include "King.h"
#include "Board.h"
#include "TestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ChessPlusPlusTests
{
	TEST_CLASS(KingTests)
	{
	public:

		TEST_METHOD(KingFreeBoardTest)
		{
			// Arrange
			Board board{};
			King *piece = new King{ Color::WHITE };
			Position pos{ 3,3 };
			board.placePieceAt(piece, pos);

			// Act
			auto validPositions = piece->getMovesFor(pos, board);

			// Assert
			TestUtils::AssertPositions(validPositions, {
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,1,1,1,0,0,0,
				0,0,1,0,1,0,0,0,
				0,0,1,1,1,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
			});
		}

		TEST_METHOD(KingCornerTest)
		{
			// Arrange
			Board board{};
			King *piece = new King{ Color::WHITE };
			Position pos{ 7,7 };
			board.placePieceAt(piece, pos);

			// Act
			auto validPositions = piece->getMovesFor(pos, board);

			// Assert
			TestUtils::AssertPositions(validPositions, {
				0,0,0,0,0,0,1,0,
				0,0,0,0,0,0,1,1,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
			});
		}

		TEST_METHOD(KingAttackTest)
		{
			// Arrange
			Board board{};
			King *whitePiece = new King{ Color::WHITE };
			Position whitePos{ 3,3 };
			King *blackPiece = new King{ Color::BLACK };
			Position blackPos{ 3,4 };
			board.placePieceAt(whitePiece, whitePos);
			board.placePieceAt(blackPiece, blackPos);

			// Act
			auto validPositions = whitePiece->getMovesFor(whitePos, board);

			// Assert
			TestUtils::AssertPositions(validPositions, {
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,1,1,1,0,0,0,
				0,0,1,0,1,0,0,0,
				0,0,1,1,1,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
			});
		}

		TEST_METHOD(KingBlockTest)
		{
			// Arrange
			Board board{};
			King *whitePiece = new King{ Color::WHITE };
			Position whitePos{ 3,3 };
			King *otherPiece = new King{ Color::WHITE };
			Position otherPos{ 3,4 };
			board.placePieceAt(whitePiece, whitePos);
			board.placePieceAt(otherPiece, otherPos);

			// Act
			auto validPositions = whitePiece->getMovesFor(whitePos, board);

			// Assert
			TestUtils::AssertPositions(validPositions, {
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,1,0,1,0,0,0,
				0,0,1,0,1,0,0,0,
				0,0,1,1,1,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
			});
		}

		TEST_METHOD(KingCoverTest)
		{
			// Arrange
			Board board{};
			King *whitePiece = new King{ Color::WHITE };
			Position whitePos{ 3,3 };
			King *otherPiece = new King{ Color::WHITE };
			Position otherPos{ 3,4 };
			board.placePieceAt(whitePiece, whitePos);
			board.placePieceAt(otherPiece, otherPos);

			// Act
			auto validPositions = whitePiece->getThreatedFieldsFor(whitePos, board);

			// Assert
			TestUtils::AssertPositions(validPositions, {
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,1,1,1,0,0,0,
				0,0,1,0,1,0,0,0,
				0,0,1,1,1,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
			});
		}
	};
}