#include "labelList.h"

labelNode* createLabelNode(int row, char* content)
{
	labelNode* node = (labelNode*)malloc(sizeof(labelNode));
	if(!node)
	{
		return NULL;
	}

	int i;
	if(content[strlen(content) - 1] == ':') //check if there is a label in this line and if there is replace ':' with '\0'
	{
		for(i = 0; i < strlen(content); i++)
		{
			if(content[i] == ':')
			{
				node->contnet[i] = '\0';
				break;
			}

			node->contnet[i] = content[i];
		}


	}
	else
	{
		strcpy(node->contnet, content);
	}

	node->row = row;
	node->next = NULL;

	return node;
}

void destroyLabelNode(labelNode* node)
{
	if(!node)
	{
		return;
	}
	node->next = NULL;
	free(node);
}

labelList* createLabelList()
{
	labelList* list = (labelList*)malloc(sizeof(labelList));
	if(!list)
	{
		return NULL;
	}

	list->first = NULL;
	list->last = NULL;


	return list;
}

void printList(labelList* list)
{
	if (!list)
	{
		return;
	}
	if(!list->first)
	{
		printf("list is empty\n");
		return;
	}
	labelNode* iter = list->first;

	while(iter)
	{
		printf("%d: %s\n", iter->row, iter->contnet);
		iter = iter->next;
	}
}

int getRowByLabelName(labelList* list, char* content)
{
	if(!list || !content)
	{
		return -1;
	}

	if(!list->first)
	{
		return -1;
	}

	labelNode* iter = list->first;

	while(iter)
	{
		if(!strcmp(iter->contnet, content))
		{
			return iter->row;
		}
		iter = iter->next;
	}

	return -1;

}

void destroyListRecurse(labelNode* node)
{
	if(!node)
	{
		return;
	}

	if(node->next)
	{
		destroyListRecurse(node->next);
	}

	node->next = NULL;
	free(node);
	return;
}

void destroyLabelList(labelList* list)
{
	if(!list)
	{
		return;
	}

	if(!list->first)
	{
		free(list);
		return;
	}

	destroyListRecurse(list->first);

	free(list);

	return;
}

void addLastToList(labelList* list, labelNode* node)
{
	if(!list || ! node)
	{
		return;
	}

	if(!list->first)
	{
		list->first = node;
		list->last = node;
		return;
	}

	list->last->next = node;
	list->last = node;
	return;
}






