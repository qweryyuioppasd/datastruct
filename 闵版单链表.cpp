#include<stdio.h>
#include<malloc.h>
/**
 * Linked list of integers. The key is data. The key is sorted in non-descending order.
 */ 
typedef struct LinkNode{
	char data;
	struct LinkNode *next;
}LNode,*LinkList,*NodePtr;

/**
 * Initialize the list with a header.
 * @return The pointer to the header.
 */
 
 LinkList initLinkList()
 {
 	NodePtr tempHeader=(NodePtr)malloc(sizeof(LNode));
 	tempHeader->data='\0';
 	tempHeader->next=NULL;
 	return tempHeader;
 }// Of initLinkList
 
 /**
 * Print the list.
 * @param paraHeader The header of the list.
 */
 
 void printList(NodePtr paraHeader)
 {
 	NodePtr p=paraHeader->next;
 	while(p!=NULL)
 	{
 		printf("%c",p->data);
 		p=p->next;
    }// Of while
    printf("\r\n");
 }// Of printList
 
 
 /**
 * Add an element to the tail.
 * @param paraHeader The header of the list.
 * @param paraChar The given char.
 */
 
 void appendElement(NodePtr paraHeader, char paraChar){
	NodePtr p, q;
	// Step 1. Construct a new node.
	q = (NodePtr)malloc(sizeof(LNode));
	q->data = paraChar;
	q->next = NULL;
	// Step 2. Search to the tail.
	p = paraHeader;
	while (p->next != NULL) {
		p = p->next;
	}// Of while
	// Step 3. Now add/link.
	p->next = q;
}// Of appendElement
/**
 * Insert an element to the given position.
 * @param paraHeader The header of the list.
 * @param paraChar The given char.
 * @param paraPosition The given position.
 */

void insertElement(NodePtr paraHeader, char paraChar, int paraPosition){
	NodePtr p, q;
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
	q = (NodePtr)malloc(sizeof(LNode));
	q->data = paraChar;
	// Step 3. Now link.
	printf("linking\r\n");
	q->next = p->next;
	p->next = q;
}// Of insertElement


/**
 * Delete an element from the list.
 * @param paraHeader The header of the list.
 * @param paraChar The given char.
 */
 
 void deleteElement(NodePtr paraHeader, char paraChar){
	NodePtr p, q;
	p = paraHeader;
	while ((p->next != NULL) && (p->next->data != paraChar)){
		p = p->next;
	}// Of while

	if (p->next == NULL) {
		printf("Cannot delete %c\r\n", paraChar);
		return;
	}// Of if

	q = p->next;
	p->next = p->next->next;
	free(q);
}// Of deleteElement


/**
 * Unit test.
**/
 
 void appendInsertDeleteTest(){
	// Step 1. Initialize an empty list.
	LinkList tempList = initLinkList();
	printList(tempList);

	// Step 2. Add some characters.
	appendElement(tempList, 'H');
	appendElement(tempList, 'e');
	appendElement(tempList, 'l');
	appendElement(tempList, 'l');
	appendElement(tempList, 'o');
	appendElement(tempList, '!');
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
	LNode tempNode1, tempNode2;

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
	appendInsertDeleteTest();
}// Of main
