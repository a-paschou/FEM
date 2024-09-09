#include "Node.h"

Node::Node(int id, double x, double y, double z)
	:ID{ id }, X{ x }, Y{ y }, Z{ z }
{
}

int Node::GetID()
{
	return ID;
}

double Node::GetX()
{
	return X;
}

double Node::GetY()
{
	return Y;
}

double Node::GetZ()
{
	return Z;
}