#include "MIPS.h"

int ALU(int X, int Y, int C, int *Z) {
	int c32, c10;
	int ret;

	c32 = (C >> 2) & 3;
	c10 = C & 3;
	if (c32 == 0) { // shift        
		ret = shiftOperation(X, Y, c10);
	}
	else if (c32 == 1) {  // set less   
		ret = checkSetLess(X, Y);
	}
	else if (c32 == 2) {  // add | subtract
		*Z = checkZero(c10 & 1);
		ret = addSubtract(X, Y, *Z);
	}
	else {
		ret = logicOperation(X, Y, c10);
	}
	return ret;
}

int logicOperation(int X, int Y, int C)
{
	//C32 ==2

	if (C < 0 || C > 3) {
		printf("error in logic operation\n");
		exit(1);
	}
	if (C == 0)
		// AND
		return X & Y;
	else if (C == 1)
		// OR
		return X | Y;
	else if (C == 2)
		// XOR
		return X ^ Y;
	else
		// NOR
		return !(X | Y);
}

int addSubtract(int X, int Y, int C) {
	int ret;
	if (C < 0 || C > 1)
	{
		printf("error in add / subract operation\n");
		exit(1);
	}
	if (C == 0) {
		//add
		ret = X + Y;
	}
	else {
		//subtract
		ret = X - Y;
	}
	return ret;
}

// V is 5bit shift amount
int shiftOperation(int V, int Y, int C) {
	// C32 == 11

	int ret;
	if (C < 0 || C > 3) {
		printf("error in shift operation\n");
		exit(1);
	}
	if (C == 0) {
		// No shift
		ret = V;
	}
	else if (C == 1) {
		// Shift left logical
		ret = V << Y;
	}
	else if (C == 2) {
		// Shift right logical
		ret = (V >> Y) & ~(((0x1 << sizeof(V)) >> Y) << 1);
	}
	else {
		// Shift right artihmetic
		ret = V >> Y;
	}
	return ret;
}

// 이 함수는 add 또는 subtract 수행 시만 
// 사용하여 Z 값을 설정한다.
int checkZero(int S) {
	int ret;

	// check if S is zero,
	//  and return 1 if it is zero
	//  else return 0
	if (S == 0) {
		ret = 1;
	}
	else {
		ret = 0;
	}
	return ret;
}

int checkSetLess(int X, int Y) {
	int ret;

	// check if X < Y,
	//  and return 1 if it is true
	//  else return 0
	if (X < Y)
		ret = 1;
	else
		ret = 0;
	return ret;
}

void step(void) {

}