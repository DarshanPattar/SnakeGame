/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(gfx),
	rng(std::random_device()()),
	snake({ 4, 4 }),
	food(rng, brd, snake)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (!GameStarted && wnd.kbd.KeyIsPressed(VK_RETURN)) {
		GameStarted = true;
	}
	if (GameStarted) {
		if (!GameOver) {
			if (wnd.kbd.KeyIsPressed(VK_UP)) {
				Location l({ 0, 1 });
				if (delta_loc.x != l.x && delta_loc.y != l.y)
					delta_loc = { 0, -1 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
				Location l({ 0, -1 });
				if (delta_loc.x != l.x && delta_loc.y != l.y)
					delta_loc = { 0, 1 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_LEFT)) {
				Location l({ 1, 0 });
				if (delta_loc.x != l.x && delta_loc.y != l.y)
					delta_loc = { -1, 0 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {
				Location l({ -1, 0 });
				if (delta_loc.x != l.x && delta_loc.y != l.y)
					delta_loc = { 1, 0 };
			}
			count++;
			if (count >= SnakeMoveRate) {
				count = 0;
				//Custom

				if (!brd.IsInsideBoard(snake.GetNextHeadLocation(delta_loc)) || snake.BitItself(delta_loc)) {
					GameOver = true;
				}
				else {
					const bool eating = snake.GetNextHeadLocation(delta_loc).x == food.GetLocation().x && snake.GetNextHeadLocation(delta_loc).y == food.GetLocation().y;
					if (eating) {
						snake.Grow();
					}
					snake.MoveBy(delta_loc);
					if (eating) {
						food.Respawn(rng, brd, snake);
						difficultyCount++;
						if (difficultyCount == difficulty) {
							difficultyCount = 0;
							SnakeMoveRate--;
						}
					}
				}
			}
		}
	}
}

void Game::ComposeFrame()
{	
	if (GameStarted) {
		snake.Draw(brd);
		food.Draw(brd);
		if (GameOver) {
			SpriteCodex::DrawGameOver(200, 200, gfx);
		}
		brd.DrawBorder();
	}
	else {
		SpriteCodex::DrawTitle(200, 200, gfx);
	}
}
