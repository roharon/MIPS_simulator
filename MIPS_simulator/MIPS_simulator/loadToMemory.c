#include "MIPS.h"

// MEM�� binary code ������ �ִ� �Լ�
extern int PC;

int LoadBin(char* PATH) {
	PATH = "C:/roharon98/HUFS/Computer_structure/report3/machine_example/as_ex01_arith.bin";

	// PATH�� bin������ �ε�
	FILE *fpointer = NULL;
	errno_t err = 0;
	unsigned char data;
	int ind = 0;
	//MEM ���� ���� Ƚ�� ���� �ε���
	unsigned int put_data;
	//MEM�� �ֱ� ��, 4���� ���� �����Ҷ�

	printf("aaaa");
	err = fopen_s(&fpointer, PATH, "rb");
	if (err) {
		printf("\n====== CAN NOT OPEN FILE =====\n%s \n", PATH);
		return 500;
	}
	printf("read works\n");

	while(1 == fread(&data, 1, 1, fpointer)) {
		/*
		if ((ind % 4 == 0) && (ind >= 4))
			put_data = data;
		else if (((ind - 1) % 4) == 0 && (ind >= 4))
			put_data = (put_data * 16) + data;
		else if (((ind - 2) % 4) == 0 && (ind >= 4))
			put_data = (put_data * 16) + data;
		else if (((ind-3) % 4 == 0) && (ind >= 4)) {
			put_data = (put_data * 16) + data;
			MEM(0x00400000 + (4 * ind), data, 1, 0);
		}
		*/
		if (ind >= 8) {
			MEM(0x00400000 + (ind-8), data, 1, 0);
			printf("%x\n", data);
			//binary���� �����κ� ����
		}
		// �ε��� �ϳ��� ����

		
		ind++;
	}


	fclose(fpointer);
	return 0;
}

//bin ����
// 00~03���� 