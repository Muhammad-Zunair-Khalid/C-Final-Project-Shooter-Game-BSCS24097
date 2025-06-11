//SPACESHIP CLASS (inherits from Ship which is Base Class)
#pragma once
#include "raylib.h"
#include "Laser.h"
#include "Ship.h"
#include <iostream>
#include <vector>
using namespace std;

class SpaceShip : public Ship {
private:
    double lastFireTime;

public:
    SpaceShip();
    ~SpaceShip();
    void Draw() override;           // Virtual function override
    void Update() override;        // Virtual function override
    Rectangle getRect() override;  // Virtual function override
    void MoveLeft();
    void MoveRight();
    void FireLaser();
    void Reset();
    vector<Laser> laser;
};
