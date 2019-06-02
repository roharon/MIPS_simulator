#include "MIPS.h"

int* REGISTER;
int PC = 0x400000;
int SP = 0x80000000;

void setPC(unsigned int);

unsigned int REG(unsigned int A, unsigned int V, unsigned int nRW) {
	// A : memory address
	// V: write value
	// nRW: 0-> Read, 1-> Write

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
	// 명령어 r
	printf("-------------[REGISTER]-------------\n");

	for (int i = 0; i < REG_SIZE; i++) {
		//printf("R%d = %d", i, REGISTER[i]);
		printf("R%d = %d\n", i, REG(i, 0, 0));
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
	char get_result[20] = "";
	*get_result = toBinary(IR);	
	*get_result = substr(get_result, 0, 6);

	return fromBinary(get_result);
}

int getFn(int IR) {
	char get_result[20] = "";
	*get_result = toBinary(IR);
	*get_result = substr(get_result, 26, 6);

	return fromBinary(get_result);
}

int getRs(int IR) {
	char get_result[20] = "";
	*get_result = toBinary(IR);
	*get_result = substr(get_result, 6, 5);

	return fromBinary(get_result);
}

int getRt(int IR) {
	char get_result[20] = "";
	*get_result = toBinary(IR);
	*get_result = substr(get_result, 11, 5);

	return fromBinary(get_result);
}

int getRd(int IR) {
	char get_result[20] = "";
	*get_result = toBinary(IR);
	*get_result = substr(get_result, 16, 5);

	return fromBinary(get_result);
}

int getOffset(int IR) {
	char get_result[20] = "";
	*get_result = toBinary(IR);
	*get_result = substr(get_result, 16, 16);

	return fromBinary(get_result);
}

int getJta(int IR) {
	char get_result[20] = "";
	*get_result = toBinary(IR);
	*get_result = substr(get_result, 6, 26);

	return fromBinary(get_result);
}