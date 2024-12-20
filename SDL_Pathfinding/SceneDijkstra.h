#pragma once

#include "Scene.h"

class SceneDijkstra :
	public Scene
{
public:
	SceneDijkstra();
	~SceneDijkstra();
	
	void Update(float dtime, SDL_Event* event);
	void Draw();
	
	const char* GetTitle();
	
private:
	Agent* agent;
	Vector2D coinPosition;
	
	void DrawCoin();
	void SetRandomCoinPosition(Vector2D characterPosition);
};
