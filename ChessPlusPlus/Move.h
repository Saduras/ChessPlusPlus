#pragma once

#include "Position.h"

struct Move
{
	Position from;
	Position to;
};

inline bool operator==(const Move& lhs, const Move& rhs) { return lhs.from == rhs.from && lhs.to == rhs.to; }
inline bool operator!=(const Move& lhs, const Move& rhs) { return !(lhs == rhs); }

namespace std
{
	template <>
	struct hash<Move>
	{
		size_t operator()(Move const & move) const noexcept
		{
			return (
				(51 + std::hash<Position>()(move.from)) * 51
				+ std::hash<Position>()(move.to)
				);
		}
	};
}