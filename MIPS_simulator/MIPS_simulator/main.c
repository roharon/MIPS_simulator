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
	// 레지스터 할당

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

			printf("먼저 binary파일을 로드해주세요\n");
			continue;
		}

		if (!strcmp(cmd, "sr")) {
			scanf("%s", argv1);
			scanf("%s", argv2);

			temp_argv1 = atoi(argv1);
			temp_argv2 = (unsigned int)strtoul(argv2, NULL, 16);
			// atoi 실패시 0반환

			if (!temp_argv2) {
				// 변환실패시
				printf("== sr 명령어 인자가 잘못되었습니다. 다시 입력해주세요 ==\n");

			}
			else if ((temp_argv1 > 31) || (temp_argv1 < 0)) {
				// 레지스터 범위를 넘었을때
				printf("== 레지스터 범위가 올바르지 않습니다. 다시 입력해주세요 ==\n");
			}
			else if(!setSr(temp_argv1, temp_argv2)) {
				//setSr성공시 return 0
				printf("== 레지스터 %d가 %d로 설정되었습니다 ==\n", temp_argv1, temp_argv2);
			}
			else {
				printf("== sr명령어 - 설정에 실패하였습니다 == \n");
			}
			// sr <register number> <value> : 특정 레지스터의 값 설정
		}

		else if (!strcmp(cmd, "sm")) {
			scanf("%s", argv1);
			scanf("%s", argv2);

			temp_argv1 = (unsigned int)strtoul(argv1, NULL, 16);
			temp_argv2 = atoi(argv2);

			if (!setSm(temp_argv1, temp_argv2)) {
				printf("== 메모리 %0x가 %d로 설정되었습니다 ==\n", temp_argv1, MEM(temp_argv1, 0, 0, 2));
			}
			else {
				printf("== sm 명령어가 실패하였습니다 ==\n");
			}
			// sm <location> <value> : 메모리 특정 주소의 값 설정
		}

		else if (EQUAL(cmd, "l")) {
			printf("== enter the File Name :: ");
			scanf("%s", cmd);

			// TODO 메모리에 올리기

			//result_temp = bin_read(cmd);

			result = LoadBin(cmd);
			if (result == 0) {
				printf("%s \nLoad 완료\n", cmd);
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
					printf("== BreakPoint 입니다 ==\n");
					break;
				}
			}

			// 현재 PC위치에서 시뮬레이터가 명령어 끝까지 처리
			// while(1) step(); 을 하며 step에서 500를 호출하면 종료하도록
			// 그러기 위해선 step() 프로토타입을 바꿔야함
			// 500(systemcall 10)반환시 while 풀림
		}

		else if (EQUAL(cmd, "s")) {
			int step_result = step();
			if (step_result == 500) {
				printf("\n--- program exit - systemcall 10 ---\nPC를 초기값으로 설정합니다.\n");
				setPC(0x00400000);
			}
			else if (step_result == 100) {
				printf("== BreakPoint 입니다 ==\n");
			}
		}

		else if (EQUAL(cmd, "m")) {
			// m <start> <end>
			scanf("%s", argv1);
			scanf("%s", argv2);
			
			temp_argv1 = (unsigned int)strtoul(argv1, NULL, 16);
			temp_argv2 = (unsigned int)strtoul(argv2, NULL, 16);

			if (!(temp_argv1 && temp_argv1))
				printf("== m 명령어가 올바르지 않습니다 ==\n");
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
				printf("Break point 해제\n");
				setBreakPoint(0);
			}
			else {
				//breakpoint 설정
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