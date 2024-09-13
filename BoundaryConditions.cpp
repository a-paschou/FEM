#include "BoundaryConditions.h"

BoundaryConditions::BoundaryConditions(DirichletBoundaryConditions* dirichlet, NeumannBoundaryConditions* neumann)
	:dirichletBoundaryConditions(dirichlet), neumannBoundaryConditions(neumann)
{
}

DirichletBoundaryConditions* BoundaryConditions::GetDirichlet()
{
	return dirichletBoundaryConditions;
}

NeumannBoundaryConditions* BoundaryConditions::GetNeumann()
{
	return neumannBoundaryConditions;
}
