#include "MIPS.h"

extern int* REGISTER;
extern int PC;
// TODO IR와 PC extern
// TODO getOp(IR) getFn(IR) getRs(IR) getRt(IR) getRd(IR) getOffset(IR)구현
int step(void) {
	//instruction fetch

	int IR = MEM(PC, 0, 0, 2);
	int offset;
	

	int op = getOp(IR);

	int fn = getFn(IR);
	int rs = getRs(IR);
	int rt = getRt(IR);
	int rd = getRd(IR);
	printf("PC : %x\n", PC);
	printf("IR : %x\n", IR);
	printf("op = %d fn = %d rs =%d\nrt = %d rd = %d\n", op, fn, rs, rt, rd);
	if (op == 0) {
		// opcode 000000 - R-format
		if (fn == 32) {
			REGISTER[rd] = ALU(ADD, REGISTER[rs], REGISTER[rt]);
		}
		else if (fn == 34) {
			REGISTER[rd] = ALU(SUB, REGISTER[rs], REGISTER[rt]);
		}
		else if (fn == 0) {
			REGISTER[rd] = ALU(SLL, REGISTER[rs], REGISTER[rt]);
		}
		else if (fn == 2) {
			REGISTER[rd] = ALU(SRL, REGISTER[rs], REGISTER[rt]);
		}
		else if (fn == 3) {
			REGISTER[rd] = ALU(SRA, REGISTER[rs], REGISTER[rt]);
		}
		else if (fn == 42) {
			REGISTER[rd] = ALU(SL, REGISTER[rs], REGISTER[rt]);
		}
		else if (fn == 36) {
			REGISTER[rd] = ALU(AND, REGISTER[rs], REGISTER[rt]);
		}
		else if (fn == 37) {
			REGISTER[rd] = ALU(OR, REGISTER[rs], REGISTER[rt]);
		}
		else if (fn == 38) {
			REGISTER[rd] = ALU(XOR, REGISTER[rs], REGISTER[rt]);
		}
		else if (fn == 39) {
			REGISTER[rd] = ALU(NOR, REGISTER[rs], REGISTER[rt]);
		}
		else if (fn == 12) {
			printf("\n\nsystemcall 10 호출 됩니다\n%d %d\n\n", REGISTER[rs], REGISTER[rt]);

			if (REGISTER[rs] == 10) {
				return 500;
				// syscall 10일때 500 반환
			}
		}
		else {
			printf("Undefined Inst~");
		}
	}
	else {
		
		int operand = getOffset(IR); //I-type operand
		int jta = getJta(IR); //J-type jump target address

		if (op == 1) {
			// I-format. bltz
			offset = getOffset(IR);
			PC = PC + 4 * offset;
		}
		else if (op == 2) {
			// j-format. j
			PC = getJta(IR);
		}
		else if (op == 3) {
			//jal
			REGISTER[ra] = PC + 4;
			PC = getJta(IR);
		}
		else if (op == 4) {
			//beq
			if (getRs(IR) == getRt(IR)) {
				offset = getOffset(IR);
			}
		}
		else if (op == 5) {
			//bne
			if (getRs(IR) != getRt(IR)) {
				offset = getOffset(IR);
			}
		}
		else if (op == 8) {
			//addi
			REGISTER[rd] = REGISTER[rs] + getOffset(IR);
		}
		else if (op == 10) {
			//slti
			REGISTER[rt] = (getRs(IR) < getOffset(IR));
		}
		else if (op == 12) {
			//andi
			REGISTER[rt] = getRs(IR) & getOffset(IR);
		}
		else if (op == 13) {
			//ori
			REGISTER[rt] = getRs(IR) | getOffset(IR);
		}
		else if (op == 14) {
			//xori
			REGISTER[rt] = getRs(IR) ^ getOffset(IR);
		}
		else if (op == 15) {
			//lui
			// TODO rechange to for MEM
			REGISTER[rt] = getOffset(IR);
			//*(regs+rt) = *(mem+( *(regs+rs)+offset) );
		}
		else if (op == 32) {
			//lb
			//MEM
			REGISTER[rt] = getRs(IR) + getOffset(IR);
			//*(regs+rt) = *(mem+( *(regs+rs)+offset) );
		}
		else if (op == 35) {
			//lw
			//MEM
			//lw $t1, 10($s0)
			REGISTER[rt] = getRs(IR) + getOffset(IR);
			//*(regs+rt) = *(mem+( *(regs+rs)+offset) );
		}
		else if (op == 36) {
			//lbu
			// MEM
			REGISTER[rt] = getRs(IR) + getOffset(IR);
			// *(mem+( *(regs+rs)+offset) ) = *(regs+rt);
		}
		else if (op == 40) {
			//sb
			// MEM
			REGISTER[rt] = getRs(IR) + getOffset(IR);
			// *(mem+( *(regs+rs)+offset) ) = *(regs+rt);
		}
		else if (op == 43) {
			//sw
			//MEM
			REGISTER[rt] = getRs(IR) + getOffset(IR);
			//*(mem + (*(regs + rs) + offset)) = *(regs + rt);
		}
	}
	PC += 4;
	return 0;
}