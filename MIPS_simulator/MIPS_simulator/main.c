#include "MIPS.h"

/*
Program counter는 동일하게 구현

MIPS명령어
add $t0, $t0, $t2

하면 결과 나오게

레지스터 공간 구현해야한다.

ALU
*/

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
	FILE *fpointer = NULL;
	REGISTER = (int*)calloc(32, sizeof(int));
	REGISTER[sp] = stackMEM;
	// sp레지스터 stackMEM에 연결

	char var1[10] = "";
	char var2[10] = "";

	errno_t err = 0;
	while (1) {
		printf("enter the command : ");
		scanf("%[^\n]", cmd);
		fflush(stdin);
		user_cmd = cmd[0];

		switch (user_cmd) {

		case '-':
			bin_read(0,0);
			break;

		case 'l':
			printf("enter the File Name : ");
			scanf("%s", cmd);
			
			//result_temp = bin_read(cmd);
			err = fopen_s(&fpointer, cmd, "rb");
			if (err) {
				printf("\n==CAN NOT OPEN FILE ==\nfile name = %s\n", cmd);
				break;
			}
			strcpy(PATH, cmd);
			PC = 0x400000;
			setPC(0x400000);
			break;

		case 'j':			
			scanf("%x", &target_address);
			break;

		case 'g':
			bin_read(0, 0);
			// 현재 PC위치에서 시뮬레이터가 명령어 끝까지 처리
			break;

		case 's':
			bin_read(1, 0);
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