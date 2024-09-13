#include "Element.h"

Element::Element(int elementID, int* nodesIDs, int nNodes)
	:elementID(elementID), nodesIDs(nullptr), nNodes(nNodes)
{
	this->nodesIDs = new int[nNodes];
	for (size_t i = 0; i < nNodes; i++)
	{
		this->nodesIDs[i] = *(nodesIDs + i);
	}
}

int Element::GetNodeID(int pos)
{
	return nodesIDs[pos];
}

int Element::GetNumberOfNodes()
{
	return nNodes;
}

void Element::SetStressStrainRelations(Material* material, StressStrainRelation relation)
{
	double factor{};
	D = new double[9];
	switch (relation)
	{
	case StressStrainRelation::PlaneStress:
	{
		factor = material->elasticModulus / (1 - pow(material->poissonRatio, 2));
		D[0] = 1 * factor;
		D[1] = material->poissonRatio * factor;
		D[2] = 0;
		D[3] = material->poissonRatio * factor;
		D[4] = 1 * factor;
		D[5] = 0;
		D[6] = 0;
		D[7] = 0;
		D[8] = ((1 - material->poissonRatio) / 2) * factor;
		break;
	}
	case StressStrainRelation::PlaneStain:
	{
		factor = material->elasticModulus / ((1 + material->poissonRatio) * (1 - 2 * material->poissonRatio));
		D[0] = (1 - material->poissonRatio) * factor;
		D[1] = material->poissonRatio * factor;
		D[2] = 0;
		D[3] = material->poissonRatio * factor;
		D[4] = (1 - material->poissonRatio) * factor;
		D[5] = 0;
		D[6] = 0;
		D[7] = 0;
		D[8] = ((1 - material->poissonRatio) / 2) * factor;
		break;
	}
	default:
		break;
	}
}

Element::~Element()
{
	delete[] D;
	delete[] nodesIDs;
}

void Element::SetThickness(double thickness)
{
	Element::thickness = thickness;
}

double Element::GetThickness()
{
	return thickness;
}

int Element::GetNumberOfDOFsPerNode()
{
	return nDOFsPerNode;
}
