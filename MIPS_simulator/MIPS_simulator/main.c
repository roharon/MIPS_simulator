#include "MIPS.h"
//#include "Hash.h"

/*
Program counter�� �����ϰ� ����

MIPS��ɾ�
add $t0, $t0, $t2

�ϸ� ��� ������

�������� ���� �����ؾ��Ѵ�.

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

int main() {
	
	FILE *fpointer;
	REGISTER = (int*)calloc(32, sizeof(int));

	while (1) {
		
		scanf("%[^\n]", cmd);
		user_cmd = cmd[0];

		switch (user_cmd) {
			case 'l':
				fpointer = fopen(cmd[2], "r");
				if (fpointer == NULL) {
					printf("Error opening file");
				}
				setPC(0x400000);


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
	}







	free(REGISTER);
}