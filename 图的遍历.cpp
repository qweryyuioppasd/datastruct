#include <stdio.h>
#include <malloc.h>
#define QUEUE_SIZE 10

int* visitedPtr;

/**
 * A queue with a number of indices.
 */
typedef struct GraphNodeQueue{
	int* nodes;
	int front;
	int rear;
}GraphNodeQueue, *QueuePtr;

/**
 * Initialize the queue.
 */
QueuePtr initQueue(){
	QueuePtr resultQueuePtr = (QueuePtr)malloc(sizeof(struct GraphNodeQueue));
	resultQueuePtr->nodes = (int*)malloc(QUEUE_SIZE * sizeof(int));
	resultQueuePtr->front = 0;
	resultQueuePtr->rear = 1;
	return resultQueuePtr;
}//Of initQueue

/**
 * Is the queue empty?
 */
bool isQueueEmpty(QueuePtr paraQueuePtr){
	if ((paraQueuePtr->front + 1) % QUEUE_SIZE == paraQueuePtr->rear) {
		return true;
	}//Of if

	return false;
}//Of isQueueEmpty

/**
 * Add a node to the queue.
 */
void enqueue(QueuePtr paraQueuePtr, int paraNode){
	//printf("front = %d, rear = %d.\r\n", paraQueuePtr->front, paraQueuePtr->rear);
	if ((paraQueuePtr->rear + 1) % QUEUE_SIZE == paraQueuePtr->front % QUEUE_SIZE) {
		printf("Error, trying to enqueue %d. queue full.\r\n", paraNode);
		return;
	}//Of if
	paraQueuePtr->nodes[paraQueuePtr->rear] = paraNode;
	paraQueuePtr->rear = (paraQueuePtr->rear + 1) % QUEUE_SIZE;
	//printf("enqueue %d ends.\r\n", paraNode);
}//Of enqueue

/**
 * Remove an element from the queue and return.
 */
int dequeue(QueuePtr paraQueuePtr){
	if (isQueueEmpty(paraQueuePtr)) {
		printf("Error, empty queue\r\n");
		return NULL;
	}//Of if

	paraQueuePtr->front = (paraQueuePtr->front + 1) % QUEUE_SIZE;

	//printf("dequeue %d ends.\r\n", paraQueuePtr->nodes[paraQueuePtr->front]);
	return paraQueuePtr->nodes[paraQueuePtr->front];
}//Of dequeue

/**
 * The structure of a graph.
 */
typedef struct Graph{
	int** connections;
	int numNodes;
} *GraphPtr;

//void deepFirst(GraphPtr paraGraphPtr, int paraNode);

GraphPtr initGraph(int paraSize, int** paraData) {
	int i, j;
	GraphPtr resultPtr = (GraphPtr)malloc(sizeof(Graph));
	resultPtr -> numNodes = paraSize;
	//resultPtr -> connections = (int**)malloc(paraSize * paraSize * sizeof(int));
	resultPtr -> connections = (int**)malloc(paraSize * sizeof(int*));
	for (i = 0; i < paraSize; i ++) {
		resultPtr -> connections[i] = (int*)malloc(paraSize * sizeof(int));
		for (j = 0; j < paraSize; j ++) {
			resultPtr -> connections[i][j] = paraData[i][j];
		}//Of for j
	}//Of for i
	
	return resultPtr;
}//Of initGraph

/**
 * Initialize the tranverse.
 */
void initTranverse(GraphPtr paraGraphPtr) {
	int i;
	//Initialize data
	visitedPtr = (int*) malloc(paraGraphPtr -> numNodes * sizeof(int));
	
	for (i = 0; i < paraGraphPtr -> numNodes; i ++) {
		visitedPtr[i] = 0;
	}//Of for i
}//Of initTranverse

/**
 * Depth first tranverse.
 */
void depthFirstTranverse(GraphPtr paraGraphPtr, int paraNode) {
	int i;
	
	visitedPtr[paraNode] = 1;
	printf("%d\t", paraNode);
	
	for (i = 0; i < paraGraphPtr -> numNodes; i ++) {
		if (!visitedPtr[i]){ 
			if (paraGraphPtr -> connections[paraNode][i]) {
				depthFirstTranverse(paraGraphPtr, i);
			}//Of if
		}//Of if
	}//Of for i
}//Of depthFirstTranverse

/**
 * Width first tranverse.
 */
void widthFirstTranverse(GraphPtr paraGraphPtr, int paraStart){
	//Use a queue to manage the pointers
	int i, j, tempNode;
	i = 0;
	QueuePtr tempQueuePtr = initQueue();
	printf("%d\t", paraStart);
	visitedPtr[paraStart] = 1;
	enqueue(tempQueuePtr, paraStart);
	while (!isQueueEmpty(tempQueuePtr)) {
		tempNode = dequeue(tempQueuePtr);
		visitedPtr[tempNode] = 1;
		
		//For output.
		i ++;

		for (j = 0; j < paraGraphPtr->numNodes; j ++) {
			if (visitedPtr[j]) 
				continue;

			if (paraGraphPtr->connections[tempNode][j] == 0)
				continue;
			
			printf("%d\t", j);
			visitedPtr[j] = 1;
			enqueue(tempQueuePtr, j);
		}//Of  for j
	}//Of while
}//Of widthFirstTranverse

void testGraphTranverse() {
	int i, j;
	int myGraph[5][5] = { 
		{0, 1, 0, 1, 0},
		{1, 0, 1, 0, 1}, 
		{0, 1, 0, 1, 1}, 
		{1, 0, 1, 0, 0}, 
		{0, 1, 1, 0, 0}};
	int** tempPtr;
	printf("Preparing data\r\n");
		
	tempPtr = (int**)malloc(5 * sizeof(int*));
	for (i = 0; i < 5; i ++) {
		tempPtr[i] = (int*)malloc(5 * sizeof(int));
	}//Of for i
	 
	for (i = 0; i < 5; i ++) {
		for (j = 0; j < 5; j ++) {
			//printf("i = %d, j = %d, ", i, j);
			//printf("%d\r\n", tempPtr[i][j]);
			tempPtr[i][j] = myGraph[i][j];
			//printf("i = %d, j = %d, %d\r\n", i, j, tempPtr[i][j]);
		}//Of for j
	}//Of for i
 
	printf("Data ready\r\n");
	
	GraphPtr tempGraphPtr = initGraph(5, tempPtr);
	printf("num nodes = %d \r\n", tempGraphPtr -> numNodes);
	printf("Graph initialized\r\n");

	printf("Depth first visit:\r\n");
	initTranverse(tempGraphPtr);
	depthFirstTranverse(tempGraphPtr, 4);

	printf("\r\nWidth first visit:\r\n");
	initTranverse(tempGraphPtr);
	widthFirstTranverse(tempGraphPtr, 4);
}//Of testGraphTranverse

int main(){
	testGraphTranverse();
	return 1;
}//Of main

