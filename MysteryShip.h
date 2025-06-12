// ========== MYSTERY SHIP CLASS (inherits from Ship) ==========
#pragma once
#include "raylib.h"
#include "Ship.h"

class MysteryShip : public Ship {
private:
    int speed;

public:
    MysteryShip();
    ~MysteryShip();
    void Draw() override;           // Virtual function override
    void Update() override;        // Virtual function override
    Rectangle getRect() override;  // Virtual function override
    void Spawn();
    bool alive;
};
