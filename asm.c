#include "asm.h"

void parseCommand(const char* cmd, char* result)
{
	char line[500];
	char s[] = " ,\t\r\n";
	strcpy(line, cmd);
	char* opcodeStr = strtok(line, s);
	char* rdStr = strtok(NULL, s);
	char* rsStr = strtok(NULL, s);
	char* rtStr = strtok(NULL, s);
	char* immStr = strtok(NULL, s);

	char opcode = convertOpcode(opcodeStr);

	char rd = convertRegister(rdStr);
	char rt = convertRegister(rtStr);
	char rs = convertRegister(rsStr);
	printf("rs = %d\n", rs);
	char imm[5];
	convertImmediate(immStr, imm);

	printf("rs=%s\n", rsStr);
	printf("opcode=%c, rd=%c, rs=%c, rt=%c\n", opcode, rd, rs, rt);

	result[0] = opcode;
	result[1] = rd;
	result[2] = rs;
	result[3] = rt;
	result[4] = imm[0];
	result[5] = imm[1];
	result[6] = imm[2];
	result[7] = imm[3];
	result[8] = '\0';
}

char convertRegister(char* reg)
{
	printf("reg=%s\n", reg);
	if(!strcmp(reg, "$zero"))
	{
		return '0';
	}
	else if (!strcmp(reg, "$at"))
	{
		return '1';
	}
	else if(!strcmp(reg, "$v0"))
	{
		return '2';
	}
	else if(!strcmp(reg, "$a0"))
	{
		return '3';
	}
	else if (!strcmp(reg, "$a1"))
	{
		return '4';
	}
	else if(!strcmp(reg, "$t0"))
	{
		return '5';
	}
	else if(!strcmp(reg, "$t1"))
	{
		return '6';
	}
	else if(!strcmp(reg, "$t2"))
	{
		return '7';
	}
	else if(!strcmp(reg, "$t3"))
	{
		return '8';
	}
	else if (!strcmp(reg, "$s0"))
	{
		return '9';
	}
	else if(!strcmp(reg, "$s1"))
	{
		return 'A';
	}
	else if(!strcmp(reg, "$s2"))
	{
		return 'B';
	}
	else if(!strcmp(reg, "$gp"))
	{
		return 'C';
	}
	else if(!strcmp(reg, "$sp"))
	{
		return 'D';
	}
	else if(!strcmp(reg, "$fp"))
	{
		return 'E';
	}
	else if(!strcmp(reg, "$ra"))
	{
		return 'F';
	}

	return (char)16;
}

char convertOpcode(char* opcode)
{
	if(!strcmp(opcode, "add"))
	{
		return '0';
	}
	else if(!strcmp(opcode, "sub"))
	{
		return '1';
	}
	else if(!strcmp(opcode, "and"))
		{
			return '2';
		}
	else if(!strcmp(opcode, "or"))
		{
			return '3';
		}
	else if(!strcmp(opcode, "sll"))
		{
			return '4';
		}
	else if(!strcmp(opcode, "sra"))
		{
			return '5';
		}
	else if(!strcmp(opcode, "limm"))
		{
			return '6';
		}
	else if(!strcmp(opcode, "beq"))
		{
			return '7';
		}
	else if(!strcmp(opcode, "bgt"))
		{
			return '8';
		}
	else if(!strcmp(opcode, "ble"))
		{
			return '9';
		}
	else if(!strcmp(opcode, "bne"))
		{
			return 'A';
		}
	else if(!strcmp(opcode, "jal"))
		{
			return 'B';
		}
	else if(!strcmp(opcode, "lw"))
		{
			return 'C';
		}
	else if(!strcmp(opcode, "sw"))
		{
			return 'D';
		}
	else if(!strcmp(opcode, "jr"))
		{
			return 'E';
		}
	else if(!strcmp(opcode, "halt"))
		{
			return 'F';
		}
	return 'G';
}

void convertDecToHex(int a, char* result)
{
	int i;
	int t;
	int mask = 15;
	for(i = 3; i >= 0; i--)
	{
		t = mask & a;
		if (t > 9)
		{
			result[i] = 'A' + t - 10;
		}
		else
		{
			result[i] = '0' + (char)(mask & a);
		}

		a >>= 4;
	}
	result[4] = '\0';

}

void convertImmediate(char* imm, char* result)
{
	if((imm[0] == '0') &&(imm[1] = 'x'))
	{
		//result = imm + 2;
		result[0] = imm[2];
		result[1] = imm[3];
		result[2] = imm[4];
		result[3] = imm[5];
		result[4] = '\0';

	}
	else
	{
		convertDecToHex(atoi(imm), result);
	}
}

//void* updatingLabelsArray(char* labels[65300])


int isThereLabelInIt(char* getline,char* label)
{
	// return 0 if there is no label
	// return 1 if there is label but no cmd in this line
	// return 2 if there is a label and cmd in this line
	//return 3 if there is a command and no label
	// what about a line with two labels, one in the first word and one in the immediate?  ignore!
	char line[500];
	char s[] = " ,\t\r\n";
	strcpy(line, getline);
	char* firstWord = strtok(line, s);
	char* secondWord;
	int tempCheckIsCmd = 0;
	int lenword = strlen(firstWord);
	if( firstWord[0] == '#')
	{
		printf("there is no label in the first word here");
		return 0;
	}
	if(firstWord[lenword-1] == ':') //check if the first word in line is a label
	{
		strcpy(label, firstWord);
		label[lenword] = '\0';
		secondWord = strtok(line, s);
		if(!secondWord)
		{
			printf("there is no legal optcode in this line, step forward");
			return 1;
		}
		else if (secondWord[0] =='#')
		{
			printf("there is no legal optcode in this line, step forward");
			return 1;
		}
		else
		{
			tempCheckIsCmd = isCMD(secondWord);
			if(tempCheckIsCmd == 1)
			{
				printf("there is cmd and label in this line");
				return 2;
			}
			else if(tempCheckIsCmd == -1)
			{
				printf("there is WORD CMD");
				return 1;
			}
			else
			{
				return 0; ///////////////////////////////////not true
			}
		}
	}
	else
	{
		if (isCMD(firstWord) == 1)
		{
			printf("there is only command but no label");
			return 3;
		}
		else{
			return 0;
		}
	}
	 // check if the there is a legal command in this line (before the label)
//	int optNumber = isCMD(firstWord);
//	if(optNumber != -1)
//	{
//		if (optNumber == 1)
//		{
//			printf("there is a branch cmd - need to remember relative jump");
//			getImm(firstWord, imm); //jump to immm and check if it a label
//
//		}
//	}
}

void changeLine(char* currLine, int labelIndex, int lineIndex, bool isRel, char* newLine)
{
	//should i jump 4 strtok to imm?
	if(isRel)
	{
		//goren goren goren
	}
	else
	{

	}
}
//void getImm(char* firstWord, char* imm)
//{
//	//not sure the logic is right(suppose to retrieve the imm based on the optcode(=firstWord)
//	char line[500];
//	char s[] = " ,\t\r\n";
//	strcpy(line, firstWord);
//	char* rdStr = strtok(NULL, s);
//	char* rsStr = strtok(NULL, s);
//	char* rtStr = strtok(NULL, s);
//	char* immStr = strtok(NULL, s);
//	imm = immStr;
//}

//int isThereACommand(char* firstWord)
//{
//	if(firstWord[0] == '#')
//	{
//		printf("there is a no command here");
//		return 0;
//	}
//	else
//	{
//		printf("there is a command here");
//		return 0;
//	}
//}

bool isBufferHasLabel(char* line, char* label)
{
	char s[] = " ,\t\r\n";
	char* oc = strtok(line, s);
	char* r1 = strtok(NULL, s);
	char* r2 = strtok(NULL, s);
	char* r3 = strtok(NULL, s);
	char* im = strtok(NULL, s);
	if(!im)
	{
		return false;
	}
	if(strlen(im) == 1)
	{
		if (im[0] >= '0' && im[0] <= '9')
		{
			return false;
		}
		else
		{
			strcpy(label, im);
			return true;
		}
	}

	if((im[0] >= 'A' && im[0] <= 'Z') || (im[1] >= 'a' && im[0] <= 'z'))
	{
		return true;
	}

	strcpy(label, im);
	return false;
}

int isCMD(char* firstWord)
{
	if((strlen(firstWord) > 4) || (strlen(firstWord) < 2))
	{
		printf("the word we get is not a cmd");
		return -1;
	}
	char cmd[4];
	strcpy(cmd, firstWord);
	//should we check the strcpy success?
	if(strcmp(cmd, "WORD") == 0)
	{
		return -1;
	}
	else
	{
		return 1;
	}
}

int whichOptCode(char* Word)
{
	//return -1 if there is cmd "WORD"
	// return 0 if there is any other cmd
	//return 1 if there is relative jump
	//return 2 if there is absolute jump
	if((Word[0] == '#') || (strcmp(Word, "WORD") == 0))
	{
		return -1;
	}
	if((strcmp(Word, "beq") == 0)||(strcmp(Word, "bgt") == 0)||(strcmp(Word, "ble") == 0)||(strcmp(Word, "bne") == 0))
	{
		return 1;
	}
	if((strcmp(Word, "jal") == 0)||(strcmp(Word, "jr") == 0)) //what about ld and sw?
	{
		return 2;
	}
	return 0;
}


void readFile(char* path)
{
	FILE* f;
	char buffer[MAX_ROW_LENGTH];
	char newLine[MAX_ROW_LENGTH];
	char* firstWord;
	int i, labelIndex;
	char s[] = " ,\t\r\n";
	f = fopen(path, "r");
	int cmdCounter = 0;
	if(!f)
	{
		printf("Can't open File\n");
		return;
	}
	int tempcheck = 0;
	char* labels[MAX_ROWS];
	char label[MAX_LABEL_LENGTH];
	while(fgets(buffer, MAX_ROW_LENGTH, f))
	{
		if(!strcmp(buffer, ""))
		{
			continue;
		}
		tempcheck = isThereLabelInIt(buffer,label);
		if(tempcheck ==1)
		{
			labels[cmdCounter] = label; //is that the right way to insert a string to an array?
		}
		else if (tempcheck == 2)
		{
			labels[cmdCounter] = label;
			cmdCounter++;
		}
		else if(tempcheck == 3)
		{
			cmdCounter++;
		}
	}
	cmdCounter = 0;
	fseek(f, 0, SEEK_SET);
	while(fgets(buffer, MAX_ROW_LENGTH, f))
	{
		firstWord = strtok(buffer, s);
		if((!firstWord))
		{
			continue;
		}

		if(isBufferHasLabel(buffer, label))
		{
			for(i = 0; i < MAX_ROWS; i++)
			{
				if(!(strcmp(label, labels[i])))
				{
					labelIndex = i;
					break;
				}
			}

			tempcheck = whichOptCode(firstWord);
			if(tempcheck == -1)
			{
				continue;
			}

			if(tempcheck == 1)
			{
				changeLine(buffer, labelIndex, cmdCounter, true, newLine);
			}
			else if(tempcheck == 2)
			{
				changeLine(buffer, labelIndex, cmdCounter, false, newLine);
			}
			cmdCounter++;
		}
	}
	//close the file?
}
