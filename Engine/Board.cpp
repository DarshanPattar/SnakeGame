#include "Board.h"
#include <assert.h>

Board::Board(Graphics& gfx):gfx(gfx)
{

}

void Board::DrawCell(const Location& loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);	

	const int off_x = x + borderPadding + borderWidth;
	const int off_y = y + borderPadding + borderWidth;

	gfx.DrawRectDim(off_x + loc.x * dimention, off_y + loc.y * dimention, dimention - 1, dimention - 1, c);
}

bool Board::IsInsideBoard(const Location& loc) const
{
	return (loc.x >= 0 && loc.x < width && loc.y >= 0 && loc.y < height);
}

void Board::DrawBorder()
{
	const int top = y;
	const int left = x;
	const int bottom = top + 2*(borderWidth + borderPadding) + height * dimention;
	const int right = left + 2 * (borderWidth + borderPadding) + width * dimention;

	//top
	gfx.DrawRect(left, top, right, top + borderWidth, BorderColor);
	//left
	gfx.DrawRect(left, top + borderWidth, left + borderWidth, bottom - borderWidth, BorderColor);
	//right
	gfx.DrawRect(right - borderWidth, top + borderWidth, right, bottom - borderWidth, BorderColor);
	//bottom
	gfx.DrawRect(left, bottom - borderWidth, right, bottom, BorderColor);
}
