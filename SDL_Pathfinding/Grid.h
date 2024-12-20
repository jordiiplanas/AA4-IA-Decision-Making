#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include "Agent.h"
#include "Connection.h"

class Grid
{
public:
	Grid(char* filename);
	~Grid();

private:
	int num_cell_x;
	int num_cell_y;

	std::vector<std::vector<Node*>> terrain;


public:
	Vector2D cell2pix(Vector2D cell);
	Vector2D pix2cell(Vector2D pix);
	bool isValidCell(Vector2D cell);
	std::vector<Connection*> getNeightbours(Node* current);

	inline std::vector<std::vector<Node*>> getTerrain() { return terrain; }
	Node* getNode(Vector2D pos) const;
	int getNumCellX();
	int getNumCellY();
	Vector2D getRandomValidPosition();
};
