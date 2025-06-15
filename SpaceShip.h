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
    Sound lasersound;

public:
    SpaceShip();
    ~SpaceShip();
    void Draw() override;           
    void Update() override;        
    Rectangle getRect() override;  
    void MoveLeft();
    void MoveRight();
    void FireLaser();
    void Reset();
    vector<Laser> laser;
};
