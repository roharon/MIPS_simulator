#include <stdio.h>
#include "MIPS.h"

int ALU(int C, int X, int Y) {
	// C : opcode | X : 피연산1 | Y : 피연산2
	// 계산된 값을 반환한다.

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
		ret = addSubtract(X, Y, checkZero(c10 & 1));
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
		return ~(X | Y);
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
		//printf("\n sll : ret %x <- %x %x \n", ret, V, Y);

	}
	else if (C == 2) {
		// Shift right logical
		//ret = (V >> Y) & ~(((0x1 << (sizeof(int)*8)) >> Y) << 1);
		int mask = ~(-1 << Y) << (32 - Y);
		ret = ~mask & ((V >> Y) | mask);
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

void test(void) {
	int x, y, c, s, z;

	x = 2;
	y = 1;

	printf("x: % 8x, y : % 8x\n", x, y);
	for (int i = 0; i < 16; i++) {
		s = ALU(x, y, i, &z);
		printf("s: % 8x, z : % 8x\n", s, z);
	}
}
