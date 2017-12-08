#ifndef LABELLIST_H_
#define LABELLIST_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LABEL 500

typedef struct label_node_type
{
	int row;
	char contnet[MAX_LABEL];
	struct label_node_type* next;
} labelNode;

typedef struct label_list_type
{
	labelNode* first;
	labelNode* last;
} labelList;

/*creating a new list node that resemble a line in the memory.
 * It has 2 attributes: the row number (int 'row') and the line content
 * (string 'content')
 * return - a pointer to the new node that was created
 */
labelNode* createLabelNode(int row, char* content);

/*this function get a list node and destroy it
 * (free its memory)
 */
void destroyLabelNode(labelNode* node);

/*this function create a new linked list object
 * and returns a pointer to its head.
 */
labelList* createLabelList();

/*this function gets a pointer to a linked list 'list'
 * and prints its content.
 */
void printList(labelList* list);

/*this function get a pointer to list 'list' and a string 'content' and print
 * the row number that has 'content'.
 * return - int 'row number' if the function find a match.
 * return - (-1) otherwise
 */
int getRowByLabelName(labelList* list, char* content);

/*this function get a pointer to a list 'list' and destroy it.
 *
 */
void destroyLabelList(labelList* list);

/*this function get a pointer to 'list' and a pointer to 'node'
 * and add the node at the end of the list
 */
void addLastToList(labelList* list, labelNode* node);



#endif /* LABELLIST_H_ */
