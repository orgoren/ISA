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

char convertRegister(char* reg)
{
	if(!strcmp(reg, "$zero"))
	{
		return '0';
	}
	else if (!strcmp(reg, "$at"))
	{
		return '1';
	}
	else if(!strcmp(reg, "$v0"))
	{
		return '2';
	}
	else if(!strcmp(reg, "$a0"))
	{
		return '3';
	}
	else if (!strcmp(reg, "$a1"))
	{
		return '4';
	}
	else if(!strcmp(reg, "$t0"))
	{
		return '5';
	}
	else if(!strcmp(reg, "$t1"))
	{
		return '6';
	}
	else if(!strcmp(reg, "$t2"))
	{
		return '7';
	}
	else if(!strcmp(reg, "$t3"))
	{
		return '8';
	}
	else if (!strcmp(reg, "$s0"))
	{
		return '9';
	}
	else if(!strcmp(reg, "$s1"))
	{
		return 'A';
	}
	else if(!strcmp(reg, "$s2"))
	{
		return 'B';
	}
	else if(!strcmp(reg, "$gp"))
	{
		return 'C';
	}
	else if(!strcmp(reg, "$sp"))
	{
		return 'D';
	}
	else if(!strcmp(reg, "$fp"))
	{
		return 'E';
	}
	else if(!strcmp(reg, "$ra"))
	{
		return 'F';
	}

	return (char)16;
}

char* createString(char* opcode, char* rd, char* rs, char* rt, char* imm)
{


}

char convertOpcode(char* opcode)
{
	if(!strcmp(opcode, "add"))
	{
		return '0';
	}
	else if(!strcmp(opcode, "sub"))
	{
		return '1';
	}
	else if(!strcmp(opcode, "and"))
		{
			return '2';
		}
	else if(!strcmp(opcode, "or"))
		{
			return '3';
		}
	else if(!strcmp(opcode, "sll"))
		{
			return '4';
		}
	else if(!strcmp(opcode, "sra"))
		{
			return '5';
		}
	else if(!strcmp(opcode, "limm"))
		{
			return '6';
		}
	else if(!strcmp(opcode, "beq"))
		{
			return '7';
		}
	else if(!strcmp(opcode, "bgt"))
		{
			return '8';
		}
	else if(!strcmp(opcode, "ble"))
		{
			return '9';
		}
	else if(!strcmp(opcode, "bne"))
		{
			return 'A';
		}
	else if(!strcmp(opcode, "jal"))
		{
			return 'B';
		}
	else if(!strcmp(opcode, "lw"))
		{
			return 'C';
		}
	else if(!strcmp(opcode, "sw"))
		{
			return 'D';
		}
	else if(!strcmp(opcode, "jr"))
		{
			return 'E';
		}
	else if(!strcmp(opcode, "halt"))
		{
			return 'F';
		}
	return (char)16;
}

void mergeFourMSB(char great, char second, char third ,char last, char* result)
{
//	char* result[4];
	result[0] = great;
	result[1] = second;
	result[2] = third;
	result[3] = last;
//	return result;
}

void convertImmediate(char* imm, char* result)
{
//	char* result;
	if((imm[0] == '0') &&(imm[1] = 'x'))
	{
		result = imm + 2;
//		return result;
	}else if

}
