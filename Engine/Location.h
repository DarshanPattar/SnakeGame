#pragma once

struct Location {
	void Add(const Location& value) {
		x += value.x;
		y += value.y;
	}
	int x;
	int y;
};