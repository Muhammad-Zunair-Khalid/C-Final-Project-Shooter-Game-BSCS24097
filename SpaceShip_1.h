#pragma once
#include "raylib.h"
#include "Laser.h"
#include "Ship.h"
#include <iostream>
#include <vector>
using namespace std;

class SpaceShip_1 : public Ship {
private:
    double lastFireTime;

public:
    SpaceShip_1();
    ~SpaceShip_1();
    void Draw() override;           // Virtual function override
    void Update() override;        // Virtual function override
    Rectangle getRect() override;  // Virtual function override
    void MoveLeft();
    void MoveRight();
    void FireLaser();
    void Reset();
    vector<Laser> laser;
};