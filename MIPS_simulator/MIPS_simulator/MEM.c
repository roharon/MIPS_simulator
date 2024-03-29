#include "MIPS.h"

// A : memory address
// V: write value
// nRW: 0-> Read, 1-> Write
//S(Size): 0-> Byte, 1-> Half word, 2-> Word
//Program 1MiB, Data(static, dynamic data) 1Mib, Stack: 1Mib
// 3 static char arrays of 1Mib internally.
// MEM함수 호출하면 주소변환 통해 각 메모리 접근
// 읽기에는 V 의미없고 반환값 받음
// 쓰기에는 반환값이 의미없다

unsigned char progMEM[0x100000], dataMEM[0x100000], stackMEM[0x100000];

unsigned int MEM(unsigned int A, int V, int nRW, int S) {
	// S : 0 byte | S : 1 half word | S : 2 word
	// nRW : 0 -> Read, 1 -> Write

	//s0
	// 800 00000
	unsigned int sel, offset;
	unsigned char *pM;
	sel = A >> 20;    offset = A & 0xFFFFF;
	// 메모리 주소 크기에 따라 접근하는 MEM을 변경시킨다
	if (sel == 0x004) pM = progMEM;         // program memory
	else if (sel == 0x100) pM = dataMEM;  // data memory
	else if (sel == 0x800) pM = stackMEM;  // stack
	else {
		printf("No memory\n");
		return 1;
	}
	//printf("%x %x", sel,offset);
	if (S == 0) {  // byte
		if (nRW == 0) {
			//read
			V = *(pM + offset);
			//printf("\n V is %x\n", V);
			return V;
		}
		else if (nRW == 1) {
			//write
			*(pM + offset) = V;
			//printf("\n*(pM+offset) is %d\n", *(pM + offset));
			return 0;
		}

	}
	else if (S == 1) { // half word
		if (nRW == 0) { // read
			//V = *(pM + offset) + *(pM + offset + 1);
			// 4byte면 2^4 씩 쉬프트연산으로 쪼개어 저장하자.
			V = (*(pM + offset) << 8) + *(pM + offset + 1);
			return V;
		}
		else if (nRW == 1) { // write
			*(pM + offset) = V >> 8;
			*(pM + offset + 1) = V & 0xFF;

			return 0;
		}
	}
	else if (S == 2) { // word
		if (nRW == 0) {
			V = (*(pM + offset) << 24) + (*(pM + offset + 1) << 16) + \
				(*(pM + offset + 2) << 8) + (*(pM + offset + 3));
			return V;
		}
		else if (nRW == 1) {
			*(pM + offset) = V >> 24;
			*(pM + offset + 1) = (V >> 16) & 0xFF;
			*(pM + offset + 2) = (V >> 8) & 0xFF;
			*(pM + offset + 3) = V & 0xFF;

			return 0;
		}

	}
	else {
		printf("No Size!\n");
		return 1;
	}
	return 5;
}

int setSm(unsigned int argv1, int argv2) {

	int result_MEM = MEM(argv1, argv2, 1, 2);
	// 0이면 성공
	
	if ((result_MEM == 1) || (result_MEM==5)) {
		// No size , other error
		return 1;
	}
	else if (result_MEM == 0) {
		return 0;
	}
}

int printMemory(unsigned int argv1, unsigned int argv2) {
	// 0이면 성공, 실패시 return 1
	for (unsigned int i = argv1; i <= argv2; i += 4) {
		int result_MEM = MEM(i, 0, 0, 2);
		if (result_MEM == 1) {
			return 1;
		}
		else {
			printf("메모리 %#x = %d\n", i, result_MEM);
		}
	}
}

/*
nRW : 0 -> Read, 1 -> Write
S(size) : 0 -> Byte, 1 -> Half word, 2 -> Word

Word : 4byte, halfword : 2byte, byte : 1byte
*/