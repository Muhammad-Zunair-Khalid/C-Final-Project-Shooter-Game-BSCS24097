#pragma once
// ========== BASE CLASS ==========
#pragma once
#include "raylib.h"
#include <iostream>
#include <vector>
using namespace std;

// Abstract base class for all ships
class Ship {
protected:
    Texture2D image;
    Vector2 position;

public:
    Ship() {}
    virtual ~Ship() {}

    // Pure virtual functions (must be implemented by derived classes)
    virtual void Draw() = 0;
    virtual void Update() = 0;
    virtual Rectangle getRect() = 0;

    // Common functionality
    Vector2 getPosition() { return position; }
    void setPosition(Vector2 pos) { position = pos; }
};
