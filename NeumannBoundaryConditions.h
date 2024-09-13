#pragma once
#include <vector>
#include "DOFType.h"
class NeumannBoundaryConditions
{
	std::vector<int>* nodeIDs;
	std::vector<DOFType>* dofTypes;
	std::vector<double>* amounts;
public:
	NeumannBoundaryConditions(std::vector<int>*, std::vector<DOFType>*, std::vector<double>*);
	std::vector<int>* GetIndicesOfBoundaryConditions(int);
	double GetForceValue(int);
};

