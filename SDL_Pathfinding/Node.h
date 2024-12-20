#pragma once
#include "Vector2D.h"
#include <functional> // Para std::hash
#include <cstddef>    // Para std::size_t

class Node
{
public:
	Node(int x, int y, bool blocked, int weight = 5)
		: x(x), y(y), blocked(blocked), weight(weight) {}

	Node(Vector2D position, bool blocked, int weight = 5)
		: x((int)position.x), y((int)position.y), blocked(blocked), weight(weight) {}

	Node()
	{
		x = 0;
		y = 0;
		blocked = true;
		weight = 1;
	}
	
	~Node() {}

	int x;
	int y;
	bool blocked = false;
	int weight;

	inline Vector2D getPosition() const { return Vector2D((float)x, (float)y); }

	// Operador de igualdad para usar con unordered_map
	bool operator==(const Node& other) const {
		return x == other.x && y == other.y;
	}

	// Operador < para usar con map
	bool operator<(const Node& other) const {
		if (x < other.x) return true;
		if (x > other.x) return false;
		return y < other.y;
	}
};

// Especialización de std::hash<Node> para usar con unordered_map
namespace std {
	template<>
	struct hash<Node> {
		std::size_t operator()(const Node& n) const noexcept {
			// Combinar x e y en un solo valor hash. Ejemplo simple:
			std::size_t h1 = std::hash<int>()(n.x);
			std::size_t h2 = std::hash<int>()(n.y);
			// Combinar los hashes (este es un método simple, se puede mejorar)
			return h1 ^ (h2 + 0x9e3779b97f4a7c16ULL + (h1 << 6) + (h1 >> 2));
		}
	};
}
