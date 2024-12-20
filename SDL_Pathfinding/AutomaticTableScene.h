#pragma once
#include <map>

#include "Scene.h"

enum class PathFindingTypes
{
    BFS,
    DIJKSTRA,
    GREEDY,
    ASTAR
};

class AutomaticTableScene
    : public Scene
{
public:
    AutomaticTableScene();
    ~AutomaticTableScene();
    
    void Update(float dtime, SDL_Event* event);
    void Draw();
    
    const char* GetTitle();
    
private:
    std::map<PathFindingTypes, std::vector<int>> costs;
    std::vector<std::pair<Vector2D, Vector2D>> positions;

    std::map<PathFindingTypes, int> path_max;
    std::map<PathFindingTypes, int> path_min;
    std::map<PathFindingTypes, int> path_sum;
    std::map<PathFindingTypes, int> path_count;

    std::map<PathFindingTypes, int> path_avg;
};
