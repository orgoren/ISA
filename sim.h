#ifndef SIM_H_
#define SIM_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MAX_ROW_LENGTH 500
#define MAX_ROWS 65535
#define MAX_LABEL_LENGTH 50
#define MEMORY_WORD_LENGTH 8
#define NUM_OF_REGS 16

#define MEM_OUT 0
#define REG_OUT 1
#define TRACE_OUT 2
#define COUNT_OUT 3

#define RD 0
#define RS 1
#define RT 2
#define IMM 3

#define ADD '0'
#define SUB '1'
#define AND '2'
#define OR '3'
#define SLL '4'
#define SRA '5'
#define LIMM '6'
#define BEQ '7'
#define BGT '8'
#define BLE '9'
#define BNE 'A'
#define JAL 'B'
#define LW 'C'
#define SW 'D'
#define JR 'E'
#define HALT 'F'

/*This function executes the assembly code, and output the results to files:
 * Trace, memout, count and regout
 */
int sim (int argc, char** argv);

/*this function get an array of registers 'reg' and a pointer to file 'traceOut' and the
 * current instruction 'inst' (string) and write to to 'traceOut' the 'reg' array and
 * the instruction.
 */
void updateTrace(const int* reg, FILE* traceOut,char* inst);

/*this function gets a decimal integer 'a' and returns a string 'result'
 * that contains its hex value of a in a 2's complement.
 * the len of the string is also given in int 'len'
 */
void convertDecToHex2(int a, char* result, int len);

/*this function get an array of registers 'reg' and a pointer to a file 'regout'
 * and prints the reg array to the file.
 */
void printToRegout(int* reg, FILE* regout);

/*this function gets an array of registers 'reg' (4 registers)
 * and a string 'line' that contains the 4 registers value and puts each
 * value in the right register
 * reg[0] = rd, reg[1] = rs, reg[2] = rt, reg[3] = imm.
 */
void placeInTempReg(int* reg, char* line);

/*the function gets a string 'line' and an array of registers 'reg'.
 * it performs the command that is coded in the line and update the
 * registers respectively.
 */
void performCommand(char* line, int* reg);

/*this function gets a string 'tempString' that contains
 * a hexadecimal value (int 2's comp) and returns its decimal value.
 */
int convertHexToIntTwosCom(char* tempString);

/*this function get a char 'a' and returns its decimal value.
 */
int charToInt(char a);

#endif /* SIM_H_ */
