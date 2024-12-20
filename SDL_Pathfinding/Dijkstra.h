#pragma once
#include "PathFindingAlgorithm.h"
#include "SDL_SimpleApp.h"
#include "queue"	
#include "Connection.h"
#include "unordered_map"
#include "unordered_set"
#include <stack>



class Dijkstra : public PathFindingAlgorithm
{
public:
	Dijkstra();
	~Dijkstra();
	void findPath(Agent* agent, Grid* grid) override;
	void InitFind();
	void ResetNodes() override;
	void InitPath(Grid* grid, Agent* agent);
	void RecoverPath(Grid* grid, Agent* agent);

private:
	std::priority_queue<std::pair<Node, int>, std::vector<std::pair<Node, int>>, CompareNode> frontier;
	std::unordered_map<Node, int> cost_so_far;
};