#pragma once

#include "Snake.h"
#include "Board.h"
#include <random>

class Food {
private:
	Location loc;
	static constexpr Color c = Colors::Red;
public:
	Food(std::mt19937& rng, const Board& brd, const Snake& snake);

	void Respawn(std::mt19937& rng, const Board& brd, const Snake& snake);
	void Draw(Board& brd) const;
	inline const Location& GetLocation() const {
		return loc;
	}

};
