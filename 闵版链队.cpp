#include <stdio.h>
#include <malloc.h>

/**
 * 链队列的节点.
 */
typedef struct jiedian{
	int data;
	jiedian* next;
}*jiedianPtr;

/**
 * 链队列.
 */
typedef struct duilie{
	jiedianPtr front;
	jiedianPtr rear;
}*duiliePtr;

/**
 * Construct an empty queue.
 */
duiliePtr initQueue(){
	duiliePtr resultPtr = (duiliePtr)malloc(sizeof(duilie));
	jiedianPtr headerPtr = (jiedianPtr)malloc(sizeof(jiedianPtr));
	headerPtr->next = NULL;
	resultPtr->front = headerPtr;
	resultPtr->rear = headerPtr;
	return resultPtr;
}

/**
 * Output the queue.
 */
void outputduilie(duiliePtr paraQueuePtr){
	jiedianPtr tempPtr = paraQueuePtr->front->next;
	while (tempPtr != NULL) {
		printf("%d ", tempPtr->data);
		tempPtr = tempPtr->next;
	}
	printf("\r\n");
}

/**
 * Enqueue.
 */
void enqueue(duiliePtr paraQueuePtr, int paraElement) {
	//Step 1. Create a new node
	jiedianPtr tempNodePtr = (jiedianPtr)malloc(sizeof(jiedianPtr));
	tempNodePtr->data = paraElement;
	tempNodePtr->next = NULL;
	
	//Step 2. Link to the existing rear
	paraQueuePtr->rear->next = tempNodePtr;
	
	//Step 3. It is the new rear
	paraQueuePtr->rear = tempNodePtr;
}//Of enqueue

/**
 * Dequeue.
 * @return The value of the header
 */
int dequeue(duiliePtr paraQueuePtr) {
	int resultValue;
	jiedianPtr tempNodePtr;

	//Step 1. Is the queue empty?
	if (paraQueuePtr->front == paraQueuePtr->rear) {
		printf("The queue is empty.\r\n");
		return -1;
	}

	//Step 2. Change the queue.
	tempNodePtr = paraQueuePtr->front->next;
	resultValue = tempNodePtr->data;
	paraQueuePtr->front->next = paraQueuePtr->front->next->next;

	if (paraQueuePtr->rear == tempNodePtr) {
		paraQueuePtr->rear = paraQueuePtr->front;
	}/

	//Step 3. Free space.
	tempNodePtr = NULL;

	//Step 4. Return.
	return resultValue;
}/
	
/**
 * Unit test.
 */
void testduilie(){
	duiliePtr tempQueuePtr;
	tempQueuePtr = initQueue();
	enqueue(tempQueuePtr, 10);
	enqueue(tempQueuePtr, 30);
	enqueue(tempQueuePtr, 50);

	outputduilie(tempQueuePtr);

	printf("dequeue gets %d\r\n", dequeue(tempQueuePtr));
	printf("dequeue gets %d\r\n", dequeue(tempQueuePtr));
	printf("dequeue gets %d\r\n", dequeue(tempQueuePtr));
	printf("dequeue gets %d\r\n", dequeue(tempQueuePtr));

	enqueue(tempQueuePtr, 8);
	outputduilie(tempQueuePtr);
}
 

int main(){
	testduilie();
	return 1;
}

