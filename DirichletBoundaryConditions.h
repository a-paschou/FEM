#pragma once
#include "DOFType.h"
#include <vector>
class DirichletBoundaryConditions
{
private:
	std::vector<int>* nodeIDs;
	std::vector<DOFType>* dofTypes;
	std::vector<double>* amounts;
public:
	DirichletBoundaryConditions(std::vector<int>*, std::vector<DOFType>*, std::vector<double>*);
	std::vector<int>* GetIndicesOfBoundaryConditions(int);
};

