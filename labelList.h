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

labelNode* createLabelNode(int row, char* content);

void destroyLabelNode(labelNode* node);

labelList* createLabelList();

void printList(labelList* list);

int getRowByLabelName(labelList* list, char* content);

void destroyLabelList(labelList* list);

void destroyLabelList(labelList* list);

void addLastToList(labelList* list, labelNode* node);



#endif /* LABELLIST_H_ */
