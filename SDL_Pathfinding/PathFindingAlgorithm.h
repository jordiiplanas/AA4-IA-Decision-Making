#pragma once
#include <map>

#include "Agent.h"
#include "Node.h"
#include "Grid.h"

struct CompareNode {
	bool operator()(const std::pair<Node, float>& a, const std::pair<Node, float>& b) const
	{
		if (a.second == b.second) {
			return a.first < b.first;  // Desempatar usando el puntero (por dirección de memoria)
		}
		return a.second > b.second;  // Comparación por el costo
	}
	bool operator()(const std::pair<Node, int>& a, const std::pair<Node, int>& b) const
	{
		if (a.second == b.second) {
			return a.first < b.first;  // Desempatar usando el puntero (por dirección de memoria)
		}
		return a.second > b.second;  // Comparación por el costo
	}
};

class PathFindingAlgorithm
{
public:
	PathFindingAlgorithm();
	inline void SetStart(Node node) { start = node; }
	inline void SetGoal(Node node) { goal = node; }
	virtual void findPath(Agent* agent, Grid* grid) = 0;
	void Draw(Grid* grid);
	virtual void ResetNodes();
	inline Vector2D GetGoal() { return Vector2D(goal.x, goal.y); }
	inline int GetCameFromSize() { return came_from.size(); }

protected:
	bool arrived = false;
	Node start;
	Node goal;
	Node current;
	std::vector<Node> path;
	std::map<Node, Node> came_from;

};			
