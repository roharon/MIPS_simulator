#include "MIPS.h"

int* REGISTER;
int PC = 0x400000;
int SP = 0x80000000;

void setPC(unsigned int);

unsigned int REG(unsigned int A, unsigned int V, unsigned int nRW) {
	// A : memory address
	// V: write value
	// nRW: 0-> Read, 1-> Write
	//S(Size): 0-> Byte, 1-> Half word, 2-> Word

	if (nRW == 0) {
		//read
		V = *(REGISTER + (A * 4));
		// int니 4byte씩 증가
		return V;
	}
	else if (nRW == 1) {
		//write
		*(REGISTER + (A * 4)) = V;
		return 0;
	}


}

void showRegister(void) {
	printf("[REGISTER]\n");

	for (int i = 0; i < REG_SIZE; i++) {
		printf("R%d = %d", i, REGISTER[i]);
	}
}

void setPC(unsigned int val) {
	PC = val;
	return;
}

int getPC() {
	return PC;
}