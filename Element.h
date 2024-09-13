#pragma once
#include "Material.cpp"
#include <vector>
#include "Node.h"
#include "StressStrainRelation.h"
class Element
{
protected:
	int elementID;
	int* nodesIDs{ nullptr };
	int nNodes;
	Material* material;
	inline static double* D;
	inline static double thickness;
	inline static int nDOFsPerNode;
public:
	Element(int, int*, int);
	virtual std::vector<double>* CalculateStiffnessMatrix(std::vector<Node*>*, double) = 0;
	int GetNodeID(int);
	int GetNumberOfNodes();
	static void SetStressStrainRelations(Material*, StressStrainRelation);
	~Element();
	static void SetThickness(double);
	double GetThickness();
	static int GetNumberOfDOFsPerNode();
};