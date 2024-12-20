#include "BFS.h"

BFS::BFS()
{
}

BFS::~BFS() = default;

void BFS::findPath(Agent* agent, Grid* grid)
{
    InitFind();

    std::vector<Vector2D> nodesDirections = { Vector2D(0, 1),Vector2D(0, -1),Vector2D(1, 0), Vector2D(-1, 0) };

    if (frontier.empty())
        return;   


    while (!frontier.empty())
    {
        Node current = frontier.front(); // Tomamos el nodo actual de la cola
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
            Vector2D position = (current.getPosition() + directions);
            Node* neighbor = grid->getNode(position);          
            if (!neighbor) continue;
       
            if (came_from.find(*neighbor) == came_from.end() && neighbor->blocked)
            {
                frontier.push(*neighbor); // Agregamos el vecino a la cola
                came_from[*neighbor] = current;
            }
                 
        }
    }   
}

void BFS::InitFind()
{
    //Colocamos en la frontera el nodo donde empieza el jugador
    frontier.push(start);

    //Creamos una aresta en el punto start
    came_from[start] = start;
}

void BFS::ResetNodes()
{
    frontier = std::queue<Node>();
    came_from.clear();
    arrived = false;
}

void BFS::InitPath(Grid* grid, Agent* agent)
{
    //Marcamos current como goal para buscar el camino de vuelta
    current = goal;
    path.push_back(current);
    RecoverPath(grid, agent);
}

void BFS::RecoverPath(Grid* grid, Agent* agent)
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
