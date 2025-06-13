#include "Game.h"
#include <iostream>
#include "raylib.h"
using namespace std;

Game::Game() {
    currentState = MAIN_MENU;
    selectedMenuOption = 0;
    InitGame();
}

Game::~Game() {}

void Game::InitGame() {
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    aliensDirection = 1;
    timeLastAlienFired = 0.0f;
    timeLastSpawn = 0.0f;
    mysteryShipSpawnInterval = GetRandomValue(10, 20);
    lives = 3;
    score = 0;
    level = 1;
    run = true;
    spaceship.Reset();
}

void Game::Reset() {
    spaceship.Reset();
    aliens.clear();
    alienLasers.clear();
    obstacles.clear();
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    aliensDirection = 1;
    timeLastAlienFired = 0.0f;
    timeLastSpawn = 0.0f;
    lives = 3;
    score = 0;
    level = 1;
}

void Game::DrawShip(Ship* ship) {
    ship->Draw();
}

void Game::UpdateShip(Ship* ship) {
    ship->Update();
}

void Game::Draw() {
    if (currentState == MAIN_MENU) {
        DrawText("SPACE BATTLE", 260, 180, 30, YELLOW);
        const char* options[] = { "Resume", "New Game","Exit","FighterJets(Currently Unavailable)" };
        for (int i = 0; i < 4; i++) {
            Color color = (i == selectedMenuOption) ? WHITE : GRAY;
            
           

            if (i == 3) {
                DrawText(options[i], 200, 250 + i * 40, 20, color);
            }
            else {
                DrawText(options[i], 330, 250 + i * 40, 20, color);
            }
        }
        return;
    }

    if (currentState == GAME_OVER) {
        DrawText("GAME OVER - Press ENTER to return to MENU", 180, 350, 20, RED);
        return;
    }

    DrawShip(&spaceship);
    DrawShip(&mysteryship);

    for (auto& laser : spaceship.laser) laser.Draw();
    for (auto& obstacle : obstacles) obstacle.Draw();
    for (auto& alien : aliens) DrawShip(&alien);
    for (auto& laser : alienLasers) laser.Draw();

    DrawText(TextFormat("Score: %d", score), 60, 22, 22, YELLOW);
    DrawText(TextFormat("Lives: %d", lives), 380, 22, 22, YELLOW);
    DrawText(TextFormat("Level: %d", level), 220, 22, 22, YELLOW);
    DrawText("Press P to Pause", 540, 22, 22, ORANGE);
  /*  DrawText(TextFormat("Elapsed Time: %02.02f ms", GetFrameTime() * 1000), 200, 220, 20, BLACK);*/

    if (currentState == GAME_PAUSED) {
        DrawText("GAME PAUSED", 280, 300, 30, YELLOW);
        DrawText("Press P to Resume", 250, 360, 30, BLUE);
        DrawText("Press ENTER to return to Menu", 155, 390, 30, BLUE);
    }
}

void Game::Update() {
    if (currentState != GAME_RUNNING) return;

    double currentTime = GetTime();
    if (currentTime - timeLastSpawn > mysteryShipSpawnInterval) {
        mysteryship.Spawn();
        timeLastSpawn = currentTime;
        mysteryShipSpawnInterval = GetRandomValue(10, 20);
    }

    UpdateShip(&spaceship);
    UpdateShip(&mysteryship);

    for (auto& alien : aliens) UpdateShip(&alien);
    MoveAliens();
    AlienShootLaser();
    DeleteInactiveLasers();
    CheckForCollisions();

    for (auto& laser : alienLasers) laser.Update();
    for (auto& laser : spaceship.laser) laser.Update();

    if (aliens.empty()) {
        level++;
        aliens = CreateAliens();
        aliensDirection = 1;
    }
}

void Game::HandleInput() {
    if (currentState == MAIN_MENU) {
        if (IsKeyPressed(KEY_DOWN)) selectedMenuOption = (selectedMenuOption + 1) % 3;
        if (IsKeyPressed(KEY_UP)) selectedMenuOption = (selectedMenuOption + 2) % 3;
        if (IsKeyPressed(KEY_ENTER)) {
            if (selectedMenuOption == 0 && lives > 0) {
                currentState = GAME_RUNNING;
            }
            else if (selectedMenuOption == 1) {
                Reset();
                InitGame();
                currentState = GAME_RUNNING;
            }
            else if (selectedMenuOption == 2) {
                run = false;
            }
        }
        return;
    }

    if (currentState == GAME_RUNNING) {
        if (IsKeyPressed(KEY_P)) {
            currentState = GAME_PAUSED;
            return;
        }
        if (IsKeyDown(KEY_LEFT)) spaceship.MoveLeft();
        if (IsKeyDown(KEY_RIGHT)) spaceship.MoveRight();
        if (IsKeyDown(KEY_UP)) spaceship.FireLaser();
    }

    if (currentState == GAME_PAUSED) {
        if (IsKeyPressed(KEY_P)) {
            currentState = GAME_RUNNING;
        }
        else if (IsKeyPressed(KEY_ENTER)) {
            currentState = MAIN_MENU;
        }
    }

    if (currentState == GAME_OVER && IsKeyPressed(KEY_ENTER)) {
        currentState = MAIN_MENU;
    }
}
