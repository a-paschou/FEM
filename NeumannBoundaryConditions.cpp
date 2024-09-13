#include "NeumannBoundaryConditions.h"
#include <stdexcept>

using enum DOFType;
NeumannBoundaryConditions::NeumannBoundaryConditions(std::vector<int>* nodeIDs, std::vector<DOFType>* dofTypes, std::vector<double>* amounts)
	: nodeIDs(nodeIDs), dofTypes(dofTypes), amounts(amounts)
{
}

std::vector<int>* NeumannBoundaryConditions::GetIndicesOfBoundaryConditions(int dofsPerNode)
{
	std::vector<int>* dofIndices{ nullptr };
	dofIndices = new std::vector<int>();
	int index;
	for (size_t i = 0; i < nodeIDs->size(); i++)
	{
		if (dofTypes->at(i) == DOFX)
		{
			index = nodeIDs->at(i) * dofsPerNode;
		}
		else if (dofTypes->at(i) == DOFY)
		{
			index = nodeIDs->at(i) * dofsPerNode + 1;
		}
		else if (dofTypes->at(i) == DOFZ)
		{
			index = nodeIDs->at(i) * dofsPerNode + 2;
		}
		else if (dofTypes->at(i) == ROTX)
		{
			index = nodeIDs->at(i) * dofsPerNode + 3;
		}
		else if (dofTypes->at(i) == ROTY)
		{
			index = nodeIDs->at(i) * dofsPerNode + 4;
		}
		else if (dofTypes->at(i) == ROTZ)
		{
			index = nodeIDs->at(i) * dofsPerNode + 5;
		}
		else
		{
			throw std::invalid_argument("The DOF Type is not correct.");
		}
		dofIndices->push_back(index);
	}
	return dofIndices;
}

double NeumannBoundaryConditions::GetForceValue(int index)
{
	return amounts->at(index);
}
