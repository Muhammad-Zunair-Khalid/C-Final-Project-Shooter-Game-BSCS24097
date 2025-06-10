#include "raylib.h"
#include "Game.h"


int main() {
	// UsingtheLibraryof Raylib
	Color grey = { 30,30,30,255 };
	Color yellow = { 243,216,63,255 };
	int offset = 50;
	int WindowHeight = 750;
	int WindowWidth = 750;
	
	InitWindow(WindowWidth + offset, WindowHeight+offset, "SpaceShip-Battle");
	SetTargetFPS(60);

	Game game;


	while (WindowShouldClose() == false) {

		BeginDrawing();
		ClearBackground(grey);
		DrawRectangleRoundedLines( { 10, 10, 788, 788 }, 0.18f, 20,yellow);

	

		EndDrawing();
	}
	CloseWindow();
}
