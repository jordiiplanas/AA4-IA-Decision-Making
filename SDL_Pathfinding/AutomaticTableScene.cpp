#include "AutomaticTableScene.h"

#include "AStar.h"
#include "BFS.h"
#include "Dijkstra.h"
#include "Greedy.h"
#include "PathFollowing.h"

std::string PathFindingTypeToString(PathFindingTypes type) {
    switch (type) {
    case PathFindingTypes::BFS: return "BFS";
    case PathFindingTypes::DIJKSTRA: return "DIJKSTRA";
    case PathFindingTypes::GREEDY: return "GREEDY";
    case PathFindingTypes::ASTAR: return "ASTAR";
    default: return "UNKNOWN";
    }
}

PathFindingAlgorithm* PathFindingTypeToAlgorithm(PathFindingTypes type)
{
    switch (type) {
    case PathFindingTypes::BFS: return new BFS;
    case PathFindingTypes::DIJKSTRA: return new Dijkstra;
    case PathFindingTypes::GREEDY: return new Greedy;
    case PathFindingTypes::ASTAR: return new AStar;
    default: return new BFS;
    }
}

AutomaticTableScene::AutomaticTableScene()
{
    Agent* agent = new Agent();
    agent->setBehavior(new PathFollowing);

    positions = {
        {{16, 3}, {21, 14}},
        {{36, 1}, {38, 20}},
        {{4, 3}, {32, 7}},
        {{31, 9}, {21, 8}},
        {{10, 22}, {22, 8}},
        {{13, 4}, {17, 8}},
        {{9, 3}, {29, 7}},
        {{28, 9}, {4, 13}},
        {{24, 20}, {8, 19}},
        {{27, 19}, {2, 4}},
        {{38, 8}, {6, 7}},
        {{15, 20}, {23, 14}},
        {{19, 21}, {4, 10}},
        {{20, 12}, {5, 20}},
        {{38, 9}, {6, 7}},
        {{23, 18}, {5, 7}},
        {{38, 12}, {3, 4}},
        {{25, 1}, {32, 14}}
    };

    PathFindingTypes type = PathFindingTypes::DIJKSTRA  ;
    std::cout << PathFindingTypeToString(type) << std::endl;

    for (auto positionPair : positions)
    {
        agent->setPosition(maze->cell2pix(positionPair.first));
        agent->setPathAlgorithm(PathFindingTypeToAlgorithm(type));
        agent->SetPathFindingTarget(*maze->getNode(positionPair.second));
        agent->ApplyPathFinding(maze);
        costs[type].push_back(agent->getPathAlgorithm()->GetCameFromSize());
        std::cout << "Pair: "
        << positionPair.first.x << "," << positionPair.first.y << " "
        << positionPair.second.x << "," << positionPair.second.y
        << " Cost: " << agent->getPathAlgorithm()->GetCameFromSize() << std::endl;
    }

    float max = 0;
    float min = 9999999999;
    float sum = 0;
    float count = 0;
    for (auto cost : costs)
    {
        for (int i = 0; i < cost.second.size() ; i++)
        {
            max = max(max, cost.second[i]);
            min = min(min, cost.second[i]);
            sum += cost.second[i];
            count++;
        }
    }

    std::cout << "Max: " << max << std::endl;
    std::cout << "Min: " << min << std::endl;
    std::cout << "Avg: " << sum / count << std::endl;
    
    

}

AutomaticTableScene::~AutomaticTableScene()
{
}

void AutomaticTableScene::Update(float dtime, SDL_Event* event)
{
    Scene::Update(dtime, event);
}

void AutomaticTableScene::Draw()
{
    Scene::Draw();
}

const char* AutomaticTableScene::GetTitle()
{
    return "SDL Path Finding :: Automatic Table";
}
