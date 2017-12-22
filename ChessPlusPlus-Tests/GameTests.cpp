#include "stdafx.h"
#include "CppUnitTest.h"
#include "Game.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ChessPlusPlusTests
{
	TEST_CLASS(GameTests)
	{
	public:

		TEST_METHOD(GameStartTest)
		{
			// Arrange
			Game game{};
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
			Game game{};
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

		TEST_METHOD(GameCheckmateFalseTest)
		{
			// Arrange
			Game game{};
			game.start();

			// Act
			Board *board = game.getBoard();
			board->clear();
			board->placePieceAt(new King(Color::WHITE), Position{ 0,0 });
			board->placePieceAt(new Queen(Color::BLACK), Position{ 1,1 });

			// Assert
			Assert::IsFalse(game.isCheckmate(Color::WHITE), L"Exspected white to NOT be checkmate.");
		}

		TEST_METHOD(GameCheckmateCornerTest)
		{
			// Arrange
			Game game{};
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
			Game game{};
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
	};
}