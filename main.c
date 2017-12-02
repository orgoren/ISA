#include <stdio.h>
#include <stdlib.h>
#include "asm.h"
#include "sim.h"
#include <regex.h>
#include <assert.h>

//we made several strcpy in small functions, should we free their memory? NO

#define SIM 1


int main(int argc, char** argv)
{
	//assert(argc == 6);

	if(SIM)
	{
		sim(argc, argv);
	}
	else
	{
		readFile(argv[6], argv[1]);
	}
}
