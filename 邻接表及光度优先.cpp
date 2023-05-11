
/**
 * Adjacency list for directed graph.
 * 
 * @author Fan Min minfanphd@163.com.
 */
#include <stdio.h>
#include <malloc.h>
#define QUEUE_SIZE 10

/*************** Copyied code begins *****************/

int* visitedPtr;

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
	GraphPtr resultPtr = (GraphPtr)malloc(sizeof(struct Graph));
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

/*************** Copyied code ends *****************/

/**
 * Aajacent node.
 */
typedef struct AdjacencyNode {
	int column;
	AdjacencyNode* next;
}AdjacencyNode, *AdjacentNodePtr;

/**
 * Aajacent list.
 */
typedef struct AdjacencyList {
	int numNodes;
	AdjacencyNode* headers;
}AdjacencyList, *AdjacencyListPtr;

/**
 * Construct an adjacent list.
 */
AdjacencyListPtr graphToAdjacentList(GraphPtr paraPtr) {
	//Allocate space.
	int i, j, tempNum;
	AdjacentNodePtr p, q;
	tempNum = paraPtr->numNodes;
	AdjacencyListPtr resultPtr = (AdjacencyListPtr)malloc(sizeof(struct AdjacencyList));
	resultPtr->numNodes = tempNum;
	resultPtr->headers = (AdjacencyNode*)malloc(tempNum * sizeof(struct AdjacencyNode));
	
	//Fill the data.
	for (i = 0; i < tempNum; i ++) {
		//Initialize headers.
		p = &(resultPtr->headers[i]);
		p->column = -1;
		p->next = NULL;

		for (j = 0; j < tempNum; j ++) {
			if (paraPtr->connections[i][j] > 0) {
				//Create a new node.
				q = (AdjacentNodePtr)malloc(sizeof(struct AdjacencyNode));
				q->column = j;
				q->next = NULL;

				//Link.
				p->next = q;
				p = q;
			}//Of if
		}//Of for j
	}//Of for i

	return resultPtr;
}//Of graphToAdjacentList

/**
 * Print an adjacent list.
 */
void printAdjacentList(AdjacencyListPtr paraPtr) {
	int i;
	AdjacentNodePtr p;
	int tempNum = paraPtr->numNodes;

	printf("This is the graph:\r\n");
	for (i = 0; i < tempNum; i ++) {
		p = paraPtr->headers[i].next;
		while (p != NULL) {
			printf("%d, ", p->column);
			p = p->next;
		}//Of while
		printf("\r\n");
	}//Of for i
}//Of printAdjacentList

/**
 * Width first tranverse.
 */
void widthFirstTranverse(AdjacencyListPtr paraListPtr, int paraStart){
	printf("width first \r\n");
	//Use a queue to manage the pointers
	int i, j, tempNode;
	AdjacentNodePtr p;
	i = 0;

	//Initialize data
	visitedPtr = (int*) malloc(paraListPtr->numNodes * sizeof(int));
	
	for (i = 0; i < paraListPtr->numNodes; i ++) {
		visitedPtr[i] = 0;
	}//Of for i

	QueuePtr tempQueuePtr = initQueue();
	printf("%d\t", paraStart);
	visitedPtr[paraStart] = 1;
	enqueue(tempQueuePtr, paraStart);
	// printf("After enqueue\r\n");
	while (!isQueueEmpty(tempQueuePtr)) {
		// printf("First while\r\n");
		tempNode = dequeue(tempQueuePtr);

		for (p = &(paraListPtr->headers[tempNode]); p != NULL; p = p->next) {
			j = p->column;
			// printf("j = %d \r\n", j);
			if (visitedPtr[j]) 
				continue;

			printf("%d\t", j);
			visitedPtr[j] = 1;
			enqueue(tempQueuePtr, j);
		}//Of for
	}//Of while
}//Of widthFirstTranverse

/**
 * Test graph tranverse.
 */
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
	AdjacencyListPtr tempListPtr = graphToAdjacentList(tempGraphPtr);

	printAdjacentList(tempListPtr);

	widthFirstTranverse(tempListPtr, 4);
}//Of testGraphTranverse

int main(){
	testGraphTranverse();
	return 1;
}//Of main

