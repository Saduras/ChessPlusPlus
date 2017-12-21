#include "stdafx.h"
#include "CppUnitTest.h"
#include "Board.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ChessPlusPlusTests
{
	TEST_CLASS(ThreatTests)
	{
	public:

		TEST_METHOD(ThreatNoneTest)
		{
			// Arrange
			Board board{};
			board.placePieceAt(new King{ Color::WHITE }, Position{ 3, 3 });

			// Act
			bool isCheck = board.isThreatenedBy(Position{ 3, 3 }, Color::BLACK);

			// Assert
			Assert::IsFalse(isCheck);
		}

		TEST_METHOD(ThreatDirectTest)
		{
			// Arrange
			Board board{};
			board.placePieceAt(new King{ Color::WHITE }, Position{ 3, 3 });
			board.placePieceAt(new Bishop{ Color::BLACK }, Position{ 1, 1 });

			// Act
			bool isCheck = board.isThreatenedBy(Position{ 3, 3 }, Color::BLACK);

			// Assert
			Assert::IsTrue(isCheck);
		}

		TEST_METHOD(ThreatCoverTest)
		{
			// Arrange
			Board board{};
			board.placePieceAt(new Bishop{ Color::BLACK }, Position{ 3, 3 });
			board.placePieceAt(new Bishop{ Color::BLACK }, Position{ 1, 1 });

			// Act
			bool isCheck = board.isThreatenedBy(Position{ 1, 1 }, Color::BLACK);

			// Assert
			Assert::IsTrue(isCheck);
		}
	};
}