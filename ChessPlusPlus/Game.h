#pragma once

#include <functional>
#include <thread>
#include "Board.h"
#include "Piece.h"
#include "Agent.h"

class Agent;

enum class GameState
{
	UNSTARTED,
	ONGOING,
	CHECK_WHITE,
	CHECKMATE_WHITE,
	CHECK_BLACK,
	CHECKMATE_BLACK,
};

class Game
{
public:
	Game(Agent *whiteAgent, Agent *blackAgent);
	~Game();
	inline GameState getState() { return state; }
	inline Board* getBoard() { return &board; }

	inline void setCallbacks(std::function<void(Piece*)> onRemovePiece, std::function<void(Piece*, Position)> onMovePiece)
	{
		this->onRemovePiece = onRemovePiece;
		this->onMovePiece = onMovePiece;
	}
	void start();
	void restart();
	void stop();
	bool doMove(Move move);

	inline Agent* getCurrentAgent() { return (currentPlayer == Color::WHITE) ? whiteAgent : blackAgent; }

	bool isRunning();
	bool isValidMove(Move move);
	bool isCheck(Color playerColor);
	bool isCheckmate(Color playerColor);

private:
	std::thread thread;
	GameState state{ GameState::UNSTARTED };
	Board board{};
	Color currentPlayer;
	Agent* whiteAgent;
	Agent* blackAgent;

	std::function<void(Piece*)> onRemovePiece;
	std::function<void(Piece*, Position)> onMovePiece;

	bool isCheck_internal(Color currentPlayer, Board *board);
};