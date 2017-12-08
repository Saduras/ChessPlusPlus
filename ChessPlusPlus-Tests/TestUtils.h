#pragma once

#include "../ChessPlusPlus/Position.h"
#include <vector>

namespace TestUtils
{
	void AssertPositions(std::vector<Position> positions, std::vector<bool> exspectedPositions );
}