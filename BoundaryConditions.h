#pragma once
#include "DirichletBoundaryConditions.h"
#include "NeumannBoundaryConditions.h"
class BoundaryConditions
{
private:
	DirichletBoundaryConditions* dirichletBoundaryConditions;
	NeumannBoundaryConditions* neumannBoundaryConditions;
public:
	BoundaryConditions(DirichletBoundaryConditions*, NeumannBoundaryConditions*);
	DirichletBoundaryConditions* GetDirichlet();
	NeumannBoundaryConditions* GetNeumann();
};