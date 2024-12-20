#pragma once
#include <SDL.h>
#include "Node.h"
#include "Grid.h"

class Grid;

class Scene
{
public:
    Scene();
    virtual ~Scene();
	
    virtual void Update(float dtime, SDL_Event *event);
    virtual void Draw();
    virtual const char* GetTitle() { return ""; }
protected:
    bool drawGrid;
	
    Grid *maze;
    SDL_Texture* background_texture;
    SDL_Texture* coin_texture;

    void DrawMaze();
    bool LoadTextures(char* filename_bg, char* filename_coin);
    void SetRandomCoinPosition();
};

