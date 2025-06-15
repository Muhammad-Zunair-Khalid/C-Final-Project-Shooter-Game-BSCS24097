#include "raylib.h"
#include "Game.h"
#include <exception>
#include <iostream>

int main() {
    try {
        Color grey = { 30,30,30,255 };
        Color yellow = { 243,216,63,255 };
        int offset = 50;
        int WindowHeight = 750;
        int WindowWidth = 750;

        InitWindow(WindowWidth + offset, WindowHeight + offset, "SpaceShip-Battle");
        InitAudioDevice();
        SetTargetFPS(60);

        Game game;

        while (WindowShouldClose() == false) {
            try {
                UpdateMusicStream(game.music);
                game.HandleInput();
                game.Update();

                BeginDrawing();
                ClearBackground(grey);
                DrawRectangleRoundedLines({ 10, 10, 788, 788 }, 0.18f, 20, yellow);

                game.Draw();

                EndDrawing();
            }
            catch (const exception& e) {
                cerr << "Error in game loop: " << e.what() << endl;
                
            }
        }
        CloseWindow();
        CloseAudioDevice();
        return 0;
    }
    catch (const exception& e) {
        cerr << "Fatal error in main: " << e.what() << endl;
        CloseWindow();
        CloseAudioDevice();
        return -1;
    }
}
