#ifndef ASM_H_
#define ASM_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void parseCommand(const char* cmd, char* result);

char convertRegister(char* reg);

char convertOpcode(char* opcode);

void convertDecToHex(int a, char* result);

//char mergeIntoInt(char bigger, char smaller);

void convertImmediate(char* imm, char* result);

int isThereLabelInIt(char* getline,char* label);

void getImm(char* firstWord, char* imm);

int isCMD(char* firstWord);

void readFile(char* path);



#endif /* ASM_H_ */
