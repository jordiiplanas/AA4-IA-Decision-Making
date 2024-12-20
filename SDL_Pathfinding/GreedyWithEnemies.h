#pragma once
#include <queue>
#include <unordered_map>

#include "PathFindingAlgorithm.h"


class GreedyWithEnemies : public PathFindingAlgorithm
{
public:
    struct Enemy
    {
        Agent* agent;
        int path;    
        Enemy(Agent* agent, int path)
        {
            this->agent = agent;
            this->path = path;
        }
    };
    
    GreedyWithEnemies();
    ~GreedyWithEnemies();
    void findPath(Agent* agent, Grid* grid) override;
    void InitFind();
    void ResetNodes() override;
    void InitPath(Grid* grid, Agent* agent);
    void RecoverPath(Grid* grid, Agent* agent);
    void SetEnemies(std::vector<Enemy*> enemies) { this->enemies = enemies; }

private:
    std::priority_queue<std::pair<Node, float>, std::vector<std::pair<Node, float>>, CompareNode> frontier;
    std::unordered_map<Node, int> cost_so_far;
    std::vector<Enemy*> enemies;

};