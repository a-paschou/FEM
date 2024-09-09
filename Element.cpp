#include "Element.h"

Element::Element(int elementID, int* nodesIDs)
	:elementID(elementID), nodesIDs(nodesIDs)
{
}

int Element::GetNodeID(int pos)
{
	return nodesIDs[pos];
}
