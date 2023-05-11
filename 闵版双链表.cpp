#include <stdio.h>
#include <malloc.h>

/**
 * Double linked list of integers. The key is char.
 */
typedef struct DoubleLinkedNode{
	char data;
	struct DoubleLinkedNode *previous;
	struct DoubleLinkedNode *next;
} DLNode, *DLNodePtr;

/**
 * Initialize the list with a header.
 * @return The pointer to the header.
 */
DLNodePtr initLinkList(){
	DLNodePtr tempHeader = (DLNodePtr)malloc(sizeof(struct DoubleLinkedNode));
	tempHeader->data = '\0';
	tempHeader->previous = NULL;
	tempHeader->next = NULL;
	return tempHeader;
}// Of initLinkList

/**
 * Print the list.
 * @param paraHeader The header of the list.
 */
void printList(DLNodePtr paraHeader){
	DLNodePtr p = paraHeader->next;
	while (p != NULL) {
		printf("%c", p->data);
		p = p->next;
	}// Of while
	printf("\r\n");
}// Of printList

/**
 * Insert an element to the given position.
 * @param paraHeader The header of the list.
 * @param paraChar The given char.
 * @param paraPosition The given position.
 */
void insertElement(DLNodePtr paraHeader, char paraChar, int paraPosition){
	DLNodePtr p, q, r;

	// Step 1. Search to the position.
	p = paraHeader;
	for (int i = 0; i < paraPosition; i ++) {
		p = p->next;
		if (p == NULL) {
			printf("The position %d is beyond the scope of the list.", paraPosition);
			return;
		}// Of if
	} // Of for i

	// Step 2. Construct a new node.
	q = (DLNodePtr)malloc(sizeof(struct DoubleLinkedNode));
	q->data = paraChar;

	// Step 3. Now link.
	r = p->next;
	q->next = p->next;
	q->previous = p;
	p->next = q;
	if (r != NULL) {
		r->previous = q;
	}// Of if
}// Of insertElement

/**
 * Delete an element from the list.
 * @param paraHeader The header of the list.
 * @param paraChar The given char.
 */
void deleteElement(DLNodePtr paraHeader, char paraChar){
	DLNodePtr p, q, r;
	p = paraHeader;

	// Step 1. Locate.
	while ((p->next != NULL) && (p->next->data != paraChar)){
		p = p->next;
	}// Of while

	// Step 2. Error check.
	if (p->next == NULL) {
		printf("The char '%c' does not exist.\r\n", paraChar);
		return;
	}// Of if

	// Step 3. Change links.
	q = p->next;
	r = q->next;
	p->next = r;
	if (r != NULL) {
		r->previous = p;
	}// Of if

	// Step 4. Free the space.
	free(q);
}// Of deleteElement

/**
 * Unit test.
 */
void insertDeleteTest(){
	// Step 1. Initialize an empty list.
	DLNodePtr tempList = initLinkList();
	printList(tempList);

	// Step 2. Add some characters.
	insertElement(tempList, 'H', 0);
	insertElement(tempList, 'e', 1);
	insertElement(tempList, 'l', 2);
	insertElement(tempList, 'l', 3);
	insertElement(tempList, 'o', 4);
	insertElement(tempList, '!', 5);
	printList(tempList);

	// Step 3. Delete some characters (the first occurrence).
	deleteElement(tempList, 'e');
	deleteElement(tempList, 'a');
	deleteElement(tempList, 'o');
	printList(tempList);

	// Step 4. Insert to a given position.
	insertElement(tempList, 'o', 1);
	printList(tempList);
}// Of appendInsertDeleteTest

/**
 * Address test: beyond the book.
 */
void basicAddressTest(){
	DLNode tempNode1, tempNode2;

	tempNode1.data = 4;
	tempNode1.next = NULL;

	tempNode2.data = 6;
	tempNode2.next = NULL;

	printf("The first node: %d, %d, %d\r\n",
		&tempNode1, &tempNode1.data, &tempNode1.next);
	printf("The second node: %d, %d, %d\r\n",
		&tempNode2, &tempNode2.data, &tempNode2.next);

	tempNode1.next = &tempNode2;
}// Of basicAddressTest

/**
 * The entrance.
 */
 int main(){
	insertDeleteTest();
	basicAddressTest();
	return 0;
}// Of main

