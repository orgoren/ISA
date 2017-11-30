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

int sim (int argc, char** argv);

void updateTrace(const int* reg, FILE* traceOut,char* inst);

void convertDecToHex2(int a, char* result, int len);

void printToRegout(int* reg, FILE* regout);

void placeInTempReg(int* reg, char* line);

void performCommand(char* line, int* reg);//, char** memory);

int convertHexToIntTwosCom(char* tempString);

int charToInt(char a);

#endif /* SIM_H_ */
