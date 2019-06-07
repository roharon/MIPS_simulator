#include "MIPS.h"

extern int* REGISTER;
extern int PC;

int break_point = 0;
// �극��ũ ����Ʈ

// TODO IR�� PC extern
// TODO getOp(IR) getFn(IR) getRs(IR) getRt(IR) getRd(IR) getOffset(IR)����
int step(void) {
	//instruction fetch


	long long IR = MEM(PC, 0, 0, 2);
	int offset;
	

	int op = getOp(IR);

	int fn = getFn(IR);
	int rs = getRs(IR);
	int rt = getRt(IR);
	int rd = getRd(IR);
	int sh = getSh(IR);
	printf("�� PC : %x\n", PC);
	printf("IR : %x\n", IR);
	//printf("op = %d rs =%d rt = %d rd = %d sh = %d fn = %d \n", op, rs, rt, rd,  sh, fn);
	if (op == 0) {
		// opcode 000000 - R-format
		if (fn == 32) {
			//REGISTER[rd] = ALU(ADD, REGISTER[rs], REGISTER[rt]);
			REG(rd, ALU(ADD, REG(rs, 0, 0), REG(rt, 0, 0)), 1);
			//printf("\nADD - ����Ǵ� rd : %d rs : %d + rt : %d\n", REGISTER[rd], REGISTER[rs], REGISTER[rt]);
				
		}
		else if (fn == 34) {
			REGISTER[rd] = ALU(SUB, REGISTER[rs], REGISTER[rt]);
			REG(rd, ALU(SUB, REG(rs, 0, 0), REG(rt, 0, 0)), 1);
		}
		else if (fn == 0) {
			REG(rd, ALU(SLL, REG(rt, 0, 0), sh), 1);
		}
		else if (fn == 2) {
			REG(rd, ALU(SRL, REG(rt, 0, 0), sh), 1);
		}
		else if (fn == 3) {
			REG(rd, ALU(SRA, REG(rt, 0, 0), sh), 1);
		}
		else if (fn == 42) {
			REG(rd, ALU(SRA, REG(rt, 0, 0), sh), 1);
		}
		else if (fn == 36) {
			//REGISTER[rd] = ALU(AND, REGISTER[rs], REGISTER[rt]);
			REG(rd, ALU(AND, REG(rs, 0, 0), REG(rt, 0, 0)), 1);
		}
		else if (fn == 37) {
			REG(rd, ALU(OR, REG(rs, 0, 0), REG(rt, 0, 0)), 1);

		}
		else if (fn == 38) {
			REG(rd, ALU(XOR, REG(rs, 0, 0), REG(rt, 0, 0)), 1);

		}
		else if (fn == 39) {
			REG(rd, ALU(NOR, REG(rs, 0, 0), REG(rt, 0, 0)), 1);
			//REGISTER[rd] = ALU(NOR, REGISTER[rs], REGISTER[rt]);
		}
		else if (fn == 12) {
			if (REG(v0,0,0) == 10) {
				printf("\n\nsystemcall 10 ȣ��\n");
				// v0 �� 10�϶� �����ϴ� ��
				return 500;
				// syscall 10�϶� 500 ��ȯ
			}
		}
		else if (fn == 8) {
			setPC(REG(ra, 0, 0));
		}
		else {
			printf("==���ǵ��� ���� ��ɾ��Դϴ�.==");
		}
	}
	else {
		
		int operand = getOffset(IR); //I-type operand
		offset = operand;
		int jta = getJta(IR); //J-type jump target address

		if (op == 1) {
			// I-format. bltz
			REG(ra, PC, 1);
			PC = PC + 4 * offset;
		}
		else if (op == 2) {
			// j-format. j
			PC = jta;
		}
		else if (op == 3) {
			//jal
			//REGISTER[ra] = PC + 4;
			REG(ra, PC + 4, 1);
			//printf("\nPC+4's IR : %x", MEM(PC + 4, 0, 0, 2));
			//printf("\nPC+8's IR : %x", MEM(PC + 8, 0, 0, 2));
			//printf("\nPC+12's IR : %x", MEM(PC + 12, 0, 0, 2));
			//printf("\nPC+16's IR : %x", MEM(PC + 16, 0, 0, 2));
			//printf("\nPC+20's IR : %x", MEM(PC + 20, 0, 0, 2));

			setPC(PC + (jta & 0x000FFFFF));
			//printf("\n jump target adr : %x\n", jta);
		}
		else if (op == 4) {
			//beq
			if (rs == rt) {
				REG(ra, PC, 1);
			}
		}
		else if (op == 5) {
			//bne
			if (rs != rt) {
				REG(ra, PC, 1);
			}
		}
		else if (op == 8) {
			//addi
			REG(rd, REG(rs,0,0) + operand, 1);
			printf("\noperand is %d, %x\n", operand, operand);
			//REGISTER[rd] = REGISTER[rs] + getOffset(IR);
		}
		else if (op == 10) {
			//slti
			REG(rt, REG(rs,0,0) < operand, 1);
		}
		else if (op == 12) {
			//andi
			REG(rt, REG(rs,0,0) & operand, 1);
			//REGISTER[rt] = getRs(IR) & getOffset(IR);
		}
		else if (op == 13) {
			//ori
			REG(rt, REG(rs,0,0) | operand, 1);
			//REGISTER[rt] = getRs(IR) | getOffset(IR);
		}
		else if (op == 14) {
			//xori
			REG(rt, REG(rs,0,0)^operand, 1);
			//REGISTER[rt] = getRs(IR) ^ getOffset(IR);
		}
		else if (op == 15) {
			//lui
			//printf("\nlui operand is %d \n", operand);
			//
			//printf("IR is %x\n", IR);
			if (rt == sp) {
				REG(rt, MEM(0x80000000 + (fn * 4), 0, 0, 2)<<16, 1);
			}
			else {
				REG(rt, MEM(0x10000000 + (rt * 1000 + (fn * 4)), 0, 0, 2)<<16, 1);

			}

			// 0x10000000 + (rs * 1000 + (rd * 4)), REG(rt,0,0), 1, 0
			// 2byte�� ����.
			
			//*(regs+rt) = *(mem+( *(regs+rs)+offset) );
		}
		else if (op == 32) {
			//lb
			//MEM
			if (rt == sp) {
				REG(rt, MEM(0x80000000 + (fn * 4), 0, 0, 2), 1);
			}
			else {
				REG(rt, MEM(0x10000000 + (rt * 1000 + (fn * 4)), 0, 0, 2), 1);
			}
		}
		else if (op == 35) {
			//lw
			//MEM
			//lw $t1, 10($s0)
			if (rt == sp) {
				//REGISTER[rt] = MEM(0x80000000 + (fn * 4), 0, 0, 2);
				REG(rt, MEM(0x80000000 + (fn * 4), 0, 0, 2), 1);
			}
			else {
				REG(rt, MEM(0x10000000 + (rt * 1000 + (fn * 4)), 0, 0, 2), 1);
			}
			//printf("\nrt :: %d\n", REGISTER[rt]);
		}
		else if (op == 36) {
			//lbu
			// MEM
			if (rt == sp) {
				//REGISTER[rt] = MEM(0x80000000 + (fn * 4), 0, 0, 1);
				REG(rt, MEM(0x80000000 + (fn * 4), 0, 0, 1), 1);
			}
			else {
				//REGISTER[rt] = MEM(0x10000000 + (rt * 1000 + (fn * 4)), 0, 0, 0);
				REG(rt, MEM(0x10000000 + (rt * 1000 + (fn * 4)), 0, 0, 0), 1);
			}
			//REGISTER[rt] = getRs(IR) + getOffset(IR);
			// *(mem+( *(regs+rs)+offset) ) = *(regs+rt);
		}
		else if (op == 40) {
			//sb
			// MEM
			// sw $16, 0($10)
			// op = 43, fn=0, rs=10, rt=16, rd=0
			if (rt == sp) {
				//REGISTER[rt] = MEM(0x80000000 + (fn * 4), 0, 0, 0);
				// rs�� rd*4��° �ּҿ� reg(rt)�� �ִ´�.
				MEM(0x80000000 + (rd * 4), REG(rt,0,0), 1, 0);
			}
			else {
				//REGISTER[rt] = MEM(0x10000000 + (rt * 1000 + (fn * 4)), 0, 0, 0);
				MEM(0x10000000 + (rs * 1000 + (rd * 4)), REG(rt,0,0), 1, 0);
				// �������
			}
			//REGISTER[rt] = getRs(IR) + getOffset(IR);
			// *(mem+( *(regs+rs)+offset) ) = *(regs+rt);
		}
		else if (op == 43) {
			//sw
			//MEM
			if (rt == sp) {
				MEM(0x80000000 + (rd * 4), REG(rt,0,0), 1, 0);
			}
			else {
				MEM(0x10000000 + (rs * 1000 + (rd * 4)), REG(rt,0,0), 1, 0);
			}
			//REGISTER[rt] = getRs(IR) + getOffset(IR);
			//*(mem + (*(regs + rs) + offset)) = *(regs + rt);
		}
	}


	if (break_point == PC) {
		PC += 4;
		return 100;
	}

	PC += 4;
	return 0;
}


int setBreakPoint(unsigned int argv1) {
	break_point = argv1;
	printf("�극��ũ : %x\n", break_point);
}