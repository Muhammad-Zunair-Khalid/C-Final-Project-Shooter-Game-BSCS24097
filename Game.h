#pragma once
#include "SpaceShip.h"
#include "SpaceShip_1.h"
#include "Obstacle.h"
#include "Alien.h"
#include "MysteryShip.h"
#include "Laser.h"
#include "Ship.h"
#include <vector>

enum GameState {
    MAIN_MENU,
    GAME_RUNNING,
    GAME_PAUSED,
    GAME_OVER
};

class Game {
private:
    SpaceShip spaceship;
    SpaceShip_1 spaceship_1;
    std::vector<Obstacle> obstacles;
    std::vector<Obstacle> CreateObstacles();
    std::vector<Alien> aliens;
    std::vector<Alien> CreateAliens();
    void MoveAliens();
    void MovedownAliens(int distance);
    int aliensDirection;
    std::vector<Laser> alienLasers;
    void AlienShootLaser();
    void CheckForCollisions();
    void DeleteInactiveLasers();
    constexpr static float alienLaserShootInterval = 0.35f;
    float timeLastAlienFired;
    MysteryShip mysteryship;
    float mysteryShipSpawnInterval;
    float timeLastSpawn;

    void GameOver();
    void Reset();
    void InitGame();
    void CheckForHighScore();
    void saveHighScoreToFile(int highscore);
    int loadHighScoreFromFile();
    void DrawShip(Ship* ship);
    void UpdateShip(Ship* ship);
    Sound explosionSound;

    void saveGame();
    bool loadGame();
    float gameStartTime;

public:
    Game();
    ~Game();
    void Draw();
    void Update();
    void HandleInput();
    bool run;


    int score;
    int level;
    int lives;
    int highscore;
    GameState currentState;
    int selectedMenuOption;
    Music music;
};
