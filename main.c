#include <stdio.h>
#include <stdlib.h>
#include "asm.h"

int main(int argc, char** argv)
{
	char* a = parseCommand("good 	bad bad very bad, moy bad");
	printf("yo\n");
	printf("comm: %s.", a);
	return 1;
}
