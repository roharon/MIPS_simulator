#include "MIPS.h"

unsigned int REG(unsigned int A, unsigned int V, unsigned int nRW) {
	
}

void showRegister(void) {
	int i;
	printf("[REGISTER]\n");
	
	for (int i = 0; i < REG_SIZE; i++) {
		printf("R%d = %d", i, REGISTER[i]);
	}
}

void setPC(unsigned int val) {
	PC = val;
	return;
}