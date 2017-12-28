#include "stdafx.h"
#include "Agent.h"

Agent::~Agent()
{
	promise.set_value(Move{});
}