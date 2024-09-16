#include "Model.h"
#include <iostream>
int Model::FindNewDOFIndexWithBCs(int index, std::vector<int>* indicesBCs)
{
	int initialIndex{ index };
	for (size_t i = 0; i < indicesBCs->size(); i++)
	{
		if (indicesBCs->at(i) <= initialIndex)
		{
			index--;
		}
	}
	return index;
}

Model::Model(Grid* grid, BoundaryConditions* boundaryConditions)
	:grid(grid), boundaryConditions(boundaryConditions)
{
	BuildStiffnessMatrix();
	BuildForceVector();
}

Matrix* Model::GetLeftHandSide()
{
	return stiffnessMatrix;
}

std::vector<double>* Model::GetRightHandSide()
{
	return forceVector;
}

void Model::BuildStiffnessMatrix()
{
	DirichletBoundaryConditions* dirichlet{ boundaryConditions->GetDirichlet() };
	std::vector<int> dirichletDOFsIndices{};
	dirichletDOFsIndices = *dirichlet->GetIndicesOfBoundaryConditions(Element::GetNumberOfDOFsPerNode());

	int nDOFsPerNode{ Element::GetNumberOfDOFsPerNode() };
	int dimension{ ((int)grid->nodesMap.size() * nDOFsPerNode) };
	dimension -= dirichletDOFsIndices.size();
	std::vector<double> stiffnessMatrix(dimension * dimension);
	std::vector<double> elementStiffnessMatrix;
	int* indices{ nullptr };
	for (std::pair<const int, Element*> &element : grid->elementsMap)
	{
		int nNodes{ element.second->GetNumberOfNodes() };
		indices = new int[nNodes * nDOFsPerNode];
		std::vector<Node*> elementsNodes;
		for (size_t i = 0; i < nNodes; i++)
		{
			elementsNodes.push_back(grid->nodesMap.find(element.second->GetNodeID(i))->second);
		}
		elementStiffnessMatrix = *element.second->CalculateStiffnessMatrix(&elementsNodes, element.second->GetThickness());
		int nodeID{};
		for (size_t i = 0; i < nNodes; i++)
		{
			nodeID = element.second->GetNodeID(i);
			for (size_t j = 0; j < nDOFsPerNode; j++)
			{
				indices[i * nDOFsPerNode + j] = nodeID * nDOFsPerNode + j;
			}
		}

		int indx1{};
		int indx2{};
		for (size_t i = 0; i < nNodes * nDOFsPerNode; i++)
		{
			indx1 = indices[i];
			if (std::find(dirichletDOFsIndices.begin(), dirichletDOFsIndices.end(), indx1) != dirichletDOFsIndices.end())
			{
				continue;
			}
			indx1 = FindNewDOFIndexWithBCs(indx1, &dirichletDOFsIndices);
			for (size_t j = 0; j < nNodes * nDOFsPerNode; j++)
			{
				indx2 = indices[j];
				if (std::find(dirichletDOFsIndices.begin(), dirichletDOFsIndices.end(), indx2) != dirichletDOFsIndices.end())
				{
					continue;
				}		
				indx2 = FindNewDOFIndexWithBCs(indx2, &dirichletDOFsIndices);
				stiffnessMatrix.at(indx1 * dimension + indx2) += elementStiffnessMatrix.at(i * nNodes * nDOFsPerNode + j);
			}
		}
	}

	delete[] indices;
	this->stiffnessMatrix = new Skyline(dimension, dimension, &stiffnessMatrix);
}

void Model::BuildForceVector()
{
	NeumannBoundaryConditions* neumann{ boundaryConditions->GetNeumann() };
	std::vector<int> neumannDOFsIndices{};
	neumannDOFsIndices = *neumann->GetIndicesOfBoundaryConditions(Element::GetNumberOfDOFsPerNode());

	DirichletBoundaryConditions* dirichlet{ boundaryConditions->GetDirichlet() };
	std::vector<int> dirichletDOFsIndices{};
	dirichletDOFsIndices = *dirichlet->GetIndicesOfBoundaryConditions(Element::GetNumberOfDOFsPerNode());

	int nDOFsPerNode{ Element::GetNumberOfDOFsPerNode() };
	int dimension{ ((int)grid->nodesMap.size() * nDOFsPerNode) };
	int dimensionReduction{ (int)dirichletDOFsIndices.size() };
	dimension -= dimensionReduction;
	
	forceVector = new std::vector<double>(dimension, 0);
	int indx{};
	for (size_t i = 0; i < neumannDOFsIndices.size(); i++)
	{
		indx = neumannDOFsIndices.at(i);
		if (std::find(dirichletDOFsIndices.begin(), dirichletDOFsIndices.end(), indx) != dirichletDOFsIndices.end())
		{
			continue;
		}
		indx = FindNewDOFIndexWithBCs(indx, &dirichletDOFsIndices);
		forceVector->at(indx) = neumann->GetForceValue(i);
	}
}
