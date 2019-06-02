#include "MIPS.h"

// MEM에 binary code 내용을 넣는 함수
extern int PC;

int LoadBin(char* PATH) {
	PATH = "C:/roharon98/HUFS/Computer_structure/report3/machine_example/as_ex01_arith.bin";

	// PATH의 bin파일을 로드
	FILE *fpointer = NULL;
	errno_t err = 0;
	unsigned char data;
	int ind = 0;
	//MEM 저장 전에 횟수 세는 인덱스
	unsigned int put_data;
	//MEM에 넣기 전, 4개씩 묶어 저장할때

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
			//binary에서 개수부분 빼고
		}
		// 인덱스 하나씩 저장

		
		ind++;
	}


	fclose(fpointer);
	return 0;
}

//bin 파일
// 00~03까지 