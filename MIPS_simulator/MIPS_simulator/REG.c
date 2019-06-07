#include "MIPS.h"

extern char* stackMEM;
int* REGISTER;
int PC = 0x400000;
int SP = 0x80000000;

void setPC(unsigned int);

unsigned int REG(int A, int V, unsigned int nRW) {
	// A : register No.sd
	// V: write value
	// nRW: 0-> Read, 1-> Write
	if (nRW == 0) {
		if (A == s0) {
			//s0
			//V = stackMEM[0];
		}
		//read
		//if()
		V = *(REGISTER + (A * 4));
		// int니 4byte씩 증가
		return V;
	}
	else if (nRW == 1) {
		//write
		int temp_A = REG(A, 0, 0);
		// 이전 REG A 정보

		*(REGISTER + (A * 4)) = V;

		if (temp_A != REG(A, 0, 0)) {
			printf("\n레지스터 변경 R%d = %#x\n", A, REG(A, 0, 0));
		}
		return 0;
	}
	return 0;
}

void showRegister(void) {
	// 명령어 r
	printf("-------------[REGISTER]-------------\n");

	for (int i = 0; i < REG_SIZE; i++) {
		//printf("R%d = %d", i, REGISTER[i]);
		printf("R%d = %#x\n", i, REG(i, 0, 0));
	}
}

void setPC(unsigned int val) {
	PC = val;
	return;
}

int getPC() {
	return PC;
}

int getOp(int IR) {

	return fromBinary(substr(toBinary(IR), 0, 6));
}

int getFn(int IR) {

	return fromBinary(substr(toBinary(IR), 26, 6));
}

int getRs(int IR) {

	return fromBinary(substr(toBinary(IR), 6, 5));
}

int getRt(int IR) {
	return fromBinary(substr(toBinary(IR), 11, 5));
}

int getRd(int IR) {
	return fromBinary(substr(toBinary(IR), 16, 5));
}

int getOffset(int IR) {
	return fromBinary(substr(toBinary(IR), 16, 16));
}

int getJta(int IR) {
	return fromBinary(substr(toBinary(IR), 6, 26));
}

int getSh(int IR) {
	return fromBinary(substr(toBinary(IR), 21, 5));
}

int setSr(int argv1, int argv2) {
	REG(argv1, argv2, 1);

	return 0;
}