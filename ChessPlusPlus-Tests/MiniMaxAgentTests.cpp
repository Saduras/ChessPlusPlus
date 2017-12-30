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
			Board *board = new Board{};
			board->clear();
			auto color = Color::WHITE;

			// Act
			board->placePieceAt(new Rook{ Color::WHITE }, Position{ 0,0 });
			int score1 = MiniMaxAgent::pieceValueEvalBoard(board, color);

			board->placePieceAt(new Knight{ Color::WHITE }, Position{ 1,0 });
			int score2 = MiniMaxAgent::pieceValueEvalBoard(board, color);

			board->placePieceAt(new Bishop{ Color::WHITE }, Position{ 2,0 });
			int score3 = MiniMaxAgent::pieceValueEvalBoard(board, color);

			board->placePieceAt(new Queen{ Color::WHITE }, Position{ 3,0 });
			int score4 = MiniMaxAgent::pieceValueEvalBoard(board, color);

			board->placePieceAt(new King{ Color::WHITE }, Position{ 4,0 });
			int score5 = MiniMaxAgent::pieceValueEvalBoard(board, color);

			board->placePieceAt(new King{ Color::BLACK }, Position{ 4,7 });
			int score6 = MiniMaxAgent::pieceValueEvalBoard(board, color);

			// Assert
			Assert::AreEqual(50, score1);
			Assert::AreEqual(50 + 30, score2);
			Assert::AreEqual(50 + 30 + 30, score3);
			Assert::AreEqual(50 + 30 + 30 + 90, score4);
			Assert::AreEqual(50 + 30 + 30 + 90 + 900, score5);
			Assert::AreEqual(50 + 30 + 30 + 90, score6);

			delete board;
		}

		TEST_METHOD(MiniMaxBlackEvalBoardTest)
		{
			// Arrange
			Board *board = new Board{};
			board->clear();
			auto color = Color::BLACK;

			// Act
			board->placePieceAt(new Rook{ Color::WHITE }, Position{ 0,0 });
			int score1 = MiniMaxAgent::pieceValueEvalBoard(board, color);

			board->placePieceAt(new Knight{ Color::WHITE }, Position{ 1,0 });
			int score2 = MiniMaxAgent::pieceValueEvalBoard(board, color);

			board->placePieceAt(new Bishop{ Color::WHITE }, Position{ 2,0 });
			int score3 = MiniMaxAgent::pieceValueEvalBoard(board, color);

			board->placePieceAt(new Queen{ Color::WHITE }, Position{ 3,0 });
			int score4 = MiniMaxAgent::pieceValueEvalBoard(board, color);

			board->placePieceAt(new King{ Color::WHITE }, Position{ 4,0 });
			int score5 = MiniMaxAgent::pieceValueEvalBoard(board, color);

			board->placePieceAt(new King{ Color::BLACK }, Position{ 4,7 });
			int score6 = MiniMaxAgent::pieceValueEvalBoard(board, color);

			// Assert
			Assert::AreEqual(-50, score1);
			Assert::AreEqual(-50 - 30, score2);
			Assert::AreEqual(-50 - 30 - 30, score3);
			Assert::AreEqual(-50 - 30 - 30 - 90, score4);
			Assert::AreEqual(-50 - 30 - 30 - 90 - 900, score5);
			Assert::AreEqual(-50 - 30 - 30 - 90, score6);

			delete board;
		}

		TEST_METHOD(MiniMaxSearchTest)
		{
			// Arrange
			auto *agent = new MiniMaxAgent{ 99, MiniMaxAgent::pieceValueEvalBoard };
			Game game{ agent, new MiniMaxAgent{ 99, MiniMaxAgent::pieceValueEvalBoard } };
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