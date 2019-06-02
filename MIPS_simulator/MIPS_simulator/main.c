#include "MIPS.h"

/*
$zero  0
$v0~$v1 2~3
$a0~$a3 4~7
$t0 ~ $t7 8~15
$s0~$s7 16~23
$t8~$t9 24~25
$gp 28
$sp 29
$fp 30
$ra 31
*/
extern stackMEM;
extern char PATH[];
extern int* REGISTER;
extern int PC;
extern int SP;

int target_address = 0;
int STEP = 0;
char cmd[50] = "";
char* result;
char user_cmd = ' ';

int main(int argc, char* argv[]) {
	REGISTER = (int*)calloc(32, sizeof(int));
	REGISTER[sp] = stackMEM;
	// sp레지스터 stackMEM에 연결

	char var1[10] = "";
	char var2[10] = "";

	while (1) {
		printf("enter the command : ");
		scanf("%[^\n]", cmd);
		fflush(stdin);
		user_cmd = cmd[0];

		switch (user_cmd) {

		case '-':
			printf("%x\n", MEM(0x00400000, 1, 0, 2));
			printf("%x\n", MEM(0x00400000 + 4, 1, 0, 2));
			printf("%x\n", MEM(0x00400000 + 8, 1, 0, 2));
			printf("%x\n", MEM(0x00400000 + 12, 1, 0, 2));
			// 테스트용
			break;

		case 'l':
			printf("enter the File Name : ");
			scanf("%s", cmd);
			// TODO 메모리에 올리기

			//result_temp = bin_read(cmd);

			result = LoadBin(cmd);
			if (result == 500) {
				
			}

			break;

		case 'j':			
			scanf("%x", &target_address);
			break;

		case 'g':
			// 현재 PC위치에서 시뮬레이터가 명령어 끝까지 처리
			break;

		case 's':
			break;

		case 'm':
			// m <start> <end>
			break;

		case 'r':
			showRegister();
			break;

		case 'x':
			printf("Bye!");
			return 0;
			break;
		}
		//sr명령어
		//sm명령어

		getchar();
		//엔터 버퍼 비우기
	}


	free(REGISTER);
}