// Author:	Colin Chan
// Date: 	January 20, 2018

#include "list.h"
#include <stdio.h>
#include <stdlib.h>

/*	
 *	Allocate memory for a node of type struct nodeStruct and initalize
 *	it with the value item. Return a pointer to the new node. 
 */
struct nodeStruct* List_createNode(int item)
{
	struct nodeStruct* node;
	node = malloc(sizeof(struct nodeStruct));
	
	node->item = item;
	node->next = NULL;
	
	return node;
}

/*
 * Insert node at the head of the list.
 */
void List_insertHead(struct nodeStruct **headRef, struct nodeStruct *node)
{
	if (!node)
		return;

	node->next = *headRef;
	*headRef = node;
}

/*
 * Insert node after the tail of the list.
 */
void List_insertTail(struct nodeStruct **headRef, struct nodeStruct *node)
{
	if (!node)
		return;

	struct nodeStruct* present = *headRef;

	// If list is empty, call List_insertHead
	if (List_countNodes(*headRef) == 0)
	{
		List_insertHead(headRef, node);
		return;
	}

	while (present->next)
	{
		present = present->next;
	}

	present->next = node;
	node->next = NULL;
}

/*
 * Count number of nodes in the list.
 * Return 0 if the list is empty, ie., head == NULL
 */
int List_countNodes(struct nodeStruct* head)
{
	struct nodeStruct* node = head;
	int count = 0;

	while(node)
	{
		node = node->next;
		count++;
	}

	return count;
}

/*
 * Return the first node holding the value item, return NULL if none found
 */
struct nodeStruct* List_findNode(struct nodeStruct *head, int item)
{
	struct nodeStruct* present = head;

	while(present)
	{
		if (present->item == item)
			return present;

		present = present->next;
	}

	return NULL;
}

/* 
 * Delete node from the list and free memory allocated to it.
 * This function assumes that node has been properly set to a valid node
 * in the list. For example, the client code may have found it by calling
 * List_findNode(). If the list contains only one node, the head of the list
 * should be set to NULL.
 */
void List_deleteNode(struct nodeStruct **headRef, struct nodeStruct *node)
{
	// If node is NULL or empty set, return
	if (!node || List_countNodes(*headRef) == 0)
		return;
	
	// Delete head node
	if (node == *headRef)
	{
		if (List_countNodes(*headRef) == 1)
			*headRef = NULL;
		else
			*headRef = node->next;
	
		free(node);

		return;
	}

	struct nodeStruct *temp = *headRef;
	
	// Delete tail node or middle node
	while (temp->next != node && temp->next)
	{
		temp = temp->next;
	}
	// If tail node
	if (!node->next)
		temp->next = NULL;
	// If middle node
	else
		temp->next = node->next;
	
	free(node);
}

/*
 * Sort the list in ascending order based on the item field.
 * Any sorting algorithm is fine.
 */
void List_sort(struct nodeStruct **headRef)
{
	// Retrieve values into array
	int array[List_countNodes(*headRef)];
	struct nodeStruct* tempNode = *headRef;
	
	for(int i = 0; tempNode; i++)
	{
		array[i] = tempNode->item;
		tempNode = tempNode->next;
	}

	// Bubble sort array
	int numNodes = sizeof(array)/sizeof(int);
	int temp = 0;
	for(int i = 0; i < numNodes-1; i++)
	{
		for(int j = i+1; j < numNodes; j++)
		{
			if (array[i] > array[j])
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}

	// Place sorted elements back to linkedlist
	tempNode = *headRef;
	for(int i = 0; tempNode; i++)
	{
		tempNode->item = array[i];
		tempNode = tempNode->next;
	}
}
