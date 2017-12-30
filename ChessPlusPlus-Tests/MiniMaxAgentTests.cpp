#include "stdafx.h"
#include "CppUnitTest.h"
#include "Board.h"
#include "MiniMaxAgent.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ChessPlusPlusTests
{
	TEST_CLASS(MiniMaxAgentTests)
	{
	public:

		TEST_METHOD(MiniMaxWhiteEvalBoardTest)
		{
			// Arrange
			auto *agent = new MiniMaxAgent{ 99 };
			Game game{ agent, new MiniMaxAgent{ 99 } };
			agent->setup(Color::WHITE, &game);
			auto board = game.getBoard();
			board->clear();

			// Act
			board->placePieceAt(new Rook{ Color::WHITE }, Position{ 0,0 });
			int score1 = agent->pieceValueEvalBoard(board);

			board->placePieceAt(new Knight{ Color::WHITE }, Position{ 1,0 });
			int score2 = agent->pieceValueEvalBoard(board);

			board->placePieceAt(new Bishop{ Color::WHITE }, Position{ 2,0 });
			int score3 = agent->pieceValueEvalBoard(board);

			board->placePieceAt(new Queen{ Color::WHITE }, Position{ 3,0 });
			int score4 = agent->pieceValueEvalBoard(board);

			board->placePieceAt(new King{ Color::WHITE }, Position{ 4,0 });
			int score5 = agent->pieceValueEvalBoard(board);

			board->placePieceAt(new King{ Color::BLACK }, Position{ 4,7 });
			int score6 = agent->pieceValueEvalBoard(board);

			// Assert
			Assert::AreEqual(50, score1);
			Assert::AreEqual(50 + 30, score2);
			Assert::AreEqual(50 + 30 + 30, score3);
			Assert::AreEqual(50 + 30 + 30 + 90, score4);
			Assert::AreEqual(50 + 30 + 30 + 90 + 900, score5);
			Assert::AreEqual(50 + 30 + 30 + 90, score6);
		}

		TEST_METHOD(MiniMaxBlackEvalBoardTest)
		{
			// Arrange
			auto *agent = new MiniMaxAgent{ 99 };
			Game game{ agent, new MiniMaxAgent{ 99 } };
			agent->setup(Color::BLACK, &game);
			auto board = game.getBoard();
			board->clear();

			// Act
			board->placePieceAt(new Rook{ Color::WHITE }, Position{ 0,0 });
			int score1 = agent->pieceValueEvalBoard(board);

			board->placePieceAt(new Knight{ Color::WHITE }, Position{ 1,0 });
			int score2 = agent->pieceValueEvalBoard(board);

			board->placePieceAt(new Bishop{ Color::WHITE }, Position{ 2,0 });
			int score3 = agent->pieceValueEvalBoard(board);

			board->placePieceAt(new Queen{ Color::WHITE }, Position{ 3,0 });
			int score4 = agent->pieceValueEvalBoard(board);

			board->placePieceAt(new King{ Color::WHITE }, Position{ 4,0 });
			int score5 = agent->pieceValueEvalBoard(board);

			board->placePieceAt(new King{ Color::BLACK }, Position{ 4,7 });
			int score6 = agent->pieceValueEvalBoard(board);

			// Assert
			Assert::AreEqual(-50, score1);
			Assert::AreEqual(-50 - 30, score2);
			Assert::AreEqual(-50 - 30 - 30, score3);
			Assert::AreEqual(-50 - 30 - 30 - 90, score4);
			Assert::AreEqual(-50 - 30 - 30 - 90 - 900, score5);
			Assert::AreEqual(-50 - 30 - 30 - 90, score6);
		}

		TEST_METHOD(MiniMaxSearchTest)
		{
			// Arrange
			auto *agent = new MiniMaxAgent{ 99 };
			Game game{ agent, new MiniMaxAgent{ 99 } };
			agent->setup(Color::WHITE, &game);
			auto board = game.getBoard();
			board->clear();
			board->placePieceAt(new Pawn(Color::WHITE), Position{ 1, 1 });
			board->placePieceAt(new Pawn(Color::BLACK), Position{ 0, 4 });

			// Act
			int score1 = agent->miniMaxSearch(0, Color::WHITE, true, board).score;
			int score2 = agent->miniMaxSearch(1, Color::WHITE, true, board).score;
			int score3 = agent->miniMaxSearch(2, Color::WHITE, true, board).score;
			int score4 = agent->miniMaxSearch(3, Color::WHITE, true, board).score;

			// Assert
			Assert::AreEqual(0, score1);
			Assert::AreEqual(0, score2);
			Assert::AreEqual(0, score3);
			Assert::AreEqual(10, score4);
		}
	};
}