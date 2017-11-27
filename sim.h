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
#define MEM_OUT 2
#define REG_OUT 3
#define TRACE 4
#define COUNT 5

int sim (int argc, char** argv);

void convertDecToHex(int a, char* result, int len);

void printToRegout(const char* reg, FILE* regout);

void placeInTempReg(char* reg, const char* line);

void performCommand(const char* line, int* reg, char** memory);

void convertIntToString(int num, char* tempString);

int convertHexToIntTwosCom(char* tempString);

int charToInt(char a);

#endif /* SIM_H_ */
