#include "MIPS.h"

//#include "Hash.h"

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

int PC = 0x400000;
int SP = 0x80000000;
unsigned char progMEM[0x100000], dataMEM[0x100000], stackMEM[0x100000];
int* REGISTER;
// 레지스터 저장공간
char cmd[50] = "";
char user_cmd = ' ';
// 유저커맨드 저장공간

int main() {
	bin_read();
	//bin_read();
	FILE *fpointer;
	REGISTER = (int*)calloc(32, sizeof(int));

	while (1) {

		scanf("%[^\n]", cmd);
		user_cmd = cmd[0];

		switch (user_cmd) {
		case 'l':
			fpointer = fopen("a", "r");
			if (fpointer == NULL) {
				printf("Error opening file");
			}
			//setPC(0x400000);

			break;
		case 'j':
			break;
		case 'g':
			break;
		case 's':
			break;
		case 'm':
			break;
		case 'r':
			break;
		case 'x':
			break;

		}
		getchar();
		//버퍼헤결
	}







	free(REGISTER);
}