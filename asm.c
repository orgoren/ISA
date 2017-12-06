#include "asm.h"

void parseCommand(const char* cmd, char* result)
{
	char line[500];
	char imm[5];
	char label[MAX_LABEL_LENGTH];
	char s[] = " ,\t\r\n";

	// Extracting the words without damaging the input
	strcpy(line, cmd);
	char* opcodeStr = strtok(line, s);
	char* rdStr = strtok(NULL, s);
	char* rsStr = strtok(NULL, s);
	char* rtStr = strtok(NULL, s);
	char* immStr = strtok(NULL, s);

	// Converts the opcode and the registers
	char opcode = convertOpcode(opcodeStr);
	char rd = convertRegister(rdStr);
	char rt = convertRegister(rtStr);
	char rs = convertRegister(rsStr);


	//If the line doesn't contains a label so we can parse the immStr and save it to imm
	// The line shouldn't contain a label it it's gotten here - but on any case.
	strcpy(line, cmd);
	if (!isBufferHasLabel(line, label))
	{
		convertImmediate(immStr, imm);
	}

	// Combining all the commands together and save it to result.
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

	// On Error - no reg can have this value
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

	// On Error - No opcode has this value
	return 'G';
}

void convertDecToHex(int a, char* result, int len)
{
	int i;
	int t;
	int mask = 15;
	for(i = len - 1; i >= 0; i--)
	{
		t = mask & a;	// Now t contains the 4 lsb bits of a
		if (t > 9)
		{
			result[i] = 'A' + t - 10;
		}
		else
		{
			result[i] = '0' + (char)(mask & a);
		}

		a >>= 4;		// continue to next 4 bits
	}
	result[len] = '\0';
}

int convertHexRowIndexToDec(const char* hexRowIndex)
{
	// The row number has to be positive so -1 can be achieved
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

		// t = (int)hexRowIndex[i]
		for(j = 0; j < strlen(nums); j++)
		{
			if (hexRowIndex[i] == nums[j])
			{
				t = j;
				break;
			}
		}

		// Add it correctly
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

	// Only if it starts with 0x it's a hex
	if(num[0] == '0' && num[1] == 'x')
	{
		return true;
	}

	return false;
}

void convertImmediate(char* imm, char* result)
{
	// If it's a hex so we just save the imm letters (only 4 in imm)
	if(isHex(imm))
	{
		result[0] = imm[2];
		result[1] = imm[3];
		result[2] = imm[4];
		result[3] = imm[5];
		result[4] = '\0';
	}
	// If it's a decimal number so we need to make it a hex and save it to result. (len is 4)
	else
	{
		convertDecToHex(atoi(imm), result, 4);
	}
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
	char* secondWord = strtok(NULL, s);
	int tempCheckIsCmd = 0;
	int lenword = strlen(firstWord);

	// No label if the line is a comment
	if( firstWord[0] == '#')
	{
		return 0;
	}
	// If the line defines a new label (LBL:)
	if(firstWord[lenword-1] == ':')
	{
		strcpy(label, firstWord);
		label[lenword] = '\0';

		// if the second word is a comment or NULL so there's no cmd in the line
		if(!secondWord)
		{
			return 1;
		}
		else if (secondWord[0] =='#')
		{
			return 1;
		}
		// if it has cmd then check whether it's a WORD or regular and returns respectively.
		else
		{
			tempCheckIsCmd = isCMD(secondWord);
			if(tempCheckIsCmd == 1)
			{
				return 2;
			}
			else
			{
				return 1;
			}
		}
	}

	// No label so we need to check if it contains a command or not without a label and return respectively.
	else
	{
		if (isCMD(firstWord) == 1)
		{
			return 3;
		}
		else
		{
			return 0;
		}
	}
}

void changeLine(char* currLine, int labelIndex, char* newLine)
{
	// Extract all the words in the line
	char s[] = " ,\t\r\n";
	char* opcodeStr = strtok(currLine, s);
	char* rdStr = strtok(NULL, s);
	char* rsStr = strtok(NULL, s);
	char* rtStr = strtok(NULL, s);
	char p[] = ", ";
	char labelReplace[4];
	int labelLines;

	// Saves all the first words to newLine - without the imm
	newLine[0] = '\0';
	strcat(newLine, opcodeStr);
	strcat(newLine, p);
	strcat(newLine, rdStr);
	strcat(newLine, p);
	strcat(newLine, rsStr);
	strcat(newLine, p);
	strcat(newLine, rtStr);
	strcat(newLine, p);

	// Converts the row of the label to 4 letters in hex, and then save it to 'newLine'
	labelLines = labelIndex;
	convertDecToHex(labelLines, labelReplace, 4);
	strcat(newLine, "0x");
	strcat(newLine, labelReplace);
}

bool isBufferHasLabel(char* buffer, char* label)
{
	// Extract all the words from the line
	char s[] = " ,\t\r\n";
	char* oc = strtok(buffer, s);
	char* r1 = strtok(NULL, s);
	char* r2 = strtok(NULL, s);
	char* r3 = strtok(NULL, s);
	char* im = strtok(NULL, s);

	// Check for errors in the line
	if(!oc || !r1 || !r2 || !r3 || !im)
	{
		return false;
	}

	// If the line is a comment so no need to check anymore
	if(oc[1] == '#')
	{
		return false;
	}

	// If ther'es no im so no label can be here.
	if(!im)
	{
		return false;
	}

	// if the length of imm is 1 we need to check if it's a number. If it's so it's not a label
	// else it is and we need to save it to the 'label' argument.
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

	// If the first letter is not 0-9 so we know it's not a hex or a dec value
	// so it has to be a label and we save it to label argument.
	if((im[0] >= 'A' && im[0] <= 'Z') || (im[0] >= 'a' && im[0] <= 'z'))
	{
		strcpy(label, im);
		return true;
	}


	return false;
}

int isCMD(char* firstWord)
{
	if(!firstWord)
	{
		return -1;
	}

	// Can't be a regular command
	if((strlen(firstWord) > 4) || (strlen(firstWord) < 2))
	{
		return -1;
	}

	char cmd[6];
	strcpy(cmd, firstWord);

	// If it contains 5 letters than it can be a WORD command, so we need to check it.
	// We can assume that the input is correct so if it's not a WORD command it has to
	// be a regular command.
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
	// If the line is a comment or a WORD command
	if((Word[0] == '#') || (strcmp(Word, "WORD") == 0))
	{
		return -1;
	}
	// If the line is a jump/branch command
	if((strcmp(Word, "beq") == 0)||(strcmp(Word, "bgt") == 0)||(strcmp(Word, "ble") == 0)||(strcmp(Word, "bne") == 0)||(strcmp(Word, "jal") == 0)||(strcmp(Word, "jr") == 0))
	{
		return 1;
	}
	// if there's a regular cmd then return 0
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

	// We concatenating back without the first word
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

void readFile(char* path,char* path_out)
{
	FILE* f;
	FILE* output;
	char hexline[15] = {0};

	char buffer[MAX_ROW_LENGTH];		// The line from the input file will be saved to 'buffer'
	char bufferCopy[MAX_ROW_LENGTH];	// We use strtok, so we do it on a copy of buffer.
	char newLine[MAX_ROW_LENGTH];
	char memory[MAX_ROWS][MEMORY_WORD_LENGTH + 1];
	int maxRowInMem = 0;
	char* firstWord;
	char* secondWord;
	char* thirdWord;
	char hexLine[MEMORY_WORD_LENGTH + 1];
	int addr;
	int tempcheck = 0;
	char zeros[] = "00000000";
	int labelIndex, i;
	int cmdCounter = 0;
	char s[] = " ,\t\r\n";
	char label[MAX_LABEL_LENGTH];

	// Open the input file
	f = fopen(path, "r");
	if(!f)
	{
		printf("Can't open File %s\n", path);
		return;
	}

	// Open the output file
	output = fopen(path_out, "w");
	if(!output)
	{
		printf("Can't open File %s\n", path_out);
		return;
	}

	// Create the labelList struct - we save the label with it's row number.
	labelList* labelsList = createLabelList();


	// First we go over the input file line by line to get the labels and their rows number
	while(fgets(buffer, MAX_ROW_LENGTH, f))
	{
		// Extract the first word from the line
		strcpy(bufferCopy, buffer);
		firstWord = strtok(bufferCopy, s);

		// If the line is empty - continue to next line
		if(!firstWord)
		{
			continue;
		}

		// Check whether is there a label in this line
		tempcheck = isThereLabelInIt(buffer,label);

		// If there's only a label:
		if(tempcheck ==1)
		{
			// Adds the label and the row number to the list
			addLastToList(labelsList, createLabelNode(cmdCounter, label));
		}
		// If there's a label and a command
		else if (tempcheck == 2)
		{
			// Adds the label and the row number to the list
			addLastToList(labelsList, createLabelNode(cmdCounter, label));

			// Advance the rows count - there's a command
			cmdCounter++;
		}
		// If there's only a command so advance the counter
		else if(tempcheck == 3)
		{
			cmdCounter++;
		}

	}

	// initialize Memory
	for(i = 0; i < MAX_ROWS; i++)
	{
		memory[i][0] = '\0';
	}

	// Go back to the beginning of the file
	cmdCounter = 0;
	fseek(f, 0, SEEK_SET);
	while(fgets(buffer, MAX_ROW_LENGTH, f))
	{
		strcpy(bufferCopy, buffer);
		firstWord = strtok(bufferCopy, s);
		secondWord = strtok(NULL, s);

		// If the line is empty then continue to next line
		if(!firstWord)
		{
			continue;
		}

		// If the line is only a comment then continue to next line
		if(firstWord[0] == '#')
		{
			continue;
		}

		// If the first word is defining a label
		if(firstWord[strlen(firstWord) - 1] == ':')
		{

			// If there's a second word than we need to delete the first word from the line in order to parse it
			if(secondWord)
			{
				strcpy(bufferCopy, buffer);
				deleteFirstWordFromLine(bufferCopy, buffer);
			}
			// Else we don't need to parse the line and can continue
			else
			{
				continue;
			}

		}

		// If the line is .word command
		if (!strcmp(firstWord, ".word"))
		{
			// get the third word in the line
			thirdWord = strtok(NULL, s);

			// make addr a decimal value of secondWord (address)
			if(isHex(secondWord))
			{
				addr = convertHexRowIndexToDec(secondWord);
			}
			else
			{
				addr = atoi(secondWord);
			}

			// make the thirdWord to be hex if it isn't and then save it to memory in the 'addr' from before.
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

			// We need to save the maxRow in order to know how much lines to print to memin. if the addr exceeding the
			// commands counter than we need to update the maxRow number.
			if(addr > maxRowInMem)
			{
				maxRowInMem = addr;
			}

			// No need to parse this line to memin
			continue;
		}

		strcpy(bufferCopy, buffer);

		// If the line has label as immm
		if(isBufferHasLabel(bufferCopy, label))
		{
			// get the label row number
			labelIndex = getRowByLabelName(labelsList, label);

			// Check the opcode
			tempcheck = whichOptCode(firstWord);

			// If it's a regular command we need to parse it and save the result to memory in the
			// current row number.
			if(tempcheck == 0)
			{
				parseCommand(buffer, hexline);
				strcpy(memory[cmdCounter], hexline);
			}
			// If it's a WORD command or a comment - shouldn't be as it was taken care of before
			// and no need to do anything
			else if(tempcheck == -1)
			{
				continue;
			}
			// Has to be a brach/Jump command (tempcheck==1)
			else
			{
				// We have a label here so we need to change it to the row number, and then parse the command
				// and save the result to memory
				newLine[0] = '\0';
				changeLine(buffer, labelIndex, newLine);
				parseCommand(newLine, hexline);
				strcpy(memory[cmdCounter], hexline);
			}
		}
		// If there isn't a label in the row we can parse it without any change and then save it to memory.
		else
		{
			parseCommand(buffer, hexline);
			strcpy(memory[cmdCounter], hexline);
		}

		// the maxRow is updated only if it's equal to cmdCounter - if not so it must be bigger.
		if(maxRowInMem == cmdCounter)
		{
			maxRowInMem++;
		}
		// advance the row number (in memin file)
		cmdCounter++;

	}


	// We've to fill the memory with zeroes until maxRowInMem - but only if there isn't anything
	// else in the memory.
	for(i = 0; i < maxRowInMem; i++)
	{
		if(memory[i][0] == 0)
		{
			fprintf(output, "%s", zeros);
		}
		else
		{
			fprintf(output, "%s", memory[i]);
		}

		fprintf(output, "\n");
	}

	// Closing all the files that was being used
	fclose(output);
	fclose(f);
}
