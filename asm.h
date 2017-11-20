#ifndef ASM_H_
#define ASM_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ROW_LENGTH 500
#define MAX_ROWS 65535
#define MAX_LABEL_LENGTH 50

void parseCommand(const char* cmd, char* result);

char convertRegister(char* reg);

char convertOpcode(char* opcode);

void convertDecToHex(int a, char* result);

void convertImmediate(char* imm, char* result);

int isThereLabelInIt(char* getline,char* label);

void changeLine(char* currLine, int labelIndex, int lineIndex, bool isRel, char* newLine);

bool isBufferHasLabel(char* line, char* label);

int isCMD(char* firstWord);

int whichOptCode(char* Word);

void readFile(char* path);

#endif /* ASM_H_ */
