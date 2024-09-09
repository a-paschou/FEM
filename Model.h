#pragma once
#include "Matrix.h"

class Model
{
protected:
	Matrix* lhs;
	std::vector<double>* rhs;
public:
	Model(Matrix*, std::vector<double>*);
	Matrix* GetLeftHandSide();
	std::vector<double>* GetRightHandSide();
};

