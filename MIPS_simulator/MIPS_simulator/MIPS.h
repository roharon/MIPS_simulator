#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma once
#pragma warning(disable: 4996)

#define M_SIZE 9999
#define EQUAL(cmd, value) (strcmp(cmd,value)==0)

#define REG_SIZE 32
#define zero 0
#define v0 2
#define v1 3
#define a0 4
#define a1 5
#define a2 6
#define a3 7
#define t0 8
#define t1 9
#define t2 10
#define t3 11
#define t4 12
#define t5 13
#define t6 14
#define t7 15
#define s0 16
#define s1 17
#define s2 18
#define s3 19
#define s4 20
#define s5 21
#define s6 22
#define s7 23
#define t8 24
#define t9 25
#define k0 26
#define k1 27
#define gp 28
#define sp 29
#define fp 30
#define ra 31

// step.c instruction

#define ADD 8
#define SUB 9
#define SLL 1
#define SRL 2
#define SRA 3
#define SL 4
#define NOSHIFT 0
#define AND 12
#define OR 13
#define XOR 14
#define NOR 15


// Instruction Encoding¿« R-formatø°º≠

// end step.c instruction


// ALU.c
int ALU(int C, int X, int Y);
int logicOperation(int X, int Y, int C);
int addSubtract(int X, int Y, int C);
int shiftOperation(int V, int Y, int C);
int checkZero(int S);
int checkSetLess(int X, int Y);
// ALU.c prototype

// binary_convert.c
int fromBinary(const char*);
char* toBinary(int val);
// binary_convert.c prototype

// MEM.c
unsigned int MEM(unsigned int A, int V, int nRW, int S);
// MEM.c prototype

// REG.c
unsigned int REG(unsigned int A, unsigned int V, unsigned int nRW);
void showRegister(void);
void setPC(unsigned int val);
int getPC();

int getOp(int);
int getFn(int);
int getRs(int);
int getRt(int);
int getRd(int IR);
int getOffset(int IR);
int getJta(int);
// REG.c prototype

// step.c
int step(void);
// step.c prototype

//loadToMemory.c
int LoadBin(char* PATH);
// loadToMemory.c prototype

// substring.c
char *substr(char *pnInput, int nStart, int nLen);
// substring.c prototype