#ifndef ASM_H_
#define ASM_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "labelList.h"
#include <limits.h>
#include <math.h>

#define MAX_ROW_LENGTH 500
#define MAX_ROWS 65535
#define MAX_LABEL_LENGTH 50
#define MEMORY_WORD_LENGTH 8

/* This function gets a string 'cmd' which contain an assembler line.
 * reads it and convert it to memory line and puts in string 'result'
 */
void parseCommand(const char* cmd, char* result);

/* This function gets the string of the register in the command
 * and returns a char of the value of the register between 0 to F
 */
char convertRegister(char* reg);

/* This function gets the string of the optCode in the command
 * and returns a char of the value of the register between 0 to F
 */
char convertOpcode(char* opcode);

/* This function gets a decimal integer 'a' and returns a string 'result'
 * that contains its hex value of a in a 2's complement.
 * the len of the string is also given in int 'len'
 */
void convertDecToHex(int a, char* result, int len);

/* This function gets a hex in string 'hexRowIndex' and
 * returns the decimal value of this string.
 * It's unsigned command - no negative values.
 * Return -1 only it it failed.
 */
int convertHexRowIndexToDec(const char* hexRowIndex);

/*
 * This function checks if the string 'num' is representing a hexadecimal
 * number. if it does it returns true.
 * else, it returns false,
 */
bool isHex(char* num);

/* This function gets a string 'imm' that contains a representation of an integer.
 * if 'imm' is a hex the function put in result its hex-value without the '0x'.
 * if 'imm' is a decimal the fuction convert it to hex and put it in result string
 * without the '0x'.
 */
void convertImmediate(char* imm, char* result);

/* The function check gets two strings 'getLine' and 'label'
 * It checks if there is a label in 'getLine'.
 * returns - 0 if there is no label. (probably a comment)
 * returns - 1 if there is only label in this line.
 * returns - 2 if there is a label and a cmd in this line
 * returns - 3 if there is only a command in this line.
 * It only checks if the label is in the first word (label:...)
 * if there is a label, it update 'label' to be the same as the label in 'getLine'.
 */
int isThereLabelInIt(char* getline,char* label);

/* This function get currLine - a string with line in the memory with label in it
 * int labelIndex - the label value (where the label is pointing)
 * string newLine - after this function finishes this string contains the same line in memory but instead
 * of the label it contains its row number in hex
 */
void changeLine(char* currLine, int labelIndex, char* newLine);

/* This function gets a 'line' (string) and a 'label' (string).
 * It checks if there is a label in this line (in the imm).
 * If there is no label it returns false.
 * else, it returns true and put the label in the string 'label'.
 */
bool isBufferHasLabel(char* buffer, char* label);

/* The function gets a string 'firstWord' and return 1 if it is a
 * legal command and -1 if it is not.
 */
int isCMD(char* firstWord);

/* This function get a string(word)
 * return -1 if it is a 'WORD' command or a comment.
 * return 1 if it is a jump command (jal, jr, beq,...)
 * return 0 if it is any other command.
 */
int whichOptCode(char* Word);

/* This function get two strings 'line' and 'newLine'
 * It copy the string line into string newLine without its first word.
 * We use this function in order to delete the label from a line which
 * contains a label and a command - so we can parse it.
 */
void deleteFirstWordFromLine(char* line, char* newLine);

/* This function gets a string 'path' that contains a path to a file in assemblr.txt
 * it reads the file and create a new file which will contain the memory of the assembler program.
 * The first time it parses the input file in order to find the labels and theirs rows number.
 * And the second time is for parsing the lines.
 */
void readFile(char* path, char* path_out);

int main(int argc, char** argv);


#endif /* ASM_H_ */
