#pragma once
class Shape
{
public:
	Shape(const char* shape);
	Shape();
	~Shape();
	void rotateShape();
	int info[4][4];
	char type;
private:
	void copyMatrix(int a[4][4], const int b[4][4]);
	const int I[4][4] = {
		{0,1,0,0},
		{0,1,0,0},
		{0,1,0,0},
		{0,1,0,0}
	};
	const int L[4][4] = {
		{0,0,0,0},
		{0,2,0,0},
		{0,2,0,0},
		{0,2,2,0}
	};
	const int J[4][4] = {
		{0,0,0,0},
		{0,0,3,0},
		{0,0,3,0},
		{0,3,3,0}
	};
	const int O[4][4] = {
		{0,0,0,0},
		{0,4,4,0},
		{0,4,4,0},
		{0,0,0,0}
	};
	const int S[4][4] = {
		{0,0,0,0},
		{0,0,0,0},
		{0,5,5,0},
		{5,5,0,0}
	};
	const int T[4][4] = {
		{0,0,0,0},
		{0,0,0,0},
		{6,6,6,0},
		{0,6,0,0}
	};
	const int Z[4][4] = {
		{0,0,0,0},
		{0,0,0,0},
		{0,7,7,0},
		{0,0,7,7}
	};
};

