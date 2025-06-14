
#include "SpaceShip_1.h"

SpaceShip_1::SpaceShip_1() {
    image = LoadTexture("FighterShip_2.png");
    position.x = (GetScreenWidth() - image.width) / 2;
    position.y = GetScreenHeight() - image.height;
    lastFireTime = 0.0;
}

SpaceShip_1::~SpaceShip_1() {
    UnloadTexture(image);
}

void SpaceShip_1::Draw() {
    DrawTextureV(image, position, WHITE);
}

void SpaceShip_1::Update() {
    // Update lasers
    for (auto& l : laser) {
        l.Update();
    }
}

void SpaceShip_1::MoveLeft() {
    position.x -= 6;
    if (position.x < 0) {
        position.x = 0;
    }
}

void SpaceShip_1::MoveRight() {
    position.x += 6;
    if (position.x > (GetScreenWidth() - image.width)) {
        position.x = (GetScreenWidth() - image.width);
    }
}

void SpaceShip_1::FireLaser() {
    if (GetTime() - lastFireTime >= 0.25) {
        laser.push_back(Laser({ position.x + image.width / 2 - 2, position.y }, -8));
        lastFireTime = GetTime();
    }
}

Rectangle SpaceShip_1::getRect() {
    return { position.x, position.y, float(image.width), float(image.height) };
}

void SpaceShip_1::Reset() {
    position.x = (GetScreenWidth() - image.width) / 2.0f;
    position.y = GetScreenHeight() - image.height;
}

