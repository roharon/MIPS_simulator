#include "MIPS.h"

const char PATH[] = "C:/roharon98/HUFS/Computer_structure/report3/machine_example/as_ex04_fct.bin";
// bin 파일경로
/*
	처음 앞 4개 4개는 각각 명령어 수와 데이터 수

	헥사코드 8D 50 00 00 이렇게 4개 읽고
	이진수로 변환하면
	앞부분 6개인 100011 은 Intruction Encoding에서 lw가 된다.
	뒷부분 000000은 R-format이므로 0이 된다.
	Opc은 001111 (lui)앞부분의 헥사값으로 출력 맨앞6비트
	Fct는 뒷부분의 헥사값 맨뒤 6비트

lw $4, 0($29)
8FA40000

‭100011 // lw - op
11101 //  29 -rs
00100 // 4 - rt
0000000000000000‬ // 0

 sll $2, $4, 2
‭000000
00000
00100
0001000010
000000‬

addi $29, $29, -4
‭001000 // addi
11101  // 29
11101  // 29
1111
1111
1111
1100‬

addiu $6, $5, 4
001001 // addiu
00101 // 5
00110 // 6
0000 0000 0000 0100 // 4


sw ＄t1, 32(＄t2)
101011	01010	01001	0000 0000 0010 0000

sub  ＄v1, ＄v1, ＄v0
opcode	rs	rt	rd	shamt	funct
000000	00011	00010	00011	00000	100010

lw  ＄v0, 4(＄at)
opcode	rs	rt	immediate
100011	00001	00010	0000 0000 0000 0100

000000
00110
01111
1101000001001000
*/

extern int PC;
unsigned char rs[40] = "";
unsigned char rt[40] = "";
unsigned char rd[40] = "";
unsigned char sh[40] = "";
unsigned char operand[40] = "";
unsigned char jump_target_address[40] = "";

int bin_read()
{
	unsigned char MEM[M_SIZE];
	FILE *pFile = NULL;
	errno_t err;
	int count = 0;
	unsigned int IR = 0;
	char IR_string[16] = "";

	err = fopen_s(&pFile, PATH, "rb");
	if (err) {
		printf("Cannot open file\n");
		return 400;
	}

	char opt[40] = "";
	char temp[40] = "";
	char temp2[40] = "";
	char funct[40] = "";

	unsigned char var_temp;
	

	

	while (1 == fread(&MEM[count], 1, 1, pFile)) {
		setPC(getPC() + 4);
		IR = MEM[count];

		if (((count + 1) % 4 == 0) && (count + 1 > 8)) {
			printf("=-=-=-=-= count : %d   Hexa : %x =-=-=-=-=-=-=-=\n", count, MEM[count]);
			//   00 11 01. 00 00 0.0 00 00.
			//	 00 11 01. 00 00 0.0 00 00.
			//itoa(MEM[count - 12], opt, 16);

			//printf("opt ->> %s\n", opt);


			strcpy(rs, "");
			strcpy(opt, "");
			strcpy(temp, "");

			for (int q = count - 3; q <= count; q++) {
				// hexa로 바꿔서 rs에 00000000 형식 한줄 저장함
				itoa(MEM[q], opt, 2);
				for (int ind = strlen(opt); ind < 8; ind++) {
					strcpy(temp, opt);
					strcpy(opt, "0");
					strcat(opt, temp);
				}

				strcat(rs, opt);
			}


			////printf("oneline-bin : %s    ", rs);
			/*
			2진만 나타내면 되기에 주석처리함 16진수로 한줄 표현 하는 것. - 00 00 00 00
			for (int q = count - 9; q <= count - 6; q++) {
				// hexa로 바꿔서 rs에 00000000 형식 한줄 저장함
				itoa(MEM[q], opt, 16);
				for (int ind = strlen(opt); ind < 2; ind++) {
					strcpy(temp, opt);
					strcpy(opt, "0");
					strcat(opt, temp);
				}

				strcat(rs, opt);
			}


			printf("oneline-hex : %s\n", rs);
			*/

			//itoa(MEM[count - 9], opt, 16); 00 00 00 00의 첫번째
			//itoa(MEM[count - 12], opt, 16); 00 00 00 00의 두번째

			//printf("레지스터 체크 count : %d  opt : %s \n", count, opt);


			strcpy(opt, rs);
			opt[6] = '\0';

			strcpy(rt, rs + 11);
			rt[5] = '\0';
			//rt값



			strcpy(rd, rs + 16);
			rd[5] = '\0';

			strcpy(sh, rs + 21);
			sh[5] = '\0';

			strcpy(funct, rs + 26);
			funct[6] = '\0';

			strcpy(operand, rs + 16);
			operand[16] = '\0';

			strcpy(jump_target_address, rs + 6);
			jump_target_address[26] = '\0';

			strcpy(rs, rs + 6);
			rs[5] = '\0';
			// rs에 모두 저장해서 나누는 것이므로 rs는 맨 마지막에 처리해야함.

			printf("opt is %s rs is %s rt is %s rd is %s fn is %s operand is %s\n", opt, rs, rt, rd, funct, operand);
			
			ops_Inst(opt, funct);

			
		}

		//printf("opt is %s rs is %s rt is %s rd is %s fn is %s\n", opt, rs, rt, rd, funct);

		/*
		if ((count + 1) == 8) {
			printf("Number of Instructions: %d, Number of Data: %d\n", MEM[3], MEM[7]);
		}
		*/
		count++;
	}

	fclose(pFile);

	return 0;
}

void ops_Inst(char Opt[], char Funct[])
{
	int opt_Hex = 0, funct_Hex = 0;
	char inst_enc[10] = "";


	char* pos = NULL;

	opt_Hex = strtol(Opt, &pos, 2);
	funct_Hex = strtol(Funct, &pos, 2);

	printf("Opc : %4x,  Fct : %4x, Inst : %s\n", opt_Hex, funct_Hex, Inst_Enc(Opt, Funct));
}

const char* Inst_Enc(char enc_target[], char f_val[]) {
	// opcode의 6비트(2진수 형식으로 나타낸 문자열) 을 명령어로 나타내도록 구현
	// strcmp 리턴값 equal: == 0 | unequal: != 0
	// R_format일때(000000) 인코딩 2-0 5-3 구간 표대로 구현
	//printf("\n%s %s\n", enc_target, f_val);
	char result[10] = "";
	if EQUAL(enc_target, "000000") {
		//R-format
		if EQUAL(f_val, "000000")
			return "sll";
		else if EQUAL(f_val, "000010")
			return "srl";
		else if EQUAL(f_val, "000011")
			return "sra";
		else if EQUAL(f_val, "001000")
			return "jr";
		else if EQUAL(f_val, "001100")
			return "syscall";
		else if EQUAL(f_val, "001001")
			return "addiu";
		else if EQUAL(f_val, "010000")
			return "mfhi";
		else if EQUAL(f_val, "010010")
			return "mflo";
		else if EQUAL(f_val, "011000")
			return "mul";
		else if EQUAL(f_val, "100000")
			return "add";
		else if EQUAL(f_val, "100010")
			return "sub";
		else if EQUAL(f_val, "100100")
			return "and";
		else if EQUAL(f_val, "100101")
			return "or";
		else if EQUAL(f_val, "100110")
			return "xor";
		else if EQUAL(f_val, "100111")
			return "nor";
		else if EQUAL(f_val, "101010")
			return "slt";
	}
	else if EQUAL(enc_target, "000001")
		return "bltz";
	else if EQUAL(enc_target, "000010")
		return "j";
	else if EQUAL(enc_target, "000011")
		return "jal";
	else if EQUAL(enc_target, "000100")
		return "beq";
	else if EQUAL(enc_target, "000101")
		return "bne";
	else if EQUAL(enc_target, "001000")
		return "addi";
	else if EQUAL(enc_target, "001010")
		return "slti";
	else if EQUAL(enc_target, "001100")
		return "andi";
	else if EQUAL(enc_target, "001101")
		return "ori";
	else if EQUAL(enc_target, "001110")
		return "xori";
	else if EQUAL(enc_target, "001111")
		return "lui";
	else if EQUAL(enc_target, "100000")
		return "lb";
	else if EQUAL(enc_target, "100011")
		return "lw";
	else if EQUAL(enc_target, "100100")
		return "lbu";
	else if EQUAL(enc_target, "101000")
		return "sb";
	else if EQUAL(enc_target, "101011")
		return "sw";
	else
		return "\n===ERROR (nearby EQUAL) ===\n";
}