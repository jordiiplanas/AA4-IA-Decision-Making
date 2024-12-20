#pragma once
#include "PathFindingAlgorithm.h"
#include "SDL_SimpleApp.h"
#include "queue"	
#include "Connection.h"
#include "unordered_map"
#include "unordered_set"
#include <stack>
class BFS : public PathFindingAlgorithm
{
public:
	BFS();
	~BFS();
	void findPath(Agent* agent, Grid* grid) override;
	void InitFind();
    void ResetNodes() override;
	void InitPath(Grid* grid, Agent* agent);
	void RecoverPath(Grid* grid, Agent* agent);

private:
	std::queue<Node> frontier;
};