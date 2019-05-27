#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma once
// 레지스터 저장공간



#pragma warning(disable: 4996)

int ALU(int X, int Y, int C, int* Z);
int logicOperation(int X, int Y, int C);
int addSubtract(int X, int Y, int C);
int shiftOperation(int V, int Y, int C);
int checkZero(int S);
int checkSetLess(int X, int Y);
// ALU.h
void step(void);

int bin_read();
void ops_Inst(char Opt[], char Funct[]);
const char* Inst_Enc(char enc_target[], char f_val[]);
// a.h

unsigned int MEM(unsigned int A, int V, int nRW, int s);
// MEM.h

unsigned int REG(unsigned int A, unsigned int V, unsigned int nRW);
void showRegister(void);
// REG.h
void setPC(unsigned int val);
int getPC();

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



