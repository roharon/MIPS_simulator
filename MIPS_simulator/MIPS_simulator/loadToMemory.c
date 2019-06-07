#include "MIPS.h"

// MEM�� binary code ������ �ִ� �Լ�
extern int PC;

int LoadBin(char* PATH) {
	//PATH = "C:/roharon98/HUFS/Computer_structure/report3/machine_example/as_ex02_logic.bin";
	// �ӽ� ���. ���� �� ����


	// PATH�� bin������ �ε�
	FILE *fpointer = NULL;
	errno_t err = 0;
	unsigned char data;
	int ind = 0;
	//MEM ���� ���� Ƚ�� ���� �ε���
	unsigned int put_data;
	//MEM�� �ֱ� ��, 4���� ���� �����Ҷ�

	err = fopen_s(&fpointer, PATH, "rb");


	if (err) {
		printf("\n====== CAN NOT OPEN FILE =====\n%s \n", PATH);
		return 400;
	}

	// set PC

	setPC(0x00400000);

	while(1 == fread(&data, 1, 1, fpointer)) {

		if (ind >= 8) {
			MEM(0x00400000 + (ind-8), data, 1, 0);
			//printf("\n%x and MEM is %x\n", data, MEM(0x00400000 + (ind - 8), data, 0, 0));
			//binary���� �����κ� ����
		}

		
		ind++;
	}


	fclose(fpointer);
	return 0;
}