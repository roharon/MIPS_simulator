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

extern int* REGISTER;
extern int PC;
extern int SP;
char cmd[50] = "";
char user_cmd = ' ';

int main(int argc, char* argv[]) {
	bin_read();
	FILE *fpointer;
	REGISTER = (int*)calloc(32, sizeof(int));

	while (1) {
		scanf("%[^\n]", cmd);
		user_cmd = cmd[0];

		switch (user_cmd) {
		case 'l':
			if (argc == 1)
				fpointer = fopen("C:/roharon98/HUFS/Computer_structure/report3/machine_example/as_ex04_fct.bin", "r");
			else
				fpointer = fopen(argv[1], "r");
			
			if (fpointer == NULL) {
				printf("Error opening file");
			}

			PC = 0x400000;
			setPC(0x400000);

			// ! 시뮬레이터 메모리에 올리기 !
			// l할떄는 bin을 받아야함.
			// 그럼 어셈블리로 바꾸고 같이 처리할까

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
			return 0;
			break;

		}
		getchar();
		//버퍼헤결
	}







	free(REGISTER);
}