#pragma once
#include "raylib.h"
#include "Ship.h"

class MysteryShip : public Ship {
private:
    int speed;

public:
    MysteryShip();
    ~MysteryShip();
    void Draw() override;           
    void Update() override;        
    Rectangle getRect() override;  
    void Spawn();
    bool alive;
};
