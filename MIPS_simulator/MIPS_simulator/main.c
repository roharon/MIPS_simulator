#include "MIPS.h"

extern stackMEM;
extern char PATH[];
extern int* REGISTER;
extern int PC;
extern int SP;
extern int break_point;

int target_address = 0;
int STEP = 0;
char cmd[30] = "";
char argv1[30] = "";
char argv2[30] = "";

char* result;
char user_cmd = ' ';

int main(int argc, char* argv[]) {
	alloc_REG();
	// �������� �Ҵ�

	char var1[10] = "";
	char var2[10] = "";

	int did_load = 0;

	unsigned int temp_argv1;
	int temp_argv2;


	while (1) {
		printf("----------------------\n");
		printf("enter the command : ");
		scanf("%s", cmd);
		//scanf("%[^\n]", cmd);
		fflush(stdin);

		if (((!did_load) && (!EQUAL(cmd, "l")))) {
			if (EQUAL(cmd, "x"))
				break;

			printf("���� binary������ �ε����ּ���\n");
			continue;
		}

		if (!strcmp(cmd, "sr")) {
			scanf("%s", argv1);
			scanf("%s", argv2);

			temp_argv1 = atoi(argv1);
			temp_argv2 = (unsigned int)strtoul(argv2, NULL, 16);
			// atoi ���н� 0��ȯ

			if (!temp_argv2) {
				// ��ȯ���н�
				printf("== sr ��ɾ� ���ڰ� �߸��Ǿ����ϴ�. �ٽ� �Է����ּ��� ==\n");

			}
			else if ((temp_argv1 > 31) || (temp_argv1 < 0)) {
				// �������� ������ �Ѿ�����
				printf("== �������� ������ �ùٸ��� �ʽ��ϴ�. �ٽ� �Է����ּ��� ==\n");
			}
			else if(!setSr(temp_argv1, temp_argv2)) {
				//setSr������ return 0
				printf("== �������� %d�� %d�� �����Ǿ����ϴ� ==\n", temp_argv1, temp_argv2);
			}
			else {
				printf("== sr��ɾ� - ������ �����Ͽ����ϴ� == \n");
			}
			// sr <register number> <value> : Ư�� ���������� �� ����
		}

		else if (!strcmp(cmd, "sm")) {
			scanf("%s", argv1);
			scanf("%s", argv2);

			temp_argv1 = (unsigned int)strtoul(argv1, NULL, 16);
			temp_argv2 = atoi(argv2);

			if (!setSm(temp_argv1, temp_argv2)) {
				printf("== �޸� %0x�� %d�� �����Ǿ����ϴ� ==\n", temp_argv1, MEM(temp_argv1, 0, 0, 2));
			}
			else {
				printf("== sm ��ɾ �����Ͽ����ϴ� ==\n");
			}
			// sm <location> <value> : �޸� Ư�� �ּ��� �� ����
		}

		else if (EQUAL(cmd, "l")) {
			printf("== enter the File Name :: ");
			scanf("%s", cmd);

			// TODO �޸𸮿� �ø���

			//result_temp = bin_read(cmd);

			result = LoadBin(cmd);
			if (result == 0) {
				printf("%s \nLoad �Ϸ�\n", cmd);
				did_load = 1;
			}
		}

		else if (EQUAL(cmd, "j")) {
			scanf("%x", &target_address);
			setPC(target_address);
		}

		else if (EQUAL(cmd, "g")) {
			int step_result = 0;

			while (step_result != 500) {
				printf("----\n");
				step_result = step();

				if (step_result == 100) {
					printf("== BreakPoint �Դϴ� ==\n");
					break;
				}
			}

			// ���� PC��ġ���� �ùķ����Ͱ� ��ɾ� ������ ó��
			// while(1) step(); �� �ϸ� step���� 500�� ȣ���ϸ� �����ϵ���
			// �׷��� ���ؼ� step() ������Ÿ���� �ٲ����
			// 500(systemcall 10)��ȯ�� while Ǯ��
		}

		else if (EQUAL(cmd, "s")) {
			int step_result = step();
			if (step_result == 500) {
				printf("\n--- program exit - systemcall 10 ---\nPC�� �ʱⰪ���� �����մϴ�.\n");
				setPC(0x00400000);
			}
			else if (step_result == 100) {
				printf("== BreakPoint �Դϴ� ==\n");
			}
		}

		else if (EQUAL(cmd, "m")) {
			// m <start> <end>
			scanf("%s", argv1);
			scanf("%s", argv2);
			
			temp_argv1 = (unsigned int)strtoul(argv1, NULL, 16);
			temp_argv2 = (unsigned int)strtoul(argv2, NULL, 16);

			if (!(temp_argv1 && temp_argv1))
				printf("== m ��ɾ �ùٸ��� �ʽ��ϴ� ==\n");
			else
				printMemory(temp_argv1, temp_argv2);
		}

		else if (EQUAL(cmd, "r")) {
			showRegister();		
		}

		else if (EQUAL(cmd, "break")) {
			scanf("%s", argv1);

			if (EQUAL(argv1, "off")) {
				// breakpoint off
				printf("Break point ����\n");
				setBreakPoint(0);
			}
			else {
				//breakpoint ����
				temp_argv1 = (unsigned int)strtoul(argv1, NULL, 16);
				setBreakPoint(temp_argv1);
			}
		}

		else if (EQUAL(cmd, "x")) {
			printf("Bye!");
			break;
		}


		*cmd = "";
		*argv1 = "";
		*argv2 = "";

	}


	free(REGISTER);
}