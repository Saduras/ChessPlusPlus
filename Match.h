#pragma once

enum class MatchState
{
	UNSTARTED,
	ONGOING,
	WON_WHITE,
	WON_BLACK,
};

class Match
{
public:
	void start();
	inline MatchState getState() { return state; }

private:
	MatchState state{ MatchState::UNSTARTED };

	bool parseInput(const std::string input, int* positions);
};