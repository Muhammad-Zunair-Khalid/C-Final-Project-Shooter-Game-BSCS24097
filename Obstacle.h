// ========== OBSTACLE CLASS (unchanged) ==========
#pragma once
#include <vector>
#include "Block.h"
#include "raylib.h"
using namespace std;

class Obstacle {
public:
    Obstacle(Vector2 position);
    void Draw();
    Vector2 position;
    vector<Block> blocks;
    static vector<vector<int>> grid;
};
