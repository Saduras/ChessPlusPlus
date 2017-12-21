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
		
		TEST_METHOD(BishopFreeBoardTest)
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

		TEST_METHOD(BishopCornerTest)
		{
			// Arrange
			Board board{};
			Bishop *piece = new Bishop{ Color::WHITE };
			Position pos{ 7,7 };
			board.placePieceAt(piece, pos);

			// Act
			auto validPositions = piece->getMovesFor(pos, board);

			// Assert
			TestUtils::AssertPositions(validPositions, {
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,1,0,
				0,0,0,0,0,1,0,0,
				0,0,0,0,1,0,0,0,
				0,0,0,1,0,0,0,0,
				0,0,1,0,0,0,0,0,
				0,1,0,0,0,0,0,0,
				1,0,0,0,0,0,0,0,
			});
		}

		TEST_METHOD(BishopAttackTest)
		{
			// Arrange
			Board board{};
			Bishop *whitePiece = new Bishop{ Color::WHITE };
			Position whitePos{ 3,3 };
			Bishop *blackPiece = new Bishop{ Color::BLACK };
			Position blackPos{ 5,5 };
			board.placePieceAt(whitePiece, whitePos);
			board.placePieceAt(blackPiece, blackPos);

			// Act
			auto validPositions = whitePiece->getMovesFor(whitePos, board);

			// Assert
			TestUtils::AssertPositions(validPositions, {
				0,0,0,0,0,0,0,0,
				1,0,0,0,0,0,0,0,
				0,1,0,0,0,1,0,0,
				0,0,1,0,1,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,1,0,1,0,0,0,
				0,1,0,0,0,1,0,0,
				1,0,0,0,0,0,1,0,
			});
		}

		TEST_METHOD(BishopBlockTest)
		{
			// Arrange
			Board board{};
			Bishop *whitePiece = new Bishop{ Color::WHITE };
			Position whitePos{ 3,3 };
			Bishop *otherPiece = new Bishop{ Color::WHITE };
			Position otherPos{ 5,5 };
			board.placePieceAt(whitePiece, whitePos);
			board.placePieceAt(otherPiece, otherPos);

			// Act
			auto validPositions = whitePiece->getMovesFor(whitePos, board);

			// Assert
			TestUtils::AssertPositions(validPositions, {
				0,0,0,0,0,0,0,0,
				1,0,0,0,0,0,0,0,
				0,1,0,0,0,0,0,0,
				0,0,1,0,1,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,1,0,1,0,0,0,
				0,1,0,0,0,1,0,0,
				1,0,0,0,0,0,1,0,
			});
		}

		TEST_METHOD(BishopCoverTest)
		{
			// Arrange
			Board board{};
			Bishop *whitePiece = new Bishop{ Color::WHITE };
			Position whitePos{ 3,3 };
			Bishop *otherPiece = new Bishop{ Color::WHITE };
			Position otherPos{ 5,5 };
			board.placePieceAt(whitePiece, whitePos);
			board.placePieceAt(otherPiece, otherPos);

			// Act
			auto validPositions = whitePiece->getThreatedFieldsFor(whitePos, board);

			// Assert
			TestUtils::AssertPositions(validPositions, {
				0,0,0,0,0,0,0,0,
				1,0,0,0,0,0,0,0,
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