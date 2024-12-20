﻿#include "Dijkstra.h"
#include <queue>
#include <unordered_map>
#include <vector>

Dijkstra::Dijkstra() : PathFindingAlgorithm()
{
}

Dijkstra::~Dijkstra()
{
}

void Dijkstra::findPath(Agent* agent, Grid* grid)
{
    InitFind();

    std::vector<Vector2D> nodesDirections = { Vector2D(0, 1),Vector2D(0, -1),Vector2D(1, 0), Vector2D(-1, 0) };

    if (frontier.empty())
        return;       

    while (!frontier.empty())
    {
        Node current = frontier.top().first; // Tomamos el nodo actual de la cola
        frontier.pop(); // Eliminamos el nodo de la cola 
        // Marcamos el nodo como visitado

        // Comprobamos si hemos alcanzado el objetivo
        if (current.getPosition() == goal.getPosition())
        {
            arrived = true;
            InitPath(grid, agent);
            return;
        }

        // Procesamos los vecinos del nodo actual
        for (Vector2D directions : nodesDirections)
        {
            Node* neighbor = grid->getNode(current.getPosition() + directions);          

            int newCost = cost_so_far[current] + neighbor->weight;
       
            if (cost_so_far.find(*neighbor) == cost_so_far.end() && neighbor->blocked)
            {
                frontier.push({*neighbor,newCost}); // Agregamos el vecino a la cola
                came_from[*neighbor] = current;
                cost_so_far[*neighbor] = newCost;
            }
                 
        }
    }   
}

void Dijkstra::InitFind()
{
    frontier.push({start,0});

    cost_so_far[start] = 0;

    came_from[start] = start;    
}

void Dijkstra::ResetNodes()
{
    while (!frontier.empty())
    {
        frontier.pop();
    }
    PathFindingAlgorithm::ResetNodes();
    cost_so_far.clear();
}

void Dijkstra::InitPath(Grid* grid, Agent* agent)
{
    // Marcamos current como goal para buscar el camino de vuelta
    current = goal;
    path.push_back(current);
    RecoverPath(grid, agent);
}

void Dijkstra::RecoverPath(Grid* grid, Agent* agent)
{
    if (arrived)
    {
        std::stack<Node> returnPath;

        Node nextNode = current;
        returnPath.push(nextNode);

        Vector2D cellPosAgent = grid->pix2cell(agent->getPosition());

        while (nextNode.getPosition() != cellPosAgent)
        {
            nextNode = came_from[nextNode];
            returnPath.push(nextNode);
        }

        agent->clearPath();
        while(!returnPath.empty())
        {            
            agent->addPathPoint(grid->cell2pix(returnPath.top().getPosition()));
            returnPath.pop();
        }
        path.clear();
    }
}
