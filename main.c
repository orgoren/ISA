#include <stdio.h>
#include <stdlib.h>
#include "asm.h"
#include "sim.h"
#include <regex.h>
#include <assert.h>

//we made several strcpy in small functions, should we free their memory? NO



int main(int argc, char** argv)
{
	assert(argc == 6);

	sim(argc, argv);



}
