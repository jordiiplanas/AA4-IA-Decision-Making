#pragma once

#include "Scene.h"

class SceneAStar : 
    public Scene
{
public:
    SceneAStar();
    ~SceneAStar();
    
    void Update(float dtime, SDL_Event* event);
    void Draw();
    
    const char* GetTitle();
    
private:
    Agent* agent;
    Vector2D coinPosition;

    void DrawCoin();
    void SetRandomCoinPosition(Vector2D characterPosition);
};