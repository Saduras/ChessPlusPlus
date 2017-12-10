#include "stdafx.h"
#include "CppUnitTest.h"
#include "Pawn.h"
#include "Board.h"
#include "TestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ChessPlusPlusTests
{
	TEST_CLASS(PawnTests)
	{
	public:

		TEST_METHOD(PawnWhiteFreeBoardTest)
		{
			// Arrange
			Board board{};
			Pawn *piece = new Pawn{ Color::WHITE };
			Position pos{ 3,3 };
			board.placePieceAt(piece, pos);

			// Act
			auto validPositions = piece->getMovesFor(pos, board);

			// Assert
			TestUtils::AssertPositions(validPositions, {
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,1,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
			});
		}

		TEST_METHOD(PawnBlackFreeBoardTest)
		{
			// Arrange
			Board board{};
			Pawn *piece = new Pawn{ Color::BLACK };
			Position pos{ 3,3 };
			board.placePieceAt(piece, pos);

			// Act
			auto validPositions = piece->getMovesFor(pos, board);

			// Assert
			TestUtils::AssertPositions(validPositions, {
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,1,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
			});
		}

		TEST_METHOD(PawnWhiteStartPosTest)
		{
			// Arrange
			Board board{};
			Pawn *piece = new Pawn{ Color::WHITE };
			Position pos{ 3,1 };
			board.placePieceAt(piece, pos);

			// Act
			auto validPositions = piece->getMovesFor(pos, board);

			// Assert
			TestUtils::AssertPositions(validPositions, {
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,1,0,0,0,0,
				0,0,0,1,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
			});
		}

		TEST_METHOD(PawnBlackStartPosTest)
		{
			// Arrange
			Board board{};
			Pawn *piece = new Pawn{ Color::BLACK };
			Position pos{ 3,6 };
			board.placePieceAt(piece, pos);

			// Act
			auto validPositions = piece->getMovesFor(pos, board);

			// Assert
			TestUtils::AssertPositions(validPositions, {
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,1,0,0,0,0,
				0,0,0,1,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
			});
		}

		TEST_METHOD(PawnWhiteCornerTest)
		{
			// Arrange
			Board board{};
			Pawn *piece = new Pawn{ Color::WHITE };
			Position pos{ 7,7 };
			board.placePieceAt(piece, pos);

			// Act
			auto validPositions = piece->getMovesFor(pos, board);

			// Assert
			TestUtils::AssertPositions(validPositions, {
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
			});
		}

		TEST_METHOD(PawnBlackCornerTest)
		{
			// Arrange
			Board board{};
			Pawn *piece = new Pawn{ Color::BLACK };
			Position pos{ 7,0 };
			board.placePieceAt(piece, pos);

			// Act
			auto validPositions = piece->getMovesFor(pos, board);

			// Assert
			TestUtils::AssertPositions(validPositions, {
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
			});
		}

		TEST_METHOD(PawnWhiteAttackTest)
		{
			// Arrange
			Board board{};
			Pawn *whitePiece = new Pawn{ Color::WHITE };
			Position whitePos{ 3,3 };
			Pawn *blackPiece = new Pawn{ Color::BLACK };
			Position blackPos{ 2,4 };
			Pawn *blackPiece2 = new Pawn{ Color::BLACK };
			Position blackPos2{ 4,4 };
			board.placePieceAt(whitePiece, whitePos);
			board.placePieceAt(blackPiece, blackPos);
			board.placePieceAt(blackPiece2, blackPos2);

			// Act
			auto validPositions = whitePiece->getMovesFor(whitePos, board);

			// Assert
			TestUtils::AssertPositions(validPositions, {
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,1,1,1,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
			});
		}

		TEST_METHOD(PawnBlackAttackTest)
		{
			// Arrange
			Board board{};
			Pawn *blackPiece = new Pawn{ Color::BLACK };
			Position blackPos{ 3,5 };
			Pawn *whitePiece = new Pawn{ Color::WHITE };
			Position whitePos{ 2,4 };
			Pawn *whitePiece2 = new Pawn{ Color::WHITE };
			Position whitePos2{ 4,4 };
			board.placePieceAt(blackPiece, blackPos);
			board.placePieceAt(whitePiece, whitePos);
			board.placePieceAt(whitePiece2, whitePos2);

			// Act
			auto validPositions = blackPiece->getMovesFor(blackPos, board);

			// Assert
			TestUtils::AssertPositions(validPositions, {
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,1,1,1,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
			});
		}

		TEST_METHOD(PawnWhiteBlockTest)
		{
			// Arrange
			Board board{};
			Pawn *whitePiece = new Pawn{ Color::WHITE };
			Position whitePos{ 3,3 };
			Pawn *otherPiece = new Pawn{ Color::WHITE };
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
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
			});
		}

		TEST_METHOD(PawnBlackBlockTest)
		{
			// Arrange
			Board board{};
			Pawn *piece = new Pawn{ Color::BLACK };
			Position pos{ 3,4 };
			Pawn *otherPiece = new Pawn{ Color::BLACK };
			Position otherPos{ 3,3 };
			board.placePieceAt(piece, pos);
			board.placePieceAt(otherPiece, otherPos);

			// Act
			auto validPositions = piece->getMovesFor(pos, board);

			// Assert
			TestUtils::AssertPositions(validPositions, {
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,
			});
		}
	};
}