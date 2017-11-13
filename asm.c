#include "asm.h"

char* parseCommand(const char* cmd)
{
	char line[500];
	char s[] = " ,\t\r\n";
	strcpy(line, cmd);
	char* opcode = strtok(line, s);
	char* rd = strtok(NULL, s);
	char* rs = strtok(NULL, s);
	char* rt = strtok(NULL, s);
	char* imm = strtok(NULL, s);
	//opcode = convertOpcode(opcode);


	return opcode;

}



char* createString(char* opcode, char* rd, char* rs, char* rt, char* imm)
{


}
