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

	int i = convertHexToIntTwosCom("FFFFAB123");
	char* str;
	convertDecToHex(12, str, 4);
	printf("%s\n", str);
}
