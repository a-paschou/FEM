#pragma once
class Node
{
protected:
	int ID;
	double X;
	double Y;
	double Z;
public:
	Node(int, double x = 0, double y = 0, double z = 0);
	int GetID();
	double GetX();
	double GetY();
	double GetZ();
};

