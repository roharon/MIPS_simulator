#include "MIPS.h"

// MEM에 binary code 내용을 넣는 함수
extern int PC;

int LoadBin(char* PATH) {
	//PATH = "C:/roharon98/HUFS/Computer_structure/report3/machine_example/as_ex02_logic.bin";
	// 임시 경로. 제출 전 삭제


	// PATH의 bin파일을 로드
	FILE *fpointer = NULL;
	errno_t err = 0;
	unsigned char data;
	int ind = 0;
	//MEM 저장 전에 횟수 세는 인덱스
	unsigned int put_data;
	//MEM에 넣기 전, 4개씩 묶어 저장할때

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
			//binary에서 개수부분 빼고
		}

		
		ind++;
	}


	fclose(fpointer);
	return 0;
}