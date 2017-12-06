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
	char zeroes[] = "00000000";
	char memory[MAX_ROWS][MEMORY_WORD_LENGTH + 2];
	bool endOfFile = false;
	int reg[17] = {0};

	// Opens memin file
	memin = fopen(argv[1], "r");
	if(!memin)
	{
		printf("Can't open File %s\n", argv[1]);
		return 0;
	}

	// Save to memory the lines from the file memin
	while(fgets(line, MEMORY_WORD_LENGTH+2, memin))
	{
		strcpy(memory[i],line);
		memory[i][8] = '\0';
		++i;
	}

	// Afterwards continue filling the memory with zeroes
	for(; i < MAX_ROWS; i++)
	{
		strcpy(memory[i], zeroes);
	}

	// Open all the output files.
	for (i = 0; i<4; ++i)
	{
		files[i] = fopen(argv[i+2], "w");
		if(!files[i])
		{
			printf("Can't open File %s\n", argv[i+2]);
		}
	}


	// Start parsing the memin instructions and execute them accordingly
	i = 0;
	PC = 0;
	while(!endOfFile)
	{
		counter++;

		// Write the instruction to the trace file - before it changes the regs.
		updateTrace(reg, files[TRACE_OUT], memory[PC]);

		// On Halt
		if(memory[PC][0] == 'F')
		{
			// Write the #inst to count file
			fprintf(files[COUNT_OUT], "%d\n", counter);

			// Write the regs values to regout file
			printToRegout(reg, files[REG_OUT]);

			// Write the memory to memout
			for(i = 0; i < MAX_ROWS; i++)
			{
				fprintf(files[MEM_OUT], "%s\n", memory[i]);
			}

			endOfFile = true; //it'll exit from the while loop
		}
		else
		{
			// The instruction is loadWord
			if(memory[PC][0] == LW)
			{
				// get the registers from the instructions and save them to tempReg
				placeInTempReg(tempReg, memory[PC]);

				// resultInt = (int)mem[R(RS)+imm];
				resultInt = convertHexToIntTwosCom(memory[reg[tempReg[RS]] + tempReg[IMM]]);

				// R(RD) = mem[R(RS)+imm]
				reg[tempReg[RD]] = resultInt;

				// PC++
				reg[PC_REG]++;
			}
			// The instruction is StoreWord
			else if(memory[PC][0] == SW)
			{
				// get the registers from the instructions and save them to tempReg
				placeInTempReg(tempReg, memory[PC]);

				// temp = (hex)R(RD)
				convertDecToHex2(reg[tempReg[RD]], temp, 8);

				// memory[R(RS)+imm] = R(RD)
				strcpy(memory[reg[tempReg[RS]] + tempReg[IMM]], temp);

				// PC++
				reg[PC_REG]++;
			}
			// All other instructions are taken care of in 'performCommand' func
			else
			{
				performCommand(memory[PC], reg);
			}

			// Update the PC value
			PC = reg[PC_REG];
		}
	}

	// Close all files
	fclose(memin);
	for(i = 0; i < 4; i++)
	{
		fclose(files[i]);
	}


}

void updateTrace(const int* reg, FILE* traceOut,char* inst)
{
	char line[(MEMORY_WORD_LENGTH + 2) * (NUM_OF_REGS + 2)];
	line[0] = '\0';

	char hexLine[9];

	convertDecToHex2(reg[PC_REG], hexLine, 8); // hexLine now contains the hex value of PC

	strcat(line, hexLine);
	strcat(line, " ");
	strcat(line, inst);
	strcat(line, " ");
	int i;
	for(i = 0; i < NUM_OF_REGS; i++)
	{
		hexLine[0] = '\0';
		convertDecToHex2(reg[i], hexLine, 8);	// hexLine now contains next reg hex value within 8 letters.
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
		t = mask & a;	// t will contain the 4 lsb of a
		if (t > 9)
		{
			result[i] = 'A' + t - 10;
		}
		else
		{
			result[i] = '0' + (char)(mask & a);
		}

		a >>= 4;		// get next "hex" value - every hex char is defined by 4 bits
	}
	result[len] = '\0';

}

void printToRegout(int* reg, FILE* regout)
{
	if(!reg || !regout)
	{
		return;
	}
	int i = 0;
	for(int i = 0; i < 16 ; ++i)
	{
		fprintf(regout, "%x\n", reg[i]);
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
	int tempReg[4] = {0};

	bool toAdvancePC = true;
	placeInTempReg(tempReg, line);
	if (line[0] == ADD)
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
		if(reg[tempReg[RS]] == reg[tempReg[RT]])
		{
			reg[PC_REG] = tempReg[IMM];
			toAdvancePC = false;		// the pc has changed so no need to advance it
		}
	}
	else if (line[0] == BGT)
	{
		if(reg[tempReg[RS]] > reg[tempReg[RT]])
		{
			reg[PC_REG] = tempReg[IMM];
			toAdvancePC = false;		// the pc has changed so no need to advance it
		}
	}
	else if (line[0] == BLE)
	{
		if(reg[tempReg[RS]] <= reg[tempReg[RT]])
		{
			reg[PC_REG] = tempReg[IMM];
			toAdvancePC = false;		// the pc has changed so no need to advance it
		}
	}
	else if (line[0] == BNE)
	{
		if(reg[tempReg[RS]] != reg[tempReg[RT]])
		{
			reg[PC_REG] = tempReg[IMM];
			toAdvancePC = false;		// the pc has changed so no need to advance it
		}
	}
	else if (line[0] == JAL)
	{
		reg[RA_REG] = reg[PC_REG]+1;
		reg[PC_REG] = tempReg[IMM];
		toAdvancePC = false;		// the pc has changed so no need to advance it
	}
	else if (line[0] == JR)
	{
		reg[PC_REG] = reg[tempReg[RD]];
		toAdvancePC = false;		// the pc has changed so no need to advance it
	}
	else if (line[0] == HALT)
	{
		return;
	}

	if(toAdvancePC)
	{
		reg[PC_REG]++;
	}
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
		// Check if it's the end
		if(tempString[i] == 0)
		{
			break;
		}

		// t would be the dec of tempString[i]
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

	// Because it's two-complement we need to check whether the msb of the imm is 1
	// And calculate accordingly
	if(tempString[0] >= '8')
	{
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

