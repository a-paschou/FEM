#include "CST.h"
#include <format>

CST::CST(int elementID, int* nodesIDs)
	: Element(elementID, nodesIDs, 3)
{
	nDOFsPerNode = 2;
}

std::vector<double>* CST::CalculateStiffnessMatrix(std::vector<Node*>* nodes, double thickness)
{
	std::vector<double>* stiffnessMatrix{ nullptr };
	stiffnessMatrix = new std::vector<double>();
	double x12{};
	double y12{};
	double x13{};
	double y13{};
	double x23{};
	double y23{};

	x12 = nodes->at(0)->GetX() - nodes->at(1)->GetX();
	y12 = nodes->at(0)->GetY() - nodes->at(1)->GetY();
	x13 = nodes->at(0)->GetX() - nodes->at(2)->GetX();
	y13 = nodes->at(0)->GetY() - nodes->at(2)->GetY();
	x23 = nodes->at(1)->GetX() - nodes->at(2)->GetX();
	y23 = nodes->at(1)->GetY() - nodes->at(2)->GetY();

	double jacobian[4]{ x13, y13, x23, y23 };
	double detJacobian{ x13 * y23 - x23 * y13 };
	double area{ 0.5 * abs(detJacobian) };

	double B[3][6]{
		{y23 / detJacobian, 0, -y13 / detJacobian, 0, y12 / detJacobian, 0},
		{0, -x23 / detJacobian, 0, x13 / detJacobian, 0, -x12 / detJacobian},
		{-x23 / detJacobian, y23 / detJacobian, x13 / detJacobian, -y13 / detJacobian, -x12 / detJacobian, y12 / detJacobian} };

	//std::vector<double> stiffnessMatrix;
	double subMatrix[3][6];

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 6; j++)
		{
			double sum{ 0 };
			for (size_t k = 0; k < 3; k++)
			{
				sum += D[i * 3 + k] * B[k][j];
			}
			subMatrix[i][j] = sum;
		}
	}

	for (size_t i = 0; i < 6; i++)
	{
		for (size_t j = 0; j < 6; j++)
		{
			double sum{ 0 };
			for (size_t k = 0; k < 3; k++)
			{
				sum += B[k][i] * subMatrix[k][j];
			}
			stiffnessMatrix->push_back(area * thickness * sum);
		}
	}
	return stiffnessMatrix;
}

CST::~CST()
{
}

//void CST::SetStressStrainRelations(Material* material, StressStrainRelation relation)
//{
//	double factor{};
//	switch (relation)
//	{
//	case StressStrainRelation::PlaneStress:
//	{
//		factor = material->elasticModulus / (1 - pow(material->poissonRatio, 2));
//		D[0][0] = 1 * factor;
//		D[0][1] = material->poissonRatio * factor;
//		D[0][2] = 0;
//		D[1][0] = material->poissonRatio * factor;
//		D[1][1] = 1 * factor;
//		D[1][2] = 0;
//		D[2][0] = 0;
//		D[2][1] = 0;
//		D[2][2] = ((1 - material->poissonRatio) / 2) * factor;
//		break;
//	}
//	case StressStrainRelation::PlaneStain:
//	{
//		factor = material->elasticModulus / ((1 + material->poissonRatio) * (1 - 2 * material->poissonRatio));
//		D[0][0] = (1 - material->poissonRatio) * factor;
//		D[0][1] = material->poissonRatio * factor;
//		D[0][2] = 0;
//		D[1][0] = material->poissonRatio * factor;
//		D[1][1] = (1 - material->poissonRatio) * factor;
//		D[1][2] = 0;
//		D[2][0] = 0;
//		D[2][1] = 0;
//		D[2][2] = ((1 - material->poissonRatio) / 2) * factor;
//		break;
//	}
//	default:
//		break;
//	}
//}
