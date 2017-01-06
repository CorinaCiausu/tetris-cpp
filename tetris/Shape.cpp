#include "Shape.h"

Shape::Shape(const char* shape)
{
	type = shape[0];
	switch (type)
	{
	case 'I':
		copyMatrix(info, I);
		break;
	case 'L':
		copyMatrix(info, L);
		break;
	case 'J':
		copyMatrix(info, J);
		break;
	case 'O':
		copyMatrix(info, O);
		break;
	case 'S':
		copyMatrix(info, S);
		break;
	case 'T':
		copyMatrix(info, T);
		break;
	case 'Z':
		copyMatrix(info, Z);
		break;
	default:
		break;
	}
}

void Shape::copyMatrix(int a[4][4], const int b[4][4])
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			a[i][j] = b[i][j];
}

Shape::Shape()
{
}


Shape::~Shape()
{
}
