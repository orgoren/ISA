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
		return (char)0;
	}
	else if (!strcmp(reg, "$at"))
	{
		return (char)1;
	}
	else if(!strcmp(reg, "$v0"))
	{
		return (char)2;
	}
	else if(!strcmp(reg, "$a0"))
	{
		return (char)3;
	}
	else if (!strcmp(reg, "$a1"))
	{
		return (char)4;
	}
	else if(!strcmp(reg, "$t0"))
	{
		return (char)5;
	}
	else if(!strcmp(reg, "$t1"))
	{
		return (char)6;
	}
	else if(!strcmp(reg, "$t2"))
	{
		return (char)7;
	}
	else if(!strcmp(reg, "$t3"))
	{
		return (char)8;
	}
	else if (!strcmp(reg, "$s0"))
	{
		return (char)9;
	}
	else if(!strcmp(reg, "$s1"))
	{
		return (char)10;
	}
	else if(!strcmp(reg, "$s2"))
	{
		return (char)11;
	}
	else if(!strcmp(reg, "$gp"))
	{
		return (char)12;
	}
	else if(!strcmp(reg, "$sp"))
	{
		return (char)13;
	}
	else if(!strcmp(reg, "$fp"))
	{
		return (char)14;
	}
	else if(!strcmp(reg, "$ra"))
	{
		return (char)15;
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
		return (char)0;
	}
	else if(!strcmp(opcode, "sub"))
	{
		return (char)1;
	}
	else if(!strcmp(opcode, "and"))
		{
			return (char)2;
		}
	else if(!strcmp(opcode, "or"))
		{
			return (char)3;
		}
	else if(!strcmp(opcode, "sll"))
		{
			return (char)4;
		}
	else if(!strcmp(opcode, "sra"))
		{
			return (char)5;
		}
	else if(!strcmp(opcode, "limm"))
		{
			return (char)6;
		}
	else if(!strcmp(opcode, "beq"))
		{
			return (char)7;
		}
	else if(!strcmp(opcode, "bgt"))
		{
			return (char)8;
		}
	else if(!strcmp(opcode, "ble"))
		{
			return (char)9;
		}
	else if(!strcmp(opcode, "bne"))
		{
			return (char)10;
		}
	else if(!strcmp(opcode, "jal"))
		{
			return (char)11;
		}
	else if(!strcmp(opcode, "lw"))
		{
			return (char)12;
		}
	else if(!strcmp(opcode, "sw"))
		{
			return (char)13;
		}
	else if(!strcmp(opcode, "jr"))
		{
			return (char)14;
		}
	else if(!strcmp(opcode, "halt"))
		{
			return (char)15;
		}
	return (char)16;
}
