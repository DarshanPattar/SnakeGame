#pragma once

#include "Graphics.h"
#include "Location.h"

class Board {

public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c);

	inline int GetGridHeight() const { return height; }
	inline int GetGridWidth() const { return width; }

	bool IsInsideBoard(const Location& loc) const;

	void DrawBorder();

private:
	static constexpr Color BorderColor = {200, 60, 60};

	static constexpr int dimention = 20;
	static constexpr int width = 32;
	static constexpr int height = 24;


	static constexpr int borderWidth = 4;
	static constexpr int borderPadding = 2;

	static constexpr int x = 70;
	static constexpr int y = 50;

	Graphics& gfx;
};
