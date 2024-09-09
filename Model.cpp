#include "Model.h"

Model::Model(Matrix* lhs, std::vector<double>* rhs)
	: lhs{ lhs }, rhs{ rhs }
{
}

Matrix* Model::GetLeftHandSide()
{
	return lhs;
}

std::vector<double>* Model::GetRightHandSide()
{
	return rhs;
}
