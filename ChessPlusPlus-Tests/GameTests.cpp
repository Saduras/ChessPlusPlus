#include "stdafx.h"
#include "CppUnitTest.h"
#include "Game.h"
#include "HumanAgent.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ChessPlusPlusTests
{
	TEST_CLASS(GameTests)
	{
	public:

		TEST_METHOD(GameStartTest)
		{
			// Arrange
			Game game{ new HumanAgent(), new HumanAgent() };
			GameState initalState = game.getState();

			// Act
			game.start();

			// Assert
			Assert::AreEqual(static_cast<int>(initalState), static_cast<int>(GameState::UNSTARTED), L"Invalid inital state!");
			Assert::AreEqual(static_cast<int>(game.getState()), static_cast<int>(GameState::ONGOING), L"Invalid state after start!");
			Assert::IsFalse(game.isCheck(Color::WHITE), L"White is check from the start!");
			Assert::IsFalse(game.isCheckmate(Color::WHITE), L"White is checkmate from the start!");
			Assert::IsFalse(game.isCheck(Color::BLACK), L"Black is check from the start!");
			Assert::IsFalse(game.isCheckmate(Color::BLACK), L"Black is checkmate from the start!");
		}

		TEST_METHOD(GameCheckTest)
		{
			// Arrange
			Game game{ new HumanAgent(), new HumanAgent() };
			game.start();

			// Act
			Board *board = game.getBoard();
			board->clear();
			board->placePieceAt(new King(Color::WHITE), Position{ 4,4 });
			board->placePieceAt(new King(Color::BLACK), Position{ 3,4 });

			// Assert
			Assert::IsTrue(game.isCheck(Color::WHITE), L"Exspected white to be check.");
			Assert::IsTrue(game.isCheck(Color::BLACK), L"Exspected black to be check.");
		}

		TEST_METHOD(GameFalseCheckmateTest)
		{
			// Arrange
			Game game{ new HumanAgent(), new HumanAgent() };
			game.start();

			// Act
			Board *board = game.getBoard();
			board->clear();
			board->placePieceAt(new King(Color::WHITE), Position{ 0,0 });
			board->placePieceAt(new Queen(Color::BLACK), Position{ 1,1 });

			// Assert
			Assert::IsFalse(game.isCheckmate(Color::WHITE), L"Exspected white to NOT be checkmate.");
		}

		TEST_METHOD(GameFalseCheckmateNoKingMoveTest)
		{
			// Arrange
			Game game{ new HumanAgent(), new HumanAgent() };
			game.start();

			// Act
			Board *board = game.getBoard();
			board->clear();
			board->placePieceAt(new King(Color::WHITE), Position{ 0,0 });
			board->placePieceAt(new Rook(Color::WHITE), Position{ 0,1 });
			board->placePieceAt(new Rook(Color::WHITE), Position{ 1,0 });
			board->placePieceAt(new Queen(Color::BLACK), Position{ 3,3 });

			// Assert
			Assert::IsFalse(game.isCheckmate(Color::WHITE), L"Exspected white to NOT be checkmate.");
		}

		TEST_METHOD(GameCheckmateCornerTest)
		{
			// Arrange
			Game game{ new HumanAgent(), new HumanAgent() };
			game.start();

			// Act
			Board *board = game.getBoard();
			board->clear();
			board->placePieceAt(new King(Color::WHITE), Position{ 0,0 });
			board->placePieceAt(new Rook(Color::BLACK), Position{ 1,4 });
			board->placePieceAt(new Queen(Color::BLACK), Position{ 1,1 });

			// Assert
			Assert::IsTrue(game.isCheckmate(Color::WHITE), L"Exspected white to be checkmate.");
		}

		TEST_METHOD(GameCheckmateSurroundedTest)
		{
			// Arrange
			Game game{ new HumanAgent(), new HumanAgent() };
			game.start();

			// Act
			Board *board = game.getBoard();
			board->clear();
			board->placePieceAt(new King(Color::WHITE), Position{ 4,4 });
			board->placePieceAt(new Rook(Color::BLACK), Position{ 3,4 });
			board->placePieceAt(new Queen(Color::BLACK), Position{ 5,4 });

			// Assert
			Assert::IsTrue(game.isCheckmate(Color::WHITE), L"Exspected white to be checkmate.");
		}

		TEST_METHOD(GameMoveIntoCheckTest)
		{
			// Arrange
			Game game{ new HumanAgent(), new HumanAgent() };
			game.start();
			Board *board = game.getBoard();
			board->clear();

			board->placePieceAt(new King{ Color::WHITE }, Position{ 3,3 });
			board->placePieceAt(new King{ Color::BLACK }, Position{ 3,4 });

			// Act
			bool move1 = game.isValidMove(Move{ Position{ 3,3 }, Position{ 3,4 } }, Color::WHITE, board);
			bool move2 = game.isValidMove(Move{ Position{ 3,3 }, Position{ 4,4 } }, Color::WHITE, board);
			bool move3 = game.isValidMove(Move{ Position{ 3,3 }, Position{ 4,3 } }, Color::WHITE, board);
			bool move4 = game.isValidMove(Move{ Position{ 3,3 }, Position{ 4,2 } }, Color::WHITE, board);

			// Assert

			// Attack other king
			Assert::IsTrue(move1, L"Move1 validation failed");
			// Move into  check
			Assert::IsFalse(move2, L"Move2 validation failed");
			Assert::IsFalse(move3, L"Move3 validation failed");
			// Move away
			Assert::IsTrue(move4, L"Move4 validation failed");
		}

		TEST_METHOD(GameCheckmateTest)
		{
			// Arrange
			Game game{ new HumanAgent(), new HumanAgent() };
			game.start();
			Board *board = game.getBoard();
			board->clear();

			board->placePieceAt(new King{ Color::WHITE }, Position{ 3,3 });
			board->placePieceAt(new Queen{ Color::BLACK }, Position{ 4,3 });
			board->placePieceAt(new Rook{ Color::BLACK }, Position{ 2,3 });

			// Act
			bool move1 = game.isValidMove(Move{ Position{ 3,3 }, Position{ 4,3 } }, Color::WHITE, board );
			bool move2 = game.isValidMove(Move{ Position{ 3,3 }, Position{ 2,3 } }, Color::WHITE, board );
			bool move3 = game.isValidMove(Move{ Position{ 3,3 }, Position{ 4,2 } }, Color::WHITE, board );
			bool move4 = game.isValidMove(Move{ Position{ 3,3 }, Position{ 3,2 } }, Color::WHITE, board );
			bool move5 = game.isValidMove(Move{ Position{ 3,3 }, Position{ 2,2 } }, Color::WHITE, board );
			bool move6 = game.isValidMove(Move{ Position{ 3,3 }, Position{ 2,4 } }, Color::WHITE, board );
			bool move7 = game.isValidMove(Move{ Position{ 3,3 }, Position{ 3,4 } }, Color::WHITE, board );
			bool move8 = game.isValidMove(Move{ Position{ 3,3 }, Position{ 4,4 } }, Color::WHITE, board );
																								
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