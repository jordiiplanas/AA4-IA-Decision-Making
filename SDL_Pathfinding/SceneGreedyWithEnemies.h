#pragma once
#include <map>

#include "Scene.h"
#include "GreedyWithEnemies.h"
class SceneGreedyWithEnemies : 
    public Scene
{
public:
    SceneGreedyWithEnemies();
    ~SceneGreedyWithEnemies();

    void Update(float dtime, SDL_Event* event);
    void Draw();

    const char* GetTitle();

private:
    Agent* agent;
    Vector2D coinPosition;
    std::vector<GreedyWithEnemies::Enemy*> enemies;
    std::map<int, std::vector<Vector2D>> paths;
    void DrawCoin();
    void SetRandomCoinPosition(Vector2D characterPosition);
};
