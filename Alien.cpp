#include "Alien.h"

Alien::Alien(int type, Vector2 position) {
    this->type = type;
    this->position = position;
    switch (type) {
    case 1:
        image = LoadTexture("EnemyShip_1.png");
        break;
    case 2:
        image = LoadTexture("EnemyShip_2.png");
        break;
    case 3:
        image = LoadTexture("EnemyShip_3.png");
        break;
    default:
        image = LoadTexture("EnemyShip_1.png");
        break;
    }
}

Alien::~Alien() {
    //UnloadTexture(image);
}

void Alien::Draw() {
    DrawTextureV(image, position, WHITE);
}

void Alien::Update() {
    // Base update functionality
}

void Alien::Update(int direction) {
    position.x += direction;
}

int Alien::GetType() {
    return type;
}

Rectangle Alien::getRect() {
    return { position.x, position.y, float(image.width), float(image.height) };
}
