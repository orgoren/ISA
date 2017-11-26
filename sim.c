
#include "sim.h"

int sim (int argc, char** argv)
{
	FILE* memin;
	FILE* files[4];

	char line[8];
	int PC = 0;
	int counter = 0;
	int i = 0;
	char memory[MAX_ROWS][MEMORY_WORD_LENGTH];
	bool end_of_file = false;
	int reg[17] = {0};

	memin = fopen(argv[1], "r");//is memin in argv[1]?
	if(!memin)
	{
		printf("Can't open File %s\n", argv[1]);
		return 0; // should we return 0 on failure?
	}
	while(fgets(line, MEMORY_WORD_LENGTH, memin))
	{
		strcpy(memory[i],line);
		++i;
	}
	for (i = 0; i<4; ++i)
	{
		files[i] = fopen(argv[i+2], "w");
		if(!files[i])
		{
			printf("Can't open File %s\n", argv[i+2]);
		}
	}
	i = 0;
	while(!end_of_file)
	{
		if(strcmp(memory[PC],"F0000000") == 0)//we got halt
		{
			fprintf(files[3], "&d", counter);
			close(files[3]);
			printToRegout(reg, files[1]);
			close(files[1]);
			//copy memory to memout (file[0])
		}
	}

}


void printToRegout(const char* reg, FILE* regout)
{

	for( int i = 0;i<16;++i)
	{
		if(i !=15)
		{
			fprintf(regout, "%x\n", reg[i]);
		}
//		else
//		{
//			fprintf(regout, "%x", reg[i]);
//		}
	}
	return;
}

void placeInTempReg(char* reg, const char* line)
{

}


void performCommand(const char* line, int* reg, char** memory)//reg[16] = pc
{
	int tempReg[4] = {0};//temReg[0] = rd, tempReg[1] = rs tempReg[2] = rt; tempReg[4] = imm; - decimal
	placeInTempReg(line, tempReg);
	if (line[0] == '0')//add
	{
		reg[tempReg[0]] = reg[tempReg[1]] + reg[tempReg[2]];
	}
	else if (line[0] == '1')
	{
		reg[tempReg[0]] = reg[tempReg[1]] - reg[tempReg[2]];
	}
	else if (line[0] == '2')
	{
		reg[tempReg[0]] = reg[tempReg[1]] & reg[tempReg[2]];
	}
	else if (line[0] == '3')
	{
		reg[tempReg[0]] = reg[tempReg[1]] | reg[tempReg[2]];
	}
	else if (line[0] == '4')
	{
		reg[tempReg[0]] = reg[tempReg[1]] << reg[tempReg[2]];
	}
	else if (line[0] == '5')
	{
		reg[tempReg[0]] = reg[tempReg[1]] >> reg[tempReg[2]];
	}
	else if (line[0] == '6')
	{
		reg[tempReg[0]] = reg[tempReg[3]];
	}
	else if (line[0] == '7')
	{
		if(reg[tempReg[1] == reg[tempReg[2]]])
		{
			reg[16] = tempReg[3];
		}
	}
	else if (line[0] == '8')
	{
		if(reg[tempReg[1] > reg[tempReg[2]]])
		{
			reg[16] = tempReg[3];
		}
	}
	else if (line[0] == '9')
	{
		if(reg[tempReg[1] <= reg[tempReg[2]]])
		{
			reg[16] = tempReg[3];
		}
	}
	else if (line[0] == 'A')
	{
		if(reg[tempReg[1] != reg[tempReg[2]]])
		{
			reg[16] = tempReg[3];
		}
	}
	else if (line[0] == 'B')
	{
		if(reg[tempReg[1] > reg[tempReg[2]]])
		{
			reg[15] = reg[16]+1;
			reg[16] = tempReg[3];
		}
	}
	else if (line[0] == 'C')//lw
	{
		reg[tempReg[0]] = memory[reg[tempReg[1]]+tempReg[3]]; // need to convert decimal to char
	}
	else if (line[0] == 'D')//sw
	{
		memory[reg[tempReg[1]]+tempReg[3]] = reg[tempReg[0]] ; // need to convert decimal to char
	}
	else if (line[0] == 'E')//jr
	{
		reg[16] = reg[tempReg[0]];
	}
	else if (line[0] == 'F')//halt
	{
		return;
	}
}
