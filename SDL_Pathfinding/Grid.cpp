#include "Grid.h"

using namespace std;

Grid::Grid(char* filename)
{
    num_cell_x = SRC_WIDTH / CELL_SIZE;
    num_cell_y = SRC_HEIGHT / CELL_SIZE;

    std::ifstream infile(filename);
    std::string line;
    int x = 0;
    int y = 0;

    while (std::getline(infile, line))
    {
        vector<Node*> terrain_row;
        std::stringstream lineStream(line);
        std::string cell;
        x = 0;

        while (std::getline(lineStream, cell, ','))
        {
            try {
                // Convertir el valor de la celda a entero
                int cost = std::stoi(cell);  // Usar std::stoi en lugar de atoi para mayor seguridad
                if (cost == 0)
                {
                    terrain_row.push_back(new Node(x, y, false, cost));
                }
                else
                {
                    terrain_row.push_back(new Node(x, y, true, cost));
                }
                // Crear el Nodo y agregarlo a la fila
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Invalid number in CSV: " << cell << std::endl;
            }

            x++;
        }

        y++;

        // Validar que cada fila tenga el número esperado de celdas
        SDL_assert(terrain_row.size() == num_cell_x);

        terrain.push_back(terrain_row);
    }

    // Validar que el número de filas coincida con la cantidad esperada
    SDL_assert(terrain.size() == num_cell_y);

    infile.close();
}

Grid::~Grid()
{
}

Node* Grid::getNode(Vector2D pos) const
{
    if (terrain.empty() || pos.x < 0 ||  pos.y < 0 || (pos.y >= terrain.size()) || (pos.x >= terrain[0].size()))
    {
        return nullptr;
    }
    return terrain[pos.y][pos.x];
}

int Grid::getNumCellX()
{
	return num_cell_x;
}

int Grid::getNumCellY()
{
	return num_cell_y;
}

Vector2D Grid::getRandomValidPosition()
{
    Vector2D randomPosition = Vector2D((int)(rand() % getNumCellX()), (float)(rand() % getNumCellY()));
    while (!isValidCell(randomPosition))
    {
        randomPosition = Vector2D((int)(rand() % getNumCellX()), (float)(rand() % getNumCellY()));
    }
    return randomPosition;
}

Vector2D Grid::cell2pix(Vector2D cell)
{
	int offset = CELL_SIZE / 2;
	return Vector2D(cell.x*CELL_SIZE + offset, cell.y*CELL_SIZE + offset);
}

Vector2D Grid::pix2cell(Vector2D pix)
{
	return Vector2D((float)((int)pix.x / CELL_SIZE), (float)((int)pix.y / CELL_SIZE));
}

bool Grid::isValidCell(Vector2D cell)
{
	if ((cell.x < 0) || (cell.y < 0) || (cell.y >= num_cell_y) || (cell.x >= num_cell_x))
		return false;

	 return (terrain[(unsigned int)cell.y][(unsigned int)cell.x]->blocked);
}

std::vector<Connection*> Grid::getNeightbours(Node* current)
{
    std::vector<Connection*> connections;

    // Cambiar las coordenadas, ahora 'x' es 'y' y 'y' es 'x'
    if (current->blocked)
    {
        if (current->y < num_cell_y - 1)
        {
            connections.push_back(new Connection(current, terrain[current->y + 1][current->x], current->weight));
        }
        if (current->x < num_cell_x - 1)  // 'x' por 'y' y 'y' por 'x'
        {
            connections.push_back(new Connection(current, terrain[current->y][current->x + 1], current->weight));
        }
        if (current->y > 0)  // 'x' por 'y' y 'y' por 'x'
        {
            connections.push_back(new Connection(current, terrain[current->y - 1][current->x], current->weight));
        }
        if (current->x > 0)  // 'x' por 'y' y 'y' por 'x'
        {
            connections.push_back(new Connection(current, terrain[current->y][current->x - 1], current->weight));
        }
    }
    return connections;
}

