//Builds a Constant-Strain Triangle element.
#pragma once
#include "Element.h"
#include <vector>
#include "Node.h"
#include "Material.cpp"
class CST : public Element
{
public:
	CST(int, int* nodesIDs);
};

