#ifndef ASM_H_
#define ASM_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* parseCommand(const char* cmd);

char convertRegister(char* reg);

char* createString(char* opcode, char* rd, char* rs, char* rt, char* imm);


char convertOpcode(char* opcode);

char mergeIntoInt(char bigger, char smaller);

#endif /* ASM_H_ */
