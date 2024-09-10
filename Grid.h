#pragma once
#include <vector>
#include <map>
#include "Element.h"
#include "Node.h"

struct Grid
{
	friend class PoissonDiskSampling;
	friend class IDelaunayTriangulation;
	friend class DelaunayTriangulation2D;
	friend void WriteMesh(Grid*);
private:
	std::vector<std::vector<int>> segments;
	//std::vector<std::pair<int, int>> segments;
	std::map<int, Node*> nodesMap;
	std::map<int, Element*> elementsMap;
};