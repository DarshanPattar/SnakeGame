#include "Food.h"

Food::Food(std::mt19937& rng, const Board& brd, const Snake& snake)
{
	Respawn(rng, brd, snake);
}

void Food::Respawn(std::mt19937& rng, const Board& brd, const Snake& snake)
{
	std::uniform_int_distribution<int> Distx(0, brd.GetGridWidth() - 1);
	std::uniform_int_distribution<int> Disty(0, brd.GetGridHeight() - 1);

	Location newLoc;

	do {
		newLoc.x = Distx(rng);
		newLoc.y = Disty(rng);

	} while (snake.IsInTile(newLoc));

	loc = newLoc;

}

void Food::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}
