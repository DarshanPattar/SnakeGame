#include "Snake.h"
#include <assert.h>

Snake::Snake(const Location& loc)
{
	constexpr int nBodyColors = 4;
	constexpr Color pattern[nBodyColors] = { {50, 168, 82}, {35, 125, 59}, {25, 97, 44}, {35, 125, 59} };

	for (int i = 0; i < nSegmentsMax; i++) {
		segments[i].InitBody(pattern[i % nBodyColors]);
	}

	segments[0].InitHead(loc);
}

void Snake::MoveBy(const Location& delta_loc)
{
	for (int i = nSegments - 1; i > 0; i--) {
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(delta_loc);
}

void Snake::Grow()
{
	if (nSegments < nSegmentsMax) {
		nSegments++;
	}
}

void Snake::Draw(Board& brd) const
{
	for (int i = 0; i < nSegments; i++) {
		segments[i].Draw(brd);
	}
}

Location Snake::GetNextHeadLocation(const Location& delta_loc) const
{
	Location l(segments[0].GetLocation());
	l.Add(delta_loc);
	return l;
}

//Custom 
bool Snake::BitItself(const Location& delta_loc) const
{
	for (int i = 1; i < nSegments - 1; i++) {
		if (segments[i].GetLocation().x  == GetNextHeadLocation(delta_loc).x 
			&& segments[i].GetLocation().y == GetNextHeadLocation(delta_loc).y)
			return true;
	}
	return false;
}

bool Snake::IsInTile(const Location& delta_loc) const
{
	for (int i = 1; i < nSegments; i++) {
		if (segments[i].GetLocation().x == GetNextHeadLocation(delta_loc).x
			&& segments[i].GetLocation().y == GetNextHeadLocation(delta_loc).y)
			return true;
	}
	return false;
}

void Snake::Segment::InitHead(const Location& in_loc)
{
	loc = in_loc;
	c = Snake::HeadColor;
}

void Snake::Segment::InitBody(Color c_n)
{
	c = c_n;
}

void Snake::Segment::Follow(const Segment& next)
{
	loc = next.loc;
}

void Snake::Segment::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

void Snake::Segment::MoveBy(const Location& delta_loc)
{
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	loc.Add(delta_loc);
}

Location Snake::Segment::GetLocation() const
{
	return loc;
}
