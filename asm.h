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

/*this function gets a string 'cmd' which contain an assembler line.
 * reads it and convert it to memory line and puts in string 'result'
 */
void parseCommand(const char* cmd, char* result);

/*this function gets the string of the register in the command
 * and returns a char of the value of the register between 0 to F
 */
char convertRegister(char* reg);

/*this function gets the string of the optCode in the command
 * and returns a char of the value of the register between 0 to F
 */
char convertOpcode(char* opcode);

/*this function gets a decimal integer 'a' and returns a string 'result'
 * that contains its hex value of a in a 2's complement.
 * the len of the string is also given in int 'len'
 */
void convertDecToHex(int a, char* result, int len);

/*this function gets a hex integer in string 'hexRowIndex' and
 * returns the decimal value of this string.
 */
int convertHexRowIndexToDec(const char* hexRowIndex);

/*
 * this function checks if the string 'num' is representing a hexadecimal
 * number. if it does it returns true.
 * else, it returns false,
 */
bool isHex(char* num);

/*this function gets a string 'imm' that contains a representation of an integer.
 * if 'imm' is a hex the function put in result its hex-value without the '0x'.
 * if 'imm' is a decimal the fuction convert it to hex and put it in result string
 * without the '0x'.
 */
void convertImmediate(char* imm, char* result);


int isThereLabelInIt(char* getline,char* label);

/* this function get currLine - a string with line in the memory with label in it
 * int labelIndex - the label value (where the label is pointing)
 * string newLine - after this function finnish this string contains the same line in memory but instead
 * of the label there is an imm
 */
void changeLine(char* currLine, int labelIndex, char* newLine);

/*this function gets a 'line' (string) and a 'label' (string).
 * It checks if there is a label in this line (instead of the imm).
 * If there is no label it returns false.
 * else, it returns true and put the label in the string 'label'.
 */
bool isBufferHasLabel(char* line, char* label);

/* the function gets a string 'firstWord' and return 1 if it is a
 * legal command and -1 if it is not.
 */
int isCMD(char* firstWord);

/*this function get a string(word)
 *return -1 if word the command 'WORD'.
 *return 1 if it is a jump command (jal, jr, beq,...)
 *return 0 if it is any other command.
 */
int whichOptCode(char* Word);

/*this function get two strings 'line' and 'newLine'
 * It copy string line into string newLine without its first word.
 */
void deleteFirstWordFromLine(char* line, char* newLine);

/*this function gets a string 'path' that contains a path to a file in assemblr.txt
 * it reads the file and create a new file which will contain the memory of the assembler program.
 */
void readFile(char* path, char* path_out);



#endif /* ASM_H_ */
