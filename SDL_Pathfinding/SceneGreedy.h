#pragma once

#include "Scene.h"

class SceneGreedy : 
    public Scene
{
public:
    SceneGreedy();
    ~SceneGreedy();
    
    void Update(float dtime, SDL_Event* event);
    void Draw();

    const char* GetTitle();
    
private:
    Agent* agent;
    Vector2D coinPosition;

    void DrawCoin();
    void SetRandomCoinPosition(Vector2D characterPosition);
};
