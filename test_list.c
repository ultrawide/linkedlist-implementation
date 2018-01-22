// Sample test routine for the list module.
#include <stdio.h>
#include "list.h"
#include <stdbool.h>
#include <string.h>
#include <assert.h>

/*
 * Main()
 */
int main(int argc, char** argv)
{
	printf("Starting tests...\n");
	struct nodeStruct *head = NULL;

	// Starting count:
	assert(List_countNodes(head) == 0);

	// Create 1 node:
	struct nodeStruct* firstNode = List_createNode(0);
	List_insertHead(&head, firstNode);
	assert(List_countNodes(head) == 1);
	assert(List_findNode(head, 0) == firstNode);
	assert(List_findNode(head, 1) == NULL);
	
	// Insert tail:
	struct nodeStruct* lastNode = List_createNode(-5);
	List_insertTail(&head, lastNode);
	assert(List_countNodes(head) == 2);
	assert(List_findNode(head, 0) == firstNode);
	assert(List_findNode(head, -5) == lastNode);
	assert(List_findNode(head, 1) == NULL);

	// Insert another head:
	struct nodeStruct* thirdNode = List_createNode(-2);
	List_insertHead(&head, thirdNode);
	assert(List_countNodes(head) == 3);
	assert(List_findNode(head, -2) == thirdNode);
	struct nodeStruct* noNode = List_findNode(head, 8);
	assert(noNode == NULL);

	// Verify list:
	struct nodeStruct *current = head;
	assert(current->item == -2);
	assert(current->next == firstNode);
	current = current->next;
	assert(current->item == 0);
	assert(current->next != NULL);
	current = current->next;
	assert(current->item == -5);
	assert(current->next == NULL);

	// Sort and verify:
	List_sort(&head);
	current = head;
	assert(current->item == -5);
	assert(current->next != NULL);
	current = current->next;
	assert(current->item == -2);
	assert(current->next != NULL);
	current = current->next;
	assert(current->item == 0);
	assert(current->next == NULL);


	// More rigorous test:
	struct nodeStruct *n1 = List_createNode(-5);
	struct nodeStruct *n2 = List_createNode(7);
	struct nodeStruct *n3 = List_createNode(-3);
	struct nodeStruct *n4 = List_createNode(2);
	struct nodeStruct *n5 = List_createNode(6);
	List_insertHead(&head, n4);
	List_insertHead(&head, n1);
	List_insertTail(&head, n2);
	List_insertTail(&head, n3);
	List_insertTail(&head, n5);

	// Delete recently added nodes
	List_deleteNode(&head, n1);
	List_deleteNode(&head, n2);
	List_deleteNode(&head, n3);
	List_deleteNode(&head, n4);
	List_deleteNode(&head, n5);

	// Delete
	assert(List_countNodes(head) == 3);
	struct nodeStruct *nodeOf0 = List_findNode(head, 0);
	List_deleteNode(&head, nodeOf0);
	assert(List_countNodes(head) == 2);
	assert(List_findNode(head, 0) == NULL);
	assert(List_findNode(head, 1) == NULL);
	current = head;
	assert(current->item == -5);
	assert(current->next != NULL);
	current = current->next;
	assert(current->item == -2);
	assert(current->next == NULL);
	
	// Delete Again
	struct nodeStruct *nodeN5 = List_findNode(head, -5);
	List_deleteNode(&head, nodeN5);
	current = head;
	assert(current->item == -2);
	assert(current->next == NULL);
	assert(List_countNodes(head) == 1);

	// Delete Again
	struct nodeStruct *nodeN2 = List_findNode(head, -2);
	List_deleteNode(&head, nodeN2);
	current = head;
	assert(List_countNodes(head) == 0);
	assert(current == NULL);

	// Add tail to empty list
	struct nodeStruct *dummyNode = List_createNode(0);
	List_insertTail(&head, dummyNode);
	current = head;
	assert(current->item == 0);
	assert(current->next == NULL);

	printf("\nExecution finished.\n");
	return 0;
}

