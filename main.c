#include <stdio.h>
#include <stdlib.h>
#include "asm.h"
#include <regex.h>
//we made several strcpy in small functions, should we free their memory?

int main(int argc, char** argv)
{
	char b[] = "64374823fsdfdsfsdfdsdd";

	int a = atoi(b);

	printf("%d\n", a);

}
