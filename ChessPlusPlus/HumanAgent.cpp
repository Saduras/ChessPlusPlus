#include "stdafx.h"
#include "HumanAgent.h"

HumanAgent::~HumanAgent()
{
	promise.set_value(Move{});
}

std::future<Move> HumanAgent::nextTurn()
{
	// wait for move to be selected
	promise = std::promise<Move>();
	return promise.get_future();;
}