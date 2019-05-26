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
*/

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
		return 1;
	}


	char opt[40] = "";
	char temp[40] = "";
	char temp2[40] = "";
	char funct[40] = "";

	while (1 == fread(&MEM[count], 1, 1, pFile)) {
		IR = MEM[count];
		if ((count + 1) == 8) {
			printf("Number of Instructions: %d, Number of Data: %d\n", MEM[3], MEM[7]);
		}
		else if ((count + 1) % 4 == 0 && (count + 1) > 8) {
			if (count > (8 + MEM[3] * 4))
				break;
			itoa(MEM[count - 3], opt, 2);


			strcpy(temp, opt);
			strcpy(opt, "");
			for (int i = 0; i < 8 - strlen(temp); i++) {
				strcat(opt, "0");
				//이 부분에서 opt가 8개로 되도록

			}
			strcat(opt, temp);

			itoa(MEM[count], funct, 2);

			strcpy(temp, funct);
			strcpy(funct, "");
			for (int i = 0; i < 8 - strlen(temp); i++) {
				strcat(funct, "0");
			}
			strcat(funct, temp);
			ops_Inst(opt, funct);
		}
		count++;
	}

	fclose(pFile);

	return 0;
}

void ops_Inst(char Opt[], char Funct[])
{
	int opt_Hex = 0, funct_Hex = 0;
	char inst_enc[10] = "";
	//inst_enc : Instruction Encoding 명령어

	Opt[6] = '\0';
	strcpy(Funct, &Funct[2]);
	Funct[6] = '\0';
	//각각 6비트씩만 설정함

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