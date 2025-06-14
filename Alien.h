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
    void Draw() override;           
    void Update() override;         
    Rectangle getRect() override;  
    int GetType();
};
