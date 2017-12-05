#include "sim.h"

int sim (int argc, char** argv)
{
	FILE* memin;
	FILE* files[4];
	char line[10];
	int PC = 0;
	int counter = 0;
	int i = 0;
	char temp[4];
	int resultInt;
	int tempReg[4] = {0};
	char zeros[] = "00000000";
	char memory[MAX_ROWS][MEMORY_WORD_LENGTH + 2];
	bool endOfFile = false;
	int reg[17] = {0};

	memin = fopen(argv[1], "r");
	if(!memin)
	{
		printf("Can't open File %s\n", argv[1]);
		return 0; // should we return 0 on failure?
	}
	while(fgets(line, MEMORY_WORD_LENGTH+2, memin))
	{
		strcpy(memory[i],line);
		memory[i][8] = '\0';
		++i;
	}

	for(; i < MAX_ROWS; i++)
	{
		strcpy(memory[i], zeros);
	}

	printf("yoyo\n");

	for (i = 0; i<4; ++i)
	{
		files[i] = fopen(argv[i+2], "w");
		if(!files[i])
		{
			printf("Can't open File %s\n", argv[i+2]);
		}
	}


	i = 0;
	PC = 0;
	while(!endOfFile)
	{
		printf("###########################################################\n");
		counter++;
		updateTrace(reg, files[TRACE_OUT], memory[PC]);
		printf("PC = %d cmm = %s\n", PC, memory[PC]);
		if(memory[PC][0] == 'F')
		{
			fprintf(files[COUNT_OUT], "%d\n", counter);
			printToRegout(reg, files[REG_OUT]);
			endOfFile = true;

			for(i = 0; i < MAX_ROWS; i++)
			{
				fprintf(files[MEM_OUT], "%s\n", memory[i]);
			}
		}
		else
		{


			if(memory[PC][0] == LW)
			{
				placeInTempReg(tempReg, memory[PC]);
				printf("reg[tempReg[1]]=%d\n", reg[tempReg[RS]]);
				resultInt = convertHexToIntTwosCom(memory[reg[tempReg[RS]] + tempReg[IMM]]);
				printf("fsfds %d\n", resultInt);
				reg[tempReg[0]] = resultInt;
				reg[16]++;
			}
			else if(memory[PC][0] == SW)
			{
				placeInTempReg(tempReg, memory[PC]);
				convertDecToHex2(reg[tempReg[RD]], temp, 8);
				strcpy(memory[reg[tempReg[RS]] + tempReg[IMM]], temp);

				reg[16]++;
			}
			else
			{
				performCommand(memory[PC], reg);
				printf("new pc is: %d\n", reg[16]);
			}

			PC = reg[16];
		}
	}

	fclose(memin);
	for(i = 0; i < 4; i++)
	{
		fclose(files[i]);
	}


}

void updateTrace(const int* reg, FILE* traceOut,char* inst)
{
	static int a = 1;
	printf("traced: %d\n", a);
	a++;
	char line[(MEMORY_WORD_LENGTH + 2) * (NUM_OF_REGS + 2)];
	line[0] = '\0';

	char hexLine[9];
	// reg[16] is the pc
	convertDecToHex2(reg[16], hexLine, 8);
	strcat(line, hexLine);
	strcat(line, " ");
	strcat(line, inst);
	strcat(line, " ");
	int i;
	for(i = 0; i < NUM_OF_REGS; i++)
	{
		hexLine[0] = '\0';
		convertDecToHex2(reg[i], hexLine, 8);
		strcat(line, hexLine);
		strcat(line, " ");
	}

	strcat(line, "\n");

	fprintf(traceOut, line);

	return;
}

void convertDecToHex2(int a, char* result, int len)
{
	int i;
	int t;
	int mask = 15;
	for(i = len - 1; i >= 0; i--)
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
	result[len] = '\0';

}

void printToRegout(int* reg, FILE* regout)
{

	for( int i = 0;i<16;++i)
	{
//		if(i !=15)
//		{
			fprintf(regout, "%x\n", reg[i]);
//		}
//		else
//		{
//			fprintf(regout, "%x", reg[i]);
//		}
	}
	return;
}

void placeInTempReg(int* reg, char* line)
{
	int i = 0;
	for (i = 0 ; i<3 ; ++i)
	{
		reg[i] = charToInt(line[i+1]);
	}
	char* imm = line + 4;
	reg[3] = convertHexToIntTwosCom(imm);

}

void performCommand(char* line, int* reg)
{
	int tempReg[4] = {0};//temReg[0] = rd, tempReg[1] = rs tempReg[2] = rt; tempReg[3] = imm; - decimal

	bool toAdvancePC = true;
	placeInTempReg(tempReg, line);
	printf("placed\n");
	if (line[0] == ADD)//add
	{
		if(tempReg[RD])
		{
			reg[tempReg[RD]] = reg[tempReg[RS]] + reg[tempReg[RT]];
		}
	}
	else if (line[0] == SUB)
	{
		if(tempReg[RD])
		{
			reg[tempReg[RD]] = reg[tempReg[RS]] - reg[tempReg[RT]];
		}
	}
	else if (line[0] == AND)
	{
		if(tempReg[RD])
		{
			reg[tempReg[RD]] = reg[tempReg[RS]] & reg[tempReg[RT]];
		}
	}
	else if (line[0] == OR)
	{
		if(tempReg[RD])
		{
			reg[tempReg[RD]] = reg[tempReg[RS]] | reg[tempReg[RT]];

		}
	}
	else if (line[0] == SLL)
	{
		if(tempReg[RD])
		{
			reg[tempReg[RD]] = reg[tempReg[RS]] << reg[tempReg[RT]];
		}
	}
	else if (line[0] == SRA)
	{
		if(tempReg[RD])
		{
			reg[tempReg[RD]] = reg[tempReg[RS]] >> reg[tempReg[RT]];

		}
	}
	else if (line[0] == LIMM)
	{
		if(tempReg[RD])
		{
			reg[tempReg[RD]] = tempReg[IMM];
		}
	}
	else if (line[0] == BEQ)
	{
		printf("beq: reg[tempReg[1]]=%d reg[tempReg[2]]=%d tempReg[3] = %d\n", reg[tempReg[1]], reg[tempReg[2]], tempReg[3]);
		if(reg[tempReg[RS]] == reg[tempReg[RT]])
		{
			reg[16] = tempReg[IMM];
			toAdvancePC = false;
		}
	}
	else if (line[0] == BGT)
	{
		printf("bgt: reg[tempReg[1]]=%d reg[tempReg[2]]=%d tempReg[3] = %d\n", reg[tempReg[1]], reg[tempReg[2]], tempReg[3]);
		if(reg[tempReg[RS]] > reg[tempReg[RT]])
		{
			reg[16] = tempReg[IMM];
			toAdvancePC = false;
		}
	}
	else if (line[0] == BLE)
	{
		if(reg[tempReg[RS]] <= reg[tempReg[RT]])
		{
			reg[16] = tempReg[IMM];
			toAdvancePC = false;
		}
	}
	else if (line[0] == BNE)
	{
		if(reg[tempReg[RS]] != reg[tempReg[RT]])
		{
			reg[16] = tempReg[IMM];
			toAdvancePC = false;
		}
	}
	else if (line[0] == JAL)
	{
		reg[15] = reg[16]+1;
		printf("jal imm=%d\n", tempReg[IMM]);
		reg[16] = tempReg[IMM];
		toAdvancePC = false;
	}
	else if (line[0] == JR)
	{
		reg[16] = reg[tempReg[RD]];
		toAdvancePC = false;
	}
	else if (line[0] == HALT)
	{
		return;
	}
	else
	{
		printf("ERROR!!!!!\n");
	}

	if(toAdvancePC)
	{
		reg[16]++;
	}

	printf("done performing\n");
}

int convertHexToIntTwosCom(char* tempString)
{
	if(!tempString)
	{
		return -1;
	}
	int i;
	int j;
	int t = 0;
	int ans = 0;
	char nums[] = "0123456789ABCDEF";

	for(i = strlen(tempString) - 1; i>= 0; i--)
	{
		if(tempString[i] == 0)
		{
			break;
		}
		for(j = 0; j < strlen(nums); j++)
		{
			if (tempString[i] == nums[j])
			{
				t = j;
				break;
			}
		}
		ans += (int)pow(16, strlen(tempString) - 1 - i) * t;
	}

	if(tempString[0] >= '8')
	{
		printf("yoyo\n");
		ans -= (int)pow(2, strlen(tempString) * 4);
	}

	return ans;
}

int charToInt(char a)
{
	if ((a>='0') && (a<='9'))
	{
		return a -'0';
	}
	return a -'A' + 10;
}

