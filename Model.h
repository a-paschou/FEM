#pragma once
#include "Grid.h"
#include "Skyline.h"
#include "BoundaryConditions.h"
class Model
{
private:
	Grid* grid{ nullptr };
	BoundaryConditions* boundaryConditions;
	Matrix* stiffnessMatrix{ nullptr };
	std::vector<double>* forceVector{ nullptr };

	int FindNewDOFIndexWithBCs(int, std::vector<int>*);
	void BuildStiffnessMatrix();
	void BuildForceVector();
protected:
	std::vector<double>* rhs;
public:
	Model(Grid*);
	Model(Grid*, BoundaryConditions*);
	Matrix* GetLeftHandSide();
	std::vector<double>* GetRightHandSide();

};