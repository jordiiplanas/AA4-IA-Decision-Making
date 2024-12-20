#include "HeuristicAStar.h"

#include <stack>

HeuristicAStar::HeuristicAStar()
{
    arrived = false;
}

HeuristicAStar::~HeuristicAStar()
{

}

void HeuristicAStar::findPath(Agent* agent, Grid* grid)
{
    InitFind();

    std::vector<Vector2D> nodesDirections = { Vector2D(0, 1),Vector2D(0, -1),Vector2D(1, 0), Vector2D(-1, 0) };

    if (frontier.empty())
        return;
    
    while (!frontier.empty())
    {
        Node current = frontier.top().first;  // Tomamos el nodo con el menor costo
        frontier.pop();  // Extraemos el nodo de la frontera

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
            Node *neighboor =  grid->getNode(current.getPosition() + directions);

            int new_cost = cost_so_far[current] + neighboor->weight;

            //Manhattan distance
            float dx = abs(goal.getPosition().x - neighboor->getPosition().x);
            float dy = abs(goal.getPosition().y - neighboor->getPosition().y);

            float heuristc = dx + dy;
            new_cost += heuristc;

            if (cost_so_far.find(*neighboor) == cost_so_far.end() && neighboor->blocked)
            {
                frontier.push({ *neighboor,new_cost }); // Agregamos el vecino a la cola
                came_from[*neighboor] = current;
                cost_so_far[*neighboor] = new_cost;
            }
        }
    }

    // Si el objetivo no fue alcanzado, imprimimos un mensaje de error o lo manejamos de otra forma
    std::cerr << "El objetivo no ha sido encontrado." << std::endl;
}

void HeuristicAStar::InitFind()
{
    //Colocamos en la frontera el nodo donde empieza el jugador
    frontier.push({ start,0 });

    cost_so_far[start] = 0;

    came_from[start] = start;
}




void HeuristicAStar::ResetNodes()
{
    frontier = std::priority_queue<std::pair<Node, float>, std::vector<std::pair<Node, float>>, CompareNode>();
    came_from.clear();
    cost_so_far.clear();
    arrived = false;
}

void HeuristicAStar::InitPath(Grid* grid, Agent* agent)
{
    // Marcamos current como goal para buscar el camino de vuelta
    current = goal;
    path.push_back(current);
    RecoverPath(grid, agent);
}

void HeuristicAStar::RecoverPath(Grid* grid, Agent* agent)
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
        while (!returnPath.empty())
        {
            agent->addPathPoint(grid->cell2pix(returnPath.top().getPosition()));
            returnPath.pop();
        }
        path.clear();
    }
}