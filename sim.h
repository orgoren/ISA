#ifndef SIM_H_
#define SIM_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MAX_ROW_LENGTH 500
#define MAX_ROWS 65535
#define MAX_LABEL_LENGTH 50
#define MEMORY_WORD_LENGTH 8
#define NUM_OF_REGS 16

#define MEM_OUT 0
#define REG_OUT 1
#define TRACE_OUT 2
#define COUNT_OUT 3

#define RD 0
#define RS 1
#define RT 2
#define IMM 3

#define ADD '0'
#define SUB '1'
#define AND '2'
#define OR '3'
#define SLL '4'
#define SRA '5'
#define LIMM '6'
#define BEQ '7'
#define BGT '8'
#define BLE '9'
#define BNE 'A'
#define JAL 'B'
#define LW 'C'
#define SW 'D'
#define JR 'E'
#define HALT 'F'

int sim (int argc, char** argv);

void updateTrace(const int* reg, FILE* traceOut,char* inst);

void convertDecToHex2(int a, char* result, int len);

void printToRegout(int* reg, FILE* regout);

void placeInTempReg(int* reg, char* line);

void performCommand(char* line, int* reg);

int convertHexToIntTwosCom(char* tempString);

int charToInt(char a);

#endif /* SIM_H_ */
