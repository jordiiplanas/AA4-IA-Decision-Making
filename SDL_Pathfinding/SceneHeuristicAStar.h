#pragma once

#include "Scene.h"

class SceneHeuristicAStar : 
    public Scene
{
public:
    SceneHeuristicAStar();
    ~SceneHeuristicAStar();
    
    void Update(float dtime, SDL_Event* event);
    void Draw();
    
    const char* GetTitle();
    
private:
    Agent* agent;
    std::vector<Vector2D> coinPositions;
    int coinsAmount = 3;
    int currentCoin;
    
    void DrawCoin();
    void SetRandomCoinsPosition(Vector2D characterPosition);
    void SetRandomCoinPosition(Vector2D characterPosition, int coin);
    int GetNearestCoinIndex(Vector2D characterPosition) const;
};