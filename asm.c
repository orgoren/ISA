#include "asm.h"

void parseCommand(const char* cmd, char* result)
{
	char line[500];
	char s[] = " ,\t\r\n";
	strcpy(line, cmd);
	printf("parseCommand: line is: %s\n", line);
	char* opcodeStr = strtok(line, s);
	char* rdStr = strtok(NULL, s);
	char* rsStr = strtok(NULL, s);
	char* rtStr = strtok(NULL, s);
	char* immStr = strtok(NULL, s);

	char opcode = convertOpcode(opcodeStr);

	char rd = convertRegister(rdStr);
	char rt = convertRegister(rtStr);
	char rs = convertRegister(rsStr);
	char imm[5];
	char label[MAX_LABEL_LENGTH];
	strcpy(line, cmd);
	if (!isBufferHasLabel(line, label))
	{
		printf("convert\n");
		convertImmediate(immStr, imm);
	}
	result[0] = opcode;
	result[1] = rd;
	result[2] = rs;
	result[3] = rt;
	result[4] = imm[0];
	result[5] = imm[1];
	result[6] = imm[2];
	result[7] = imm[3];
	result[8] = '\0';
	printf("finnaly the result is: %s\n", result);
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
	printf("opcode is: %s\n", opcode);
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

void convertDecToHex(int a, char* result, int len)
{
	int i;
	int t;
	int mask = 15;
	for(i = len - 1; i >= 0; i--)
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
	result[len] = '\0';

}

int convertHexRowIndexToDec(const char* hexRowIndex)
{
	if(!hexRowIndex)
	{
		return -1;
	}
	int i;
	int j;
	int t = 0;
	int ans = 0;
	char nums[] = "0123456789ABCDEF";

	for(i = strlen(hexRowIndex) - 1; i>= 0; i--)
	{
		if(hexRowIndex[i] == 0)
		{
			break;
		}
		for(j = 0; j < strlen(nums); j++)
		{
			if (hexRowIndex[i] == nums[j])
			{
				t = j;
				break;
			}
		}
			ans += (int)pow(16, strlen(hexRowIndex) - 1 - i) * t;
	}

	return ans;
}

bool isHex(char* num)
{
	if(!num)
	{
		return false;
	}
	if(strlen(num) == 1)
	{
		return false;
	}

	if(num[0] == '0' && num[1] == 'x')
	{
		return true;
	}

	return false;
}

void convertImmediate(char* imm, char* result)
{

	//if((imm[0] == '0') &&(imm[1] == 'x'))
	if(isHex(imm))
	{
		printf("yoyo\n");
		//result = imm + 2;
		result[0] = imm[2];
		result[1] = imm[3];
		result[2] = imm[4];
		result[3] = imm[5];
		result[4] = '\0';

	}
	else
	{
		printf("imm is a dec number\n");
		convertDecToHex(atoi(imm), result, 4);
	}
	printf("imm = %s, result = %s\n", imm, result);
}

int isThereLabelInIt(char* getline,char* label)
{
	// return 0 if there is no label
	// return 1 if there is label but no cmd in this line
	// return 2 if there is a label and cmd in this line
	//return 3 if there is a command and no label
	// what about a line with two labels, one in the first word and one in the immediate?  ignore!
	char line[MAX_ROW_LENGTH];
	char s[] = " ,\t\r\n";
	strcpy(line, getline);
	char* firstWord = strtok(line, s);
	char* secondWord;
	int tempCheckIsCmd = 0;
	int lenword = strlen(firstWord);
	if( firstWord[0] == '#')
	{
		printf("there is no label in the first word here\n");
		return 0;
	}
	if(firstWord[lenword-1] == ':') //check if the first word in line is a label
	{
		strcpy(label, firstWord);
		label[lenword] = '\0';
		secondWord = strtok(line, s);
		if(!secondWord)
		{
			printf("there is no legal optcode in this line, step forward\n");
			return 1;
		}
		else if (secondWord[0] =='#')
		{
			printf("there is no legal optcode in this line, step forward\n");
			return 1;
		}
		else
		{
			tempCheckIsCmd = isCMD(secondWord);
			if(tempCheckIsCmd == 1)
			{
				printf("there is cmd and label in this line\n");
				return 2;
			}
//			else if(tempCheckIsCmd == -1)
			else
			{
				printf("there is WORD CMD\n");
				return 1;
			}
		}
	}
	else
	{

		if (isCMD(firstWord) == 1)
		{
			printf("there is only command but no label\n");
			return 3;
		}
		else
		{
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
	char s[] = " ,\t\r\n";
	char* opcodeStr = strtok(currLine, s);
	char* rdStr = strtok(NULL, s);
	char* rsStr = strtok(NULL, s);
	char* rtStr = strtok(NULL, s);
	char p[] = ", ";
	char labelReplace[2];
	int labelLines;
	strcat(newLine, opcodeStr);
	strcat(newLine, p);
	strcat(newLine, rdStr);
	strcat(newLine, p);
	strcat(newLine, rsStr);
	strcat(newLine, p);
	strcat(newLine, rtStr);
	strcat(newLine, p);

	if(isRel)
	{
		labelLines = labelIndex - lineIndex;
	}
	else
	{
		labelLines = labelIndex;
	}

	convertDecToHex(labelLines, labelReplace, 4);
	strcat(newLine, labelReplace);

}

bool isBufferHasLabel(char* line, char* label)
{
	printf("isBufferHashLabel: line is %s\n", line);
	char s[] = " ,\t\r\n";
	char* oc = strtok(line, s);
	char* r1 = strtok(NULL, s);
	char* r2 = strtok(NULL, s);
	char* r3 = strtok(NULL, s);
	char* im = strtok(NULL, s);



	if(oc[1] == '#')
	{
		printf("isBufferhasLabel: the first word has #\n");
		return false;
	}

	if(!im)
	{
		return false;
	}

	printf("imm length: %d and is: %s\n", strlen(im), im);

	if(strlen(im) == 1)
	{
		if (im[0] >= '0' && im[0] <= '9')
		{
			printf("it doesn't have a label and its a number\n");
			return false;
		}
		else
		{
			strcpy(label, im);
			return true;
		}
	}

	if((im[0] >= 'A' && im[0] <= 'Z') || (im[0] >= 'a' && im[0] <= 'z'))
	{
		strcpy(label, im);
		return true;
	}


	return false;
}

int isCMD(char* firstWord)
{
	if((strlen(firstWord) > 4) || (strlen(firstWord) < 2))
	{
		printf("the word we get is not a cmd\n");
		return -1;
	}
	char cmd[5];
	strcpy(cmd, firstWord);
	//should we check the strcpy success?
	if(strcmp(cmd, ".word") == 0)
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

void deleteFirstWordFromLine(char* line, char* newLine)
{
	char temp[MAX_ROW_LENGTH];
	strcpy(temp, line);
	char s[] = " ,\t\r\n";
	char p[] = ", ";
	char* t1 = strtok(temp, s);
	char* t2 = strtok(NULL, s);
	char* t3 = strtok(NULL, s);
	char* t4 = strtok(NULL, s);
	char* t5 = strtok(NULL, s);
	char* t6 = strtok(NULL, s);

	newLine[0] = '\0';

	strcat(newLine, t2);
	strcat(newLine, p);
	strcat(newLine, t3);
	strcat(newLine, p);
	strcat(newLine, t4);
	strcat(newLine, p);
	strcat(newLine, t5);
	strcat(newLine, p);
	strcat(newLine, t6);

	t1 = NULL;
}

void parseWordCommand(char* command, const char** memory)
{
	char temp[MAX_ROW_LENGTH];
	char s[] = ", \t\r\n";
	strcpy(temp, command);
	char* w = strtok(temp, s);
	char* address = strtok(NULL, s);
	char* data = strtok(NULL, s);
	int addr;
	char dat[8];
	if(isHex(address))
	{
		addr = convertHexRowIndexToDec(address);
	}
	else
	{
		addr = atoi(address);
	}

	if(isHex(data))
	{

	}

}

void readFile(char* path,char* path_out)
{
	FILE* f;
	FILE* output;
	char hexline[15] = {0};
	output = fopen(path_out, "w");
	if(!output)
	{
		printf("Can't open File %s\n", path_out);
		return;
	}
	char buffer[MAX_ROW_LENGTH];
	char bufferCopy[MAX_ROW_LENGTH];
	char newLine[MAX_ROW_LENGTH];
	char memory[MAX_ROWS][MEMORY_WORD_LENGTH + 1];
	int maxRowInMem = -1;
	char* firstWord;
	char* secondWord;
	char* thirdWord;
	char hexLine[MEMORY_WORD_LENGTH + 1];
	int addr;
	char zeros[] = "00000000";
	int labelIndex, i;
	char s[] = " ,\t\r\n";
	f = fopen(path, "r");
	int cmdCounter = 0;
	if(!f)
	{
		printf("Can't open File %s\n", path);
		return;
	}
	int tempcheck = 0;

	labelList* labelsList = createLabelList();

	char label[MAX_LABEL_LENGTH];

	while(fgets(buffer, MAX_ROW_LENGTH, f))
	{
		printf("line is: %s", buffer);

		if(!strcmp(buffer, "") || (!strcmp(buffer, "\n")))
		{
			continue;
		}

		tempcheck = isThereLabelInIt(buffer,label);
		if(tempcheck ==1)
		{
//			labels[cmdCounter] = label; //is that the right way to insert a string to an array?
//			strcpy(labels[cmdCounter], label);
			printf("We Have label HERE!!!!!!\n");
			addLastToList(labelsList, createLabelNode(cmdCounter, label));
		}
		else if (tempcheck == 2)
		{
//			labels[cmdCounter] = label;
//			strcpy(labels[cmdCounter], label);
			addLastToList(labelsList, createLabelNode(cmdCounter, label));
			printf("We Have label HERE!!!!!!\n");
			cmdCounter++;
		}
		else if(tempcheck == 3)
		{
			cmdCounter++;
		}

	}

	printf("Labels list is: \n");
	printList(labelsList);

	// initialize Memory
	for(i = 0; i < MAX_ROWS; i++)
	{
		memory[i][0] = '\0';
	}

	printf("write to output\n");
	cmdCounter = 0;
	fseek(f, 0, SEEK_SET);
	while(fgets(buffer, MAX_ROW_LENGTH, f))
	{
		printf("############################################\noutput: line is: %s", buffer);

		strcpy(bufferCopy, buffer);

		firstWord = strtok(bufferCopy, s);
		secondWord = strtok(NULL, s);
//		strcpy(bufferCopy, buffer);
		if(!firstWord)
		{
			continue;
		}
		printf("firstWord is: (%s)\n", firstWord);
		if(firstWord[0] == '#')
		{
			continue;
		}
		if(firstWord[strlen(firstWord) - 1] == ':')
		{

			if(secondWord)
			{
				strcpy(bufferCopy, buffer);
				printf("bobo, bufferCopy=%s buffer=%s\n", bufferCopy, buffer);
				deleteFirstWordFromLine(bufferCopy, buffer);
				printf("gogo, bufferCopy=%s buffer=%s\n", bufferCopy, buffer);
			}
			else
			{
				printf("yoyo\n");
				continue;
			}

		}
		if (!strcmp(firstWord, ".word"))
		{
			printf("continue - this is word!!\n");
			thirdWord = strtok(NULL, s);
			if(isHex(secondWord))
			{
				addr = convertHexRowIndexToDec(secondWord);
			}
			else
			{
				addr = atoi(secondWord);
			}

			if(isHex(thirdWord))
			{
				thirdWord+=2;
				strcpy(memory[addr], thirdWord);
			}
			else
			{
				convertDecToHex(atoi(thirdWord), hexLine, 8);
				strcpy(memory[addr], hexLine);
			}

			if(addr > maxRowInMem)
			{
				maxRowInMem = addr;
			}

			continue;
		}

		strcpy(bufferCopy, buffer);

		if(isBufferHasLabel(bufferCopy, label))
		{
			printf("this buffer has label %s\n", label);
			labelIndex = getRowByLabelName(labelsList, label);
			printf("this buffer has label %s in row %d\n", label, labelIndex);
			tempcheck = whichOptCode(firstWord);
			if(tempcheck == 0)
			{
				parseCommand(buffer, hexline);
				//fprintf(output, hexline);
				strcpy(memory[cmdCounter], hexline);
//				cmdCounter++;
			}
			if(tempcheck == -1)
			{
				continue;
			}

			if(tempcheck == 1)
			{
				changeLine(buffer, labelIndex, cmdCounter, true, newLine);
				parseCommand(newLine, hexline);
				//fprintf(output, hexline);
				strcpy(memory[cmdCounter], hexline);
			}
			else if(tempcheck == 2)
			{
				printf("JAL/JR buffer is: %s\n", buffer);
				newLine[0] =  '\0';
				changeLine(buffer, labelIndex, cmdCounter, false, newLine);
				printf("JAL/JR newLine is: %s\n", newLine);
				parseCommand(newLine, hexline); //need to add \n at the end;
				//fprintf(output, hexline);
				strcpy(memory[cmdCounter], hexline);
			}
		}
		else
		{
			printf("no label in this line: %s\n", buffer);
			parseCommand(buffer, hexline);
			//fprintf(output, hexline);
			strcpy(memory[cmdCounter], hexline);
		}

		if(maxRowInMem == cmdCounter)
		{
			maxRowInMem++;
		}
		cmdCounter++;

	}

	printf("cmdCounter is: %d\n", cmdCounter);

	for(i = 0; i < MAX_ROWS; i++)
	{
		if(memory[i][0] == 0)
		{
			fprintf(output, zeros);
		}
		else
		{
			fprintf(output, memory[i]);
		}

		fprintf(output, "\n");
	}


	fclose(output);
	fclose(f);
}
