//Builds a Constant-Strain Triangle element.
#pragma once
#include "Element.h"
#include <vector>
#include "Node.h"
//#include "StressStrainRelation.h"
//#include "Material.cpp"
class CST : public Element
{
public:
	CST(int, int*);
	virtual std::vector<double>* CalculateStiffnessMatrix(std::vector<Node*>*, double) override final;
	//static void SetStressStrainRelations(Material*, StressStrainRelation);
	~CST();
};

