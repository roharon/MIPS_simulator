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
extern char PATH[];
extern int* REGISTER;
extern int PC;
extern int SP;
char cmd[50] = "";
char user_cmd = ' ';

int main(int argc, char* argv[]) {
	//bin_read();
	FILE *fpointer = NULL;
	REGISTER = (int*)calloc(32, sizeof(int));
	errno_t err = 0;
	int target_address = 0;
	while (1) {
		printf("enter the command : ");
		scanf("%[^\n]", cmd);
		user_cmd = cmd[0];

		switch (user_cmd) {

		case '-':
			bin_read();
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
			//fpointer = fopen("C:/roharon98/HUFS/Computer_structure/report3/machine_example/as_ex04_fct.bin", "r");
			break;

		case 'j':
			scanf("%x", &target_address);
			if (fpointer != NULL)
				bin_read(fpointer, target_address, 1);
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
			printf("Bye!");
			return 0;
			break;

		}
		getchar();
		//버퍼헤결
	}







	free(REGISTER);
}