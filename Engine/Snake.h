#pragma once

#include "Board.h"

class Snake {
private:
	class Segment {
	public:
		void InitHead(const Location& loc);
		void InitBody(Color c_n);
		void Follow(const Segment& next);
		void Draw(Board& brd) const;
		void MoveBy(const Location& delta_loc);
		Location GetLocation() const;
	private:
		Location loc;
		Color c;
	};
public:
	Snake(const Location& loc);
	void MoveBy(const Location& delta_loc);
	void Grow();
	void Draw(Board& brd) const;
	Location GetNextHeadLocation(const Location& delta_loc) const;

	//Custom
	bool BitItself(const Location& delta_loc) const;
	bool IsInTile(const Location& delta_loc) const;

private:
	static constexpr Color HeadColor = Colors::Yellow;

	static constexpr int nSegmentsMax = 100;
	int nSegments = 1;
	Segment segments[nSegmentsMax];
};
