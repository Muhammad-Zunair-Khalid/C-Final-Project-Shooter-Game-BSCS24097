#include "SpaceShip.h"

SpaceShip::SpaceShip() {
    image = LoadTexture("FighterShip.png");
    position.x = (GetScreenWidth() - image.width) / 2;
    position.y = GetScreenHeight() - image.height;
    lastFireTime = 0.0;
    lasersound = LoadSound("Sounds_laser.ogg");
}

SpaceShip::~SpaceShip() {
    UnloadTexture(image);
    UnloadSound(lasersound);
}

void SpaceShip::Draw() {
    DrawTextureV(image, position, WHITE);
}

void SpaceShip::Update() {
    
    for (auto& l : laser) {
        l.Update();
    }
}

void SpaceShip::MoveLeft() {
    position.x -= 4;
    if (position.x < 0) {
        position.x = 0;
    }
}

void SpaceShip::MoveRight() {
    position.x += 4;
    if (position.x > (GetScreenWidth() - image.width)) {
        position.x = (GetScreenWidth() - image.width);
    }
}

void SpaceShip::FireLaser() {
    if (GetTime() - lastFireTime >= 0.35) {
        laser.push_back(Laser({ position.x + image.width / 2 - 2, position.y }, -6));
        lastFireTime = GetTime();
        PlaySound(lasersound);
    }
}

Rectangle SpaceShip::getRect() {
    return { position.x, position.y, float(image.width), float(image.height) };
}

void SpaceShip::Reset() {
    position.x = (GetScreenWidth() - image.width) / 2.0f;
    position.y = GetScreenHeight() - image.height;
}

