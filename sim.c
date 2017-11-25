
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
	int reg[16] = {0};

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
