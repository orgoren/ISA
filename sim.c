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
	char opt;
	bool endOfFile = false;
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
	while(!endOfFile)
	{
		if(strcmp(memory[PC],"F0000000") == 0)//we got halt
		{
			counter++;
			fprintf(files[3], "&d", counter);
			close(files[3]);
			printToRegout(reg, files[1]);
			close(files[1]);
			//copy memory to memout (file[0])
		}
		else
		{
			reg[16] = PC;//update pc adress to reg array
			opt = line[0];
			updateTrace(reg, files[2], opt);
			performCommand(memory[PC], reg, memory);
			counter++;
		}

	}

}

void updateTrace(const int* reg, FILE* regout,const char opt)
{
// pc is in reg[last] as unsigned int
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

void printToRegout(const char* reg, FILE* regout)
{

	for( int i = 0;i<16;++i)
	{
		if(i !=15)
		{
			fprintf(regout, "%x\n", reg[i]);
		}
		else
		{
			fprintf(regout, "%x", reg[i]);
		}
	}
	return;
}

void placeInTempReg(int* reg, const char* line)
{
	int i = 0;
	for (i = 0 ; i<3 ; ++i)
	{
		reg[i] = charToInt(line[i+1]);
	}
	char* imm = line + 4;
	reg[3] = convertHexToIntTwosCom(imm);

}

void performCommand(const char* line, int* reg, char** memory)//reg[16] = pc
{
	int tempReg[4] = {0};//temReg[0] = rd, tempReg[1] = rs tempReg[2] = rt; tempReg[3] = imm; - decimal
	char imm[4];
	int resultInt = 0;
	placeInTempReg(tempReg, line);
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
		resultInt = convertHexToIntTwosCom(memory[reg[tempReg[1]]+tempReg[3]]);
		reg[tempReg[0]] = resultInt; // need to convert decimal to char
	}
	else if (line[0] == 'D')//sw
	{
		convertDecToHex2(reg[tempReg[0]], imm, 4);
		strcpy(memory[reg[tempReg[1]]+tempReg[3]], imm); // need to convert decimal to char
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

	//char mask = 'F';
	//int b = mask & tempString[0];
	//printf("b=%d\n", b);
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
//	if(a>="A")
//	{
//		return a - "A" +10;
//	}
}
