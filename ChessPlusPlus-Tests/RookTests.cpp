#include "stdafx.h"
#include "CppUnitTest.h"
#include "Rook.h"
#include "Board.h"
#include "TestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ChessPlusPlusTests
{
	TEST_CLASS(RookTests)
	{
	public:

		TEST_METHOD(RookFreeBoardTest)
		{
			// Arrange
			Board board{};
			Rook *piece = new Rook{ Color::WHITE };
			Position pos{ 3,3 };
			board.placePieceAt(piece, pos);

			// Act
			auto validPositions = piece->getMovesFor(pos, board);

			// Assert
			TestUtils::AssertPositions(validPositions, {
				0,0,0,1,0,0,0,0,
				0,0,0,1,0,0,0,0,
				0,0,0,1,0,0,0,0,
				0,0,0,1,0,0,0,0,
				1,1,1,0,1,1,1,1,
				0,0,0,1,0,0,0,0,
				0,0,0,1,0,0,0,0,
				0,0,0,1,0,0,0,0,
			});
		}

		TEST_METHOD(RookCornerTest)
		{
			// Arrange
			Board board{};
			Rook *piece = new Rook{ Color::WHITE };
			Position pos{ 7,7 };
			board.placePieceAt(piece, pos);

			// Act
			auto validPositions = piece->getMovesFor(pos, board);

			// Assert
			TestUtils::AssertPositions(validPositions, {
				1,1,1,1,1,1,1,0,
				0,0,0,0,0,0,0,1,
				0,0,0,0,0,0,0,1,
				0,0,0,0,0,0,0,1,
				0,0,0,0,0,0,0,1,
				0,0,0,0,0,0,0,1,
				0,0,0,0,0,0,0,1,
				0,0,0,0,0,0,0,1,
			});
		}

		TEST_METHOD(RookAttackTest)
		{
			// Arrange
			Board board{};
			Rook *whitePiece = new Rook{ Color::WHITE };
			Position whitePos{ 3,3 };
			Rook *blackPiece = new Rook{ Color::BLACK };
			Position blackPos{ 3,5 };
			board.placePieceAt(whitePiece, whitePos);
			board.placePieceAt(blackPiece, blackPos);

			// Act
			auto validPositions = whitePiece->getMovesFor(whitePos, board);

			// Assert
			TestUtils::AssertPositions(validPositions, {
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,1,0,0,0,0,
				0,0,0,1,0,0,0,0,
				1,1,1,0,1,1,1,1,
				0,0,0,1,0,0,0,0,
				0,0,0,1,0,0,0,0,
				0,0,0,1,0,0,0,0,
			});
		}

		TEST_METHOD(RookBlockTest)
		{
			// Arrange
			Board board{};
			Rook *whitePiece = new Rook{ Color::WHITE };
			Position whitePos{ 3,3 };
			Rook *otherPiece = new Rook{ Color::WHITE };
			Position otherPos{ 3,5 };
			board.placePieceAt(whitePiece, whitePos);
			board.placePieceAt(otherPiece, otherPos);

			// Act
			auto validPositions = whitePiece->getMovesFor(whitePos, board);

			// Assert
			TestUtils::AssertPositions(validPositions, {
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,1,0,0,0,0,
				1,1,1,0,1,1,1,1,
				0,0,0,1,0,0,0,0,
				0,0,0,1,0,0,0,0,
				0,0,0,1,0,0,0,0,
			});
		}

		TEST_METHOD(RookCoverTest)
		{
			// Arrange
			Board board{};
			Rook *whitePiece = new Rook{ Color::WHITE };
			Position whitePos{ 3,3 };
			Rook *otherPiece = new Rook{ Color::WHITE };
			Position otherPos{ 3,5 };
			board.placePieceAt(whitePiece, whitePos);
			board.placePieceAt(otherPiece, otherPos);

			// Act
			auto validPositions = whitePiece->getThreatedFieldsFor(whitePos, board);

			// Assert
			TestUtils::AssertPositions(validPositions, {
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,1,0,0,0,0,
				0,0,0,1,0,0,0,0,
				1,1,1,0,1,1,1,1,
				0,0,0,1,0,0,0,0,
				0,0,0,1,0,0,0,0,
				0,0,0,1,0,0,0,0,
			});
		}
	};
}