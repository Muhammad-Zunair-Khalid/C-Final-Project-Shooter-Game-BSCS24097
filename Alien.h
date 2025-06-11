// ========== ALIEN CLASS (inherits from Ship) ==========
#pragma once
#include "raylib.h"
#include "Ship.h"

class Alien : public Ship {
private:
    int type;

public:
    Alien(int type, Vector2 position);
    ~Alien();
    void Update(int direction);
    void Draw() override;           // Virtual function override
    void Update() override;        // Virtual function override  
    Rectangle getRect() override;  // Virtual function override
    int GetType();
};
