#include <stdio.h>
#include <stdlib.h>
#include "asm.h"

//we made several strcpy in small functions, should we free their memory?

int main(int argc, char** argv)
{
	/*
//	char* a = parseCommand("good 	bad bad very bad, moy bad");
	char* b = "0xff12";
//	int i = atoi(b);
//	printf("num i: %d", i);
	b = b + 2;
	printf("b: %s", b);
	printf("yo\n");
//	printf("comm: %s.", a);
	return 1;
	*/

	char* a = "add $a0 $t2 $s2 1234";
	char* b = "label34:";
	int d = strlen(b);
	printf("len: %d", d);

//	char* a = "add $a0 $t2 $s2 1234";

//	char result[9];

//	parseCommand(a, result);

//	printf("result: %s\n", result);

	readFile("Debug/aaa");
}
