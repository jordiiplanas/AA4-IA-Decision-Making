#pragma once
#include "Node.h"
class Connection
{
public:
	Connection(Node* nodeFrom, Node* nodeTo, float weight);
	~Connection();
	float weight;
	Node* nodeFrom;
	Node* nodeTo;
};