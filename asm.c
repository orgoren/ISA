#include "asm.h"

void parseCommand(const char* cmd, char* result)
{
	char line[500];
	char s[] = " ,\t\r\n";
	strcpy(line, cmd);
	char* opcodeStr = strtok(line, s);
	char* rdStr = strtok(NULL, s);
	char* rsStr = strtok(NULL, s);
	char* rtStr = strtok(NULL, s);
	char* immStr = strtok(NULL, s);

	char opcode = convertOpcode(opcodeStr);

	char rd = convertRegister(rdStr);
	char rt = convertRegister(rtStr);
	char rs = convertRegister(rsStr);
	printf("rs = %d\n", rs);
	char imm[5];
	convertImmediate(immStr, imm);

	printf("rs=%s\n", rsStr);
	printf("opcode=%c, rd=%c, rs=%c, rt=%c\n", opcode, rd, rs, rt);

	result[0] = opcode;
	result[1] = rd;
	result[2] = rs;
	result[3] = rt;
	result[4] = imm[0];
	result[5] = imm[1];
	result[6] = imm[2];
	result[7] = imm[3];
	result[8] = '\0';
}

char convertRegister(char* reg)
{
	printf("reg=%s\n", reg);
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
	return 'G';
}

void convertDecToHex(int a, char* result)
{
	int i;
	int t;
	int mask = 15;
	for(i = 3; i >= 0; i--)
	{
		t = mask & a;
		if (t > 9)
		{
			result[i] = 'A' + t - 10;
		}
		else
		{
			result[i] = '0' + (char)(mask & a);
		}

		a >>= 4;
	}
	result[4] = '\0';

}

void convertImmediate(char* imm, char* result)
{
	if((imm[0] == '0') &&(imm[1] = 'x'))
	{
		//result = imm + 2;
		result[0] = imm[2];
		result[1] = imm[3];
		result[2] = imm[4];
		result[3] = imm[5];
		result[4] = '\0';

	}
	else
	{
		convertDecToHex(atoi(imm), result);
	}
}


int isThereLabelInIt(char* getline,char* label)
{
	// return 0 if there is no label
	// return 1 if there is label but no cmd in this line
	// return 2 if there is a label and cmd in this line
	// what about a line with two labels, one in the first word and one in the immediate?
	char line[500];
	char s[] = " ,\t\r\n";
	strcpy(line, getline);
	char* firstWord = strtok(line, s);
	char* secondWord;
	char* imm;
	int lenword = strlen(firstWord);
	if(firstWord[strlen-1] == ':')
	{
		strcpy(label, firstWord);
		label[strlen] = '\0';
		secondWord = strtok(line, s);
		if(!secondWord)
		{
			printf("there is no legal optcode in this line, step forward");
			return 1;
		}
		else if (secondWord[0] =='#')
		{
			printf("there is no legal optcode in this line, step forward");
			return 1;
		}
		else
		{
			printf("there is optcode and label in this line");
			return 2;
		}
	}
	else
	{
		printf("there is no label in the first word here");
		return 0;
	}
	int optNumber = isCMD(firstWord);
	if(optNumber != -1)
	{
		if (optNumber == 1)
		{
			printf("there is a branch cmd - need to remember relative jump");
			getImm(firstWord, imm); //jump to immm and check if it a label

		}
	}
}

void readFile(char* path)
{
	FILE* f;

	f = fopen(path, "r");
	if(!f)
	{
		printf("Can't open File\n");
		return;
	}

	char buffer[500];

	while(fgets(buffer, 500, f))
	{


	}
}
