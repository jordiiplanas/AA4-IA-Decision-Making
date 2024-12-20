#pragma once
#include <queue>
#include <unordered_map>

#include "PathFindingAlgorithm.h"


class Greedy : public PathFindingAlgorithm
{
public:
    Greedy();
    ~Greedy();
    void findPath(Agent* agent, Grid* grid) override;
    void InitFind();
    void ResetNodes() override;
    void InitPath(Grid* grid, Agent* agent);
    void RecoverPath(Grid* grid, Agent* agent);

private:
    std::priority_queue<std::pair<Node, float>, std::vector<std::pair<Node, float>>, CompareNode> frontier;
    std::unordered_map<Node, int> cost_so_far;

};