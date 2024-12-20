#include "PathFindingAlgorithm.h"

#include "utils.h"

PathFindingAlgorithm::PathFindingAlgorithm(): start(Node(0,0,0,0)), goal(Node(0,0,0,0)), current(Node(0,0,0,0))
{
    arrived = false;
}

void PathFindingAlgorithm::Draw(Grid* grid)
{
    for(auto pair : came_from)
    {
        Vector2D position = grid->cell2pix(Vector2D(pair.first.x, pair.first.y));
        draw_circle(TheApp::Instance()->getRenderer(), position.x, position.y, 15, 180, 0, 0, 255);
    }
}

void PathFindingAlgorithm::ResetNodes()
{
    came_from.clear();
    arrived = false;
}

