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

		TEST_METHOD(KingMoveIntoCheckTest)
		{
			// Arrange
			Board board{};
			board.placePieceAt(new King{ Color::WHITE }, Position{ 3,3 });
			board.placePieceAt(new King{ Color::BLACK }, Position{ 3,4 });

			// Act
			bool move1 = board.isValidMove(Position{ 3,3 }, Position{ 3,4 }, Color::WHITE);
			bool move2 = board.isValidMove(Position{ 3,3 }, Position{ 4,4 }, Color::WHITE);
			bool move3 = board.isValidMove(Position{ 3,3 }, Position{ 4,3 }, Color::WHITE);
			bool move4 = board.isValidMove(Position{ 3,3 }, Position{ 4,2 }, Color::WHITE);

			// Assert
			
			// Attack other king
			Assert::IsTrue(move1, L"Move1 validation failed");
			// Move into  check
			Assert::IsFalse(move2, L"Move2 validation failed");
			Assert::IsFalse(move3, L"Move3 validation failed");
			// Move away
			Assert::IsTrue(move4, L"Move4 validation failed");
		}

		TEST_METHOD(KingCheckmateTest)
		{
			// Arrange
			Board board{};
			board.placePieceAt(new King{ Color::WHITE }, Position{ 3,3 });
			board.placePieceAt(new Queen{ Color::BLACK }, Position{ 4,3 });
			board.placePieceAt(new Rook{ Color::BLACK }, Position{ 2,3 });

			// Act
			bool move1 = board.isValidMove(Position{ 3,3 }, Position{ 4,3 }, Color::WHITE);
			bool move2 = board.isValidMove(Position{ 3,3 }, Position{ 2,3 }, Color::WHITE);
			bool move3 = board.isValidMove(Position{ 3,3 }, Position{ 4,2 }, Color::WHITE);
			bool move4 = board.isValidMove(Position{ 3,3 }, Position{ 3,2 }, Color::WHITE);
			bool move5 = board.isValidMove(Position{ 3,3 }, Position{ 2,2 }, Color::WHITE);
			bool move6 = board.isValidMove(Position{ 3,3 }, Position{ 2,4 }, Color::WHITE);
			bool move7 = board.isValidMove(Position{ 3,3 }, Position{ 3,4 }, Color::WHITE);
			bool move8 = board.isValidMove(Position{ 3,3 }, Position{ 4,4 }, Color::WHITE);

			// Assert

			// Attack queen
			Assert::IsFalse(move1, L"Move1 validation failed");
			// Attack rook
			Assert::IsFalse(move2, L"Move2 validation failed");
			// Flee
			Assert::IsFalse(move3, L"Move3 validation failed");
			Assert::IsFalse(move4, L"Move4 validation failed");
			Assert::IsFalse(move5, L"Move5 validation failed");
			Assert::IsFalse(move6, L"Move6 validation failed");
			Assert::IsFalse(move7, L"Move7 validation failed");
			Assert::IsFalse(move8, L"Move8 validation failed");
		}
	};
}