#include <stdio.h>
#include <malloc.h>
#define TOTAL_SPACE 5

//循环队列的定义 
typedef struct xunhuanduilie{
	int data[TOTAL_SPACE];
	int head;
	int tail;
}*xunhuanduiliePtr;

//初始化 
xunhuanduiliePtr initduilie() {
	xunhuanduiliePtr resultPtr = (xunhuanduiliePtr)malloc(sizeof(struct xunhuanduilie));
	resultPtr->head = 0;
	resultPtr->tail = 0;

	return resultPtr;
}

//入队
void enqueue(xunhuanduiliePtr paraPtr, int paraValue) {
	if ((paraPtr->tail + 1) % TOTAL_SPACE == paraPtr->head) {
		printf("Queue full.\r\n");
		return;
	} 

	paraPtr->data[paraPtr->tail % TOTAL_SPACE] = paraValue;
	paraPtr->tail++;
}

//出队 
int dequeue(xunhuanduiliePtr paraPtr) {
	int resultValue;
	if (paraPtr->head == paraPtr->tail) {
		printf("No element in the queue.\r\n");
		return -1;
	} 

	resultValue = paraPtr->data[paraPtr->head % TOTAL_SPACE];
	paraPtr->head++;

	return resultValue;
}

//打印 
void outputLinkQueue(xunhuanduiliePtr paraPtr){
	int i;
	if (paraPtr->head == paraPtr->tail) {
		printf("Empty queue.");
		return;
	} 

	printf("Elements in the queue: ");
	for (i = paraPtr->head; i < paraPtr->tail; i++) {
		printf("%d, ", paraPtr->data[i % TOTAL_SPACE]);
	} 

	printf("\r\n");
}

/**
 * Unit test.
 */
void testLinkQueue(){
	int i = 10;
	xunhuanduiliePtr tempPtr = initduilie();
	for (; i < 16; i ++) {
		enqueue(tempPtr, i);
	}//Of for i

	outputLinkQueue(tempPtr);

	for (i = 0; i < 6; i ++) {
		printf("dequeue gets %d\r\n", dequeue(tempPtr));
	}//Of for i

	enqueue(tempPtr, 8);
	outputLinkQueue(tempPtr);
}//Of testLinkQueue


int main(){
	testLinkQueue();
	return 1;
}

