#include <stdio.h>
#include <stdlib.h>
#include "asm.h"
#include "sim.h"
#include <regex.h>
#include <assert.h>

//we made several strcpy in small functions, should we free their memory? NO


int main(int argc, char** argv)
{
//	char b = "A";
//	char a = "0";

//	int k = charToInt(b);
//	int y = charToInt(a);
//	int a = 0x12;
	///printf("digit1 %d\n", k);
	//printf("digit2 %d\n", y);
	//int c = atoi(b);
	//printf("string %d\n", c);
	//readFile(argv[1], argv[2]);

	//labelList* l = createLabelList();

	//addLastToList(l, createLabelNode(5, "ee"));

	//printList(l);

	int k = charToInt('A');
	int j = charToInt('F');
	int l = charToInt('0');
	int m = charToInt('9');
//	int i = convertHexToIntTwosCom("FFFFAB123");
	printf("A: %d\n", k);
	printf("F: %d\n", j);
	printf("0: %d\n", l);
	printf("9: %d\n", m);
}
