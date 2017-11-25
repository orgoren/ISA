#include <stdio.h>
#include <stdlib.h>
#include "asm.h"
#include <regex.h>
#include <assert.h>

//we made several strcpy in small functions, should we free their memory? NO


int main(int argc, char** argv)
{

	readFile(argv[1], argv[2]);

	//labelList* l = createLabelList();

	//addLastToList(l, createLabelNode(5, "ee"));

	//printList(l);

}
