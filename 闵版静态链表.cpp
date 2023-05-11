#include <stdio.h>
#include <malloc.h>

#define DEFAULT_SIZE 5

typedef struct StaticLinkedNode{
	char data;

	int next;
} *NodePtr;

typedef struct StaticLinkedList{
	NodePtr nodes;
	int* used;
} *ListPtr;

/**
 * Initialize the list with a header.
 * @return The pointer to the header.
 */
ListPtr initLinkedList(){
	// The pointer to the whole list space.
	ListPtr tempPtr = (ListPtr)malloc(sizeof(StaticLinkedList));

	// Allocate total space.
	tempPtr->nodes = (NodePtr)malloc(sizeof(struct StaticLinkedNode) * DEFAULT_SIZE);
	tempPtr->used = (int*)malloc(sizeof(int) * DEFAULT_SIZE);

	// The first node is the header.
	tempPtr->nodes[0].data = '\0';
	tempPtr->nodes[0].next = -1;

	// Only the first node is used.
	tempPtr->used[0] = 1;
	for (int i = 1; i < DEFAULT_SIZE; i ++){
		tempPtr->used[i] = 0;
	}// Of for i

	return tempPtr;
}// Of initLinkedList

/**
 * Print the list.
 * @param paraListPtr The pointer to the list.
 */
void printList(ListPtr paraListPtr){
	int p = 0;
	while (p != -1) {
		printf("%c", paraListPtr->nodes[p].data);
		p = paraListPtr->nodes[p].next;
	}// Of while
	printf("\r\n");
}// Of printList

/**
 * Insert an element to the given position.
 * @param paraListPtr The position of the list.
 * @param paraChar The given char.
 * @param paraPosition The given position.
 */
void insertElement(ListPtr paraListPtr, char paraChar, int paraPosition){
	int p, q, i;

	// Step 1. Search to the position.
	p = 0;
	for (i = 0; i < paraPosition; i ++) {
		p = paraListPtr->nodes[p].next;
		if (p == -1) {
			printf("The position %d is beyond the scope of the list.\r\n", paraPosition);
			return;
		}// Of if
	} // Of for i

	// Step 2. Construct a new node.
	for (i = 1; i < DEFAULT_SIZE; i ++){
		if (paraListPtr->used[i] == 0){
			// This is identical to malloc.
			printf("Space at %d allocated.\r\n", i);
			paraListPtr->used[i] = 1;
			q = i;
			break;
		}// Of if
	}// Of for i
	if (i == DEFAULT_SIZE){
		printf("No space.\r\n");
		return;
	}// Of if

	paraListPtr->nodes[q].data = paraChar;

	// Step 3. Now link.
	printf("linking\r\n");
	paraListPtr->nodes[q].next = paraListPtr->nodes[p].next;
	paraListPtr->nodes[p].next = q;
}// Of insertElement

/**
 * Delete an element from the list.
 * @param paraHeader The header of the list.
 * @param paraChar The given char.
 */
void deleteElement(ListPtr paraListPtr, char paraChar){
	int p, q;
	p = 0;
	while ((paraListPtr->nodes[p].next != -1) && (paraListPtr->nodes[paraListPtr->nodes[p].next].data != paraChar)){
		p = paraListPtr->nodes[p].next;
	}// Of while

	if (paraListPtr->nodes[p].next == -1) {
		printf("Cannot delete %c\r\n", paraChar);
		return;
	}// Of if

	q = paraListPtr->nodes[p].next;
	paraListPtr->nodes[p].next = paraListPtr->nodes[paraListPtr->nodes[p].next].next;
	
	// This statement is identical to free(q)
	paraListPtr->used[q] = 0;
}// Of deleteElement

/**
 * Unit test.
 */
void appendInsertDeleteTest(){
	// Step 1. Initialize an empty list.
	ListPtr tempList = initLinkedList();
	printList(tempList);

	// Step 2. Add some characters.
	insertElement(tempList, 'H', 0);
	insertElement(tempList, 'e', 1);
	insertElement(tempList, 'l', 2);
	insertElement(tempList, 'l', 3);
	insertElement(tempList, 'o', 4);
	printList(tempList);

	// Step 3. Delete some characters (the first occurrence).
	printf("Deleting 'e'.\r\n");
	deleteElement(tempList, 'e');
	printf("Deleting 'a'.\r\n");
	deleteElement(tempList, 'a');
	printf("Deleting 'o'.\r\n");
	deleteElement(tempList, 'o');
	printList(tempList);

	insertElement(tempList, 'x', 1);
	printList(tempList);
}// Of appendInsertDeleteTest

/**
 * The entrance.
 */
int main(){
	appendInsertDeleteTest();
	return 0;
}// Of main

