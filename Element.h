#pragma once
class Element
{
protected:
	int elementID;
	int* nodesIDs;

	Element(int, int*);
public:
	int GetNodeID(int);
};