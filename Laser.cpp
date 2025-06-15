#include "Laser.h"
#include <iostream>
using namespace std;

Laser::Laser(Vector2 position, int speed) {
    this->position = position;
    this->speed = speed;
    active = true;
}

void Laser::Update() {
    position.y += speed;
    if (active) {
        if (position.y > GetScreenHeight() || position.y < 0) {
            active = false;
        }
    }
}

void Laser::Draw() {
    if (active)
        DrawRectangle(position.x, position.y, 4, 15, { 253,249,60,255 });
}

Rectangle Laser::getRect() {
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 4;
    rect.height = 15;
    return rect;
}
