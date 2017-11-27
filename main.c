#include <stdio.h>
#include <stdlib.h>
#include "asm.h"
#include "sim.h"
#include <regex.h>
#include <assert.h>

//we made several strcpy in small functions, should we free their memory? NO


int main(int argc, char** argv)
{
//	void placeInTempReg(int* reg, const char* line)

	int reg [4] = {0};

//	char* line = "F20AAB12";
	char* line = "22";

	placeInTempReg(reg, line);

	int i = 0;
	for(i = 0; i < 4; i++)
	{
		printf("%d\t", reg[i]);
	}
	printf("\n");
	char a = line[0];
	printf("%c", a);



}
