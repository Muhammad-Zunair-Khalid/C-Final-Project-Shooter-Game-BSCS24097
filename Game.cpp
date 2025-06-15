#include "Game.h"
#include <iostream>
#include <fstream>
#include <exception>
//#include <stdexcept>
#include "raylib.h"
using namespace std;

Game::Game() {
    try {
        currentState = MAIN_MENU;
        selectedMenuOption = 0;
        music = LoadMusicStream("interstellar.mp3");
        explosionSound = LoadSound("Sounds_explosion.ogg");
        PlayMusicStream(music);
        InitGame();
    }
    catch (const exception& e) {
        std::cerr << "Error in Game constructor: " << e.what() << endl;
        throw;
    }
}

Game::~Game() {
    try {
        UnloadMusicStream(music);
        UnloadSound(explosionSound);
    }
    catch (const exception& e) {
        std::cerr << "Error in Game destructor: " << e.what() << endl;
    }
}

void Game::InitGame() {
    try {
        obstacles = CreateObstacles();
        aliens = CreateAliens();
        aliensDirection = 1;
        timeLastAlienFired = 0.0f;
        timeLastSpawn = 0.0f;
        mysteryShipSpawnInterval = GetRandomValue(10, 20);
        lives = 3;
        score = 0;
        highscore = loadHighScoreFromFile();
        level = 1;
        run = true;
        spaceship.Reset();
        gameStartTime = GetTime();
    }
    catch (const exception& e) {
        std::cerr << "Error in InitGame: " << e.what() << endl;
        throw;
    }
}

void Game::CheckForHighScore()
{
    try {
        if (score > highscore) {
            highscore = score;
            saveHighScoreToFile(highscore);
        }
    }
    catch (const exception& e) {
        std::cerr << "Error in CheckForHighScore: " << e.what() << endl;
    }
}

void Game::saveHighScoreToFile(int highscore)
{
    try {
        ofstream highscoreFile("highscore.txt");
        if (highscoreFile.is_open()) {
            highscoreFile << highscore;
            highscoreFile.close();
        }
        else {
            cerr << "Failed to Save HighScore to File" << endl;
            throw std::runtime_error("Failed to open highscore file for writing");
        }
    }
    catch (const exception& e) {
        cerr << "Exception in saveHighScoreToFile: " << e.what() << endl;
        throw;
    }
}

int Game::loadHighScoreFromFile()
{
    try {
        int laodHighScore = 0;
        ifstream highScoreFile("highscore.txt");
        if (highScoreFile.is_open()) {
            highScoreFile >> laodHighScore;
            highScoreFile.close();
        }
        else {
            cerr << "Failed to Laod HighScore" << endl;
        }
        return laodHighScore;
    }
    catch (const exception& e) {
        cerr << "Exception in loadHighScoreFromFile: " << e.what() << endl;
        return 0; 
    }
}

void Game::Reset() {
    try {
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
    catch (const exception& e) {
        cerr << "Error in Reset: " << e.what() << endl;
        throw;
    }
}

void Game::DrawShip(Ship* ship) {
    try {
        if (ship != nullptr) {
            ship->Draw();
        }
    }
    catch (const exception& e) {
        cerr << "Error in DrawShip: " << e.what() << endl;
    }
}

void Game::UpdateShip(Ship* ship) {
    try {
        if (ship != nullptr) {
            ship->Update();
        }
    }
    catch (const exception& e) {
        cerr << "Error in UpdateShip: " << e.what() << endl;
    }
}

void Game::Draw() {
    try {
        if (currentState == MAIN_MENU) {
            DrawText("SPACE BATTLE", 260, 180, 30, YELLOW);
            const char* options[] = { "Resume", "New Game", "Save", "Load", "Exit","FighterJets(Currently Unavailable)" };
            for (int i = 0; i < 6; i++) {
                Color color = (i == selectedMenuOption) ? WHITE : GRAY;

                if (i == 5) {
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

            DrawText(("====GAME RESULT===="), 260, 30, 25, GREEN);
            DrawText(TextFormat("TOTAL-SCORE: %d", score), 285, 75, 20, YELLOW);
            DrawText(TextFormat("LIVES REMAINING: %d", lives), 285, 115, 20, YELLOW);
            DrawText(TextFormat("LEVEL-NO: %d", level), 285, 155, 20, YELLOW);
            DrawText(TextFormat("HIGH-SCORE: %d", highscore), 285, 195, 20, BLUE);
            DrawText(TextFormat("TIME PLAYED: %.0fs", gameStartTime), 285, 235, 20, PINK);

            return;
        }

        DrawShip(&spaceship);
        DrawShip(&mysteryship);

        for (auto& laser : spaceship.laser) laser.Draw();
        for (auto& obstacle : obstacles) obstacle.Draw();
        for (auto& alien : aliens) DrawShip(&alien);
        for (auto& laser : alienLasers) laser.Draw();

        DrawText(TextFormat("SCORE: %d", score), 60, 22, 20, YELLOW);
        DrawText(TextFormat("LIVES: %d", lives), 380, 22, 20, YELLOW);
        DrawText(TextFormat("LEVEL: %d", level), 220, 22, 20, YELLOW);
        DrawText(TextFormat("HIGH-SCORE: %d", highscore), 60, 50, 20, RED);
        DrawText(TextFormat("TIME: %.0fs", GetTime() - gameStartTime), 500, 50, 20, GREEN);
        DrawText("Press P to Pause", 540, 22, 20, ORANGE);


        /* static float elapsedTime = 0.0f;
        elapsedTime += GetFrameTime();
        DrawText(TextFormat("Elapsed Time: %.2f s", elapsedTime), 200, 220, 20, BLACK);*/
        //DrawText(TextFormat("Elapsed Time: %02.02f ms", GetFrameTime()), 200, 220, 20, BLACK);

        if (currentState == GAME_PAUSED) {
            DrawText("GAME PAUSED", 280, 300, 30, YELLOW);
            DrawText("Press P to Resume", 250, 360, 30, BLUE);
            DrawText("Press ENTER to return to Menu", 155, 390, 30, BLUE);
        }
    }
    catch (const exception& e) {
        cerr << "Error in Draw: " << e.what() << endl;
    }
}

void Game::Update() {
    try {
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
    catch (const exception& e) {
        cerr << "Error in Update: " << e.what() << endl;
    }
}

void Game::HandleInput() {
    try {
        if (currentState == MAIN_MENU) {
            if (IsKeyPressed(KEY_DOWN)) selectedMenuOption = (selectedMenuOption + 1) % 5;
            if (IsKeyPressed(KEY_UP)) selectedMenuOption = (selectedMenuOption + 4) % 5;
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
                    saveGame();
                }
                else if (selectedMenuOption == 3 && loadGame()) {
                    currentState = GAME_RUNNING;
                }
                else if (selectedMenuOption == 4) {
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
    catch (const exception& e) {
        cerr << "Error in HandleInput: " << e.what() << endl;
    }
}

void Game::GameOver() {
    try {
        currentState = GAME_OVER;
    }
    catch (const exception& e) {
        cerr << "Error in GameOver: " << e.what() << endl;
    }
}

void Game::DeleteInactiveLasers() {
    try {
        spaceship.laser.erase(
            remove_if(spaceship.laser.begin(), spaceship.laser.end(), [](Laser& l) { return !l.active; }),
            spaceship.laser.end());

        alienLasers.erase(
            remove_if(alienLasers.begin(), alienLasers.end(), [](Laser& l) { return !l.active; }),
            alienLasers.end());
    }
    catch (const exception& e) {
        cerr << "Error in DeleteInactiveLasers: " << e.what() << endl;
    }
}

vector<Obstacle> Game::CreateObstacles() {
    try {
        int obstacleWidth = Obstacle::grid[0].size() * 3;
        float gap = (GetScreenWidth() - (4 * obstacleWidth)) / 5;
        vector<Obstacle> result;
        for (int i = 0; i < 4; i++) {
            float offsetX = (i + 1) * gap + i * obstacleWidth;
            result.push_back(Obstacle({ offsetX, float(GetScreenHeight() - 100) }));
        }
        return result;
    }
    catch (const exception& e) {
        cerr << "Error in CreateObstacles: " << e.what() << endl;
        return vector<Obstacle>(); // Return empty vector on error
    }
}

vector<Alien> Game::CreateAliens() {
    try {
        vector<Alien> result;
        for (int row = 0; row < 5; row++) {
            for (int col = 0; col < 9; col++) {
                float x = 130 + col * 55;
                float y = 170 + row * 55;
                int alienType = 1;
                if (level == 3)
                {
                    alienType = 3;
                }
                else if (level == 1) alienType = (row % 2 == 0) ? 1 : 2;
                else if (level == 2) {
                    if (row % 3 == 0) alienType = 1;
                    else if (row % 3 == 1) alienType = 2;
                    else alienType = 3;
                }
                result.push_back(Alien(alienType, { x, y }));
            }
        }
        return result;
    }
    catch (const exception& e) {
        cerr << "Error in CreateAliens: " << e.what() << endl;
        return vector<Alien>(); // Return empty vector on error
    }
}

void Game::MoveAliens() {
    try {
        for (auto& alien : aliens) {
            if (alien.getPosition().x + alien.getRect().width > GetScreenWidth()) {
                aliensDirection = -1;
                MovedownAliens(4);
                break;
            }
            if (alien.getPosition().x < 0) {
                aliensDirection = 1;
                MovedownAliens(4);
                break;
            }
        }
        for (auto& alien : aliens) alien.Update(aliensDirection);
    }
    catch (const exception& e) {
        cerr << "Error in MoveAliens: " << e.what() << endl;
    }
}

void Game::MovedownAliens(int distance) {
    try {
        for (auto& alien : aliens) {
            Vector2 pos = alien.getPosition();
            pos.y += distance;
            alien.setPosition(pos);
        }
    }
    catch (const exception& e) {
        cerr << "Error in MovedownAliens: " << e.what() << endl;
    }
}

void Game::AlienShootLaser() {
    try {
        double currentTime = GetTime();
        float interval = std::max(0.1f, 0.35f - level * 0.02f);
        if (currentTime - timeLastAlienFired >= interval && !aliens.empty()) {
            int index = GetRandomValue(0, aliens.size() - 1);
            Vector2 pos = aliens[index].getPosition();
            Rectangle rect = aliens[index].getRect();
            alienLasers.push_back(Laser({ pos.x + rect.width / 2, pos.y + rect.height }, 6));
            timeLastAlienFired = currentTime;
        }
    }
    catch (const exception& e) {
        cerr << "Error in AlienShootLaser: " << e.what() << endl;
    }
}

void Game::CheckForCollisions() {
    try {
        for (auto& laser : spaceship.laser) {
            auto it = aliens.begin();
            while (it != aliens.end()) {
                if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
                    PlaySound(explosionSound);
                    it = aliens.erase(it);
                    laser.active = false;
                    score += 100;
                    CheckForHighScore();
                }
                else ++it;
            }
            for (auto& obstacle : obstacles) {
                auto bit = obstacle.blocks.begin();
                while (bit != obstacle.blocks.end()) {
                    if (CheckCollisionRecs(bit->getRect(), laser.getRect())) {
                        bit = obstacle.blocks.erase(bit);
                        laser.active = false;
                    }
                    else ++bit;
                }
            }
            if (CheckCollisionRecs(mysteryship.getRect(), laser.getRect())) {
                mysteryship.alive = false;
                laser.active = false;
                score += 500;
                CheckForHighScore();
                PlaySound(explosionSound);
            }
        }

        for (auto& laser : alienLasers) {
            if (CheckCollisionRecs(laser.getRect(), spaceship.getRect())) {
                laser.active = false;
                lives--;
                if (lives == 0) GameOver();
            }
            for (auto& obstacle : obstacles) {
                auto bit = obstacle.blocks.begin();
                while (bit != obstacle.blocks.end()) {
                    if (CheckCollisionRecs(bit->getRect(), laser.getRect())) {
                        bit = obstacle.blocks.erase(bit);
                        laser.active = false;
                    }
                    else ++bit;
                }
            }
        }

        for (auto& alien : aliens) {
            for (auto& obstacle : obstacles) {
                auto bit = obstacle.blocks.begin();
                while (bit != obstacle.blocks.end()) {
                    if (CheckCollisionRecs(bit->getRect(), alien.getRect())) {
                        bit = obstacle.blocks.erase(bit);
                    }
                    else ++bit;
                }
            }
            if (CheckCollisionRecs(alien.getRect(), spaceship.getRect())) {
                GameOver();
            }
        }
    }
    catch (const exception& e) {
        cerr << "Error in CheckForCollisions: " << e.what() << endl;
    }
}

void Game::saveGame() {
    try {
        ofstream file("save.dat", ios::binary);
        if (!file) {
            throw runtime_error("Failed to open save file for writing");
        }

        // Save core game state
        file.write((char*)&score, sizeof(score));
        file.write((char*)&level, sizeof(level));
        file.write((char*)&lives, sizeof(lives));
        file.write((char*)&aliensDirection, sizeof(aliensDirection));

        // Save positions
        Vector2 pos = spaceship.getPosition();
        file.write((char*)&pos, sizeof(pos));

        // Save aliens
        size_t count = aliens.size();
        file.write((char*)&count, sizeof(count));
        for (auto& alien : aliens) {
            pos = alien.getPosition();
            file.write((char*)&pos, sizeof(pos));
        }

        if (!file.good()) {
            throw runtime_error("Error occurred while writing save file");
        }

        file.close();
    }
    catch (const std::exception& e) {
        cerr << "Error in saveGame: " << e.what() << std::endl;
    }
}

bool Game::loadGame() {
    try {
        ifstream file("save.dat", ios::binary);
        if (!file) {
            return false;
        }

        //Load state
        file.read((char*)&score, sizeof(score));
        file.read((char*)&level, sizeof(level));
        file.read((char*)&lives, sizeof(lives));
        file.read((char*)&aliensDirection, sizeof(aliensDirection));

        //Load positions
        Vector2 pos;
        file.read((char*)&pos, sizeof(pos));
        spaceship.setPosition(pos);

        //Load aliens
        aliens.clear();
        size_t count;
        file.read((char*)&count, sizeof(count));

        if (count > 1000) {
            throw runtime_error("Invalid alien count in save file");
        }

        for (size_t i = 0; i < count; i++) {
            file.read((char*)&pos, sizeof(pos));
            aliens.push_back(Alien(1, pos));
        }

        if (!file.good() && !file.eof()) {
            throw runtime_error("Error occurred while reading save file");
        }

        file.close();
        return true;
    }
    catch (const exception& e) {
        cerr << "Error in loadGame: " << e.what() << std::endl;
        return false;
    }
}




