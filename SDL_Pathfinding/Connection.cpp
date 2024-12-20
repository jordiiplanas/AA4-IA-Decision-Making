#include "Connection.h"
Connection::Connection(Node* nodeFrom, Node* nodeTo, float weight) : nodeFrom(nodeFrom), nodeTo(nodeTo), weight(weight)
{

}
Connection::~Connection()
{
}
