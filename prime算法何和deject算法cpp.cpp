#include <stdio.h>
#include <malloc.h>

#define MAX_DISTANCE 10000

/**
 * The structure of a Net.
 */
typedef struct Net{
	int** weights;
	int numNodes;
} *NetPtr;

/**
 * Initialize a Net.
 */
NetPtr initNet(int paraSize, int** paraData) {
	int i, j;
	NetPtr resultPtr = (NetPtr)malloc(sizeof(Net));
	resultPtr -> numNodes = paraSize;
	//Two stage space allocation.
	resultPtr->weights = (int**)malloc(paraSize * sizeof(int*));
	for (i = 0; i < paraSize; i ++) {
		resultPtr -> weights[i] = (int*)malloc(paraSize * sizeof(int));
		for (j = 0; j < paraSize; j ++) {
			resultPtr -> weights[i][j] = paraData[i][j];
		}//Of for j
	}//Of for i
	
	return resultPtr;
}//Of initNet

/**
 * The Prim algorithm for spanning tree, or the Dijkstra algorithm for nearest path.
 * @param paraAlgorithm 0 for Dijkstra, 1 for Prim
 * @return The total cost of the tree.
 */
int dijkstraOrPrim(NetPtr paraPtr, int paraAlgorithm) {
	int i, j, minDistance, tempBestNode, resultCost;
	int source = 0;
	int numNodes = paraPtr->numNodes;
	int *distanceArray = (int*)malloc(numNodes * sizeof(int));
	int *parentArray = (int*)malloc(numNodes * sizeof(int));
	//Essentially boolean
	int *visitedArray = (int*)malloc(numNodes * sizeof(int)); 

	// Step 1. Initialize. Any node can be the source.
	for (i = 0; i < numNodes; i++) {
		distanceArray[i] = paraPtr->weights[source][i];
		parentArray[i] = source;
		visitedArray[i] = 0;
	} // Of for i
	distanceArray[source] = 0;
	parentArray[source] = -1;
	visitedArray[source] = 1;

	// Step 2. Main loops.
	tempBestNode = -1;
	for (i = 0; i < numNodes - 1; i++) {
		// Step 2.1 Find out the best next node.
		minDistance = MAX_DISTANCE;
		for (j = 0; j < numNodes; j++) {
			// This node is visited.
			if (visitedArray[j]) {
				continue;
			} // Of if

			if (minDistance > distanceArray[j]) {
				minDistance = distanceArray[j];
				tempBestNode = j;
			} // Of if
		} // Of for j

		visitedArray[tempBestNode] = 1;

		// Step 2.2 Prepare for the next round.
		for (j = 0; j < numNodes; j++) {
			// This node is visited.
			if (visitedArray[j]) {
				continue;
			} // Of if

			// This node cannot be reached.
			if (paraPtr->weights[tempBestNode][j] >= MAX_DISTANCE) {
				continue;
			} // Of if

			// Attention: the difference between Dijkstra and Prim algorithms.
			if (paraAlgorithm == 0) {
				if (distanceArray[j] > distanceArray[tempBestNode] + paraPtr->weights[tempBestNode][j]) {
					// Change the distance.
					distanceArray[j] = distanceArray[tempBestNode] + paraPtr->weights[tempBestNode][j];
					// Change the parent.
					parentArray[j] = tempBestNode;
				} // Of if
			} else {
				if (distanceArray[j] > paraPtr->weights[tempBestNode][j]) {
					// Change the distance.
					distanceArray[j] = paraPtr->weights[tempBestNode][j];
					// Change the parent.
					parentArray[j] = tempBestNode;
				} // Of if
			}//Of if
		} // Of for j
	} // Of for i

	printf("the parent of each node: ");
	for (i = 0; i < numNodes; i++) {
		printf("%d, ", parentArray[i]);
	} // Of for i

	if (paraAlgorithm == 0) {
		printf("From node 0, path length to all nodes are: ");
		for (i = 0; i < numNodes; i++) {
			printf("%d (%d), ", i, distanceArray[i]);
		} // Of for i
	} else {
		resultCost = 0;
		for (i = 0; i < numNodes; i++) {
			resultCost += distanceArray[i];
			printf("cost of node %d is %d, total = %d\r\n", i, distanceArray[i], resultCost);
		} // Of for i
		printf("Finally, the total cost is %d.\r\n ", resultCost);
	}//Of if

	// Step 3. Output for debug.
	printf("\r\n");

	return resultCost;
}// Of dijkstraOrPrim

/**
 * Construct a sample net.
 * Revised from testGraphTranverse().
 */
NetPtr constructSampleNet() {
	int i, j;
	int myGraph[6][6] = { 
		{0, 6, 1, 5, 0, 0},
		{6, 0, 5, 0, 3, 0}, 
		{1, 5, 0, 5, 6, 4}, 
		{5, 0, 5, 0, 0, 2}, 
		{0, 3, 6, 0, 0, 6},
		{0, 0, 4, 2, 6, 0}};
	int** tempPtr;
	int numNodes = 6;
	printf("Preparing data\r\n");
		
	tempPtr = (int**)malloc(numNodes * sizeof(int*));
	for (i = 0; i < numNodes; i ++) {
		tempPtr[i] = (int*)malloc(numNodes * sizeof(int));
	}//Of for i
	 
	for (i = 0; i < numNodes; i ++) {
		for (j = 0; j < numNodes; j ++) {
			if (myGraph[i][j] == 0) {
				tempPtr[i][j] = MAX_DISTANCE;
			} else {
				tempPtr[i][j] = myGraph[i][j];
			}//Of if
		}//Of for j
	}//Of for i
 
	printf("Data ready\r\n");
	
	NetPtr resultNetPtr = initNet(numNodes, tempPtr);
	return resultNetPtr;
}//Of constructSampleNet

/**
 * Test the Prim algorithm.
 */
void testPrim() {
	NetPtr tempNetPtr = constructSampleNet();
	printf("=====Dijkstra algorithm=====\r\n");
	dijkstraOrPrim(tempNetPtr, 0);
	printf("=====Prim algorithm=====\r\n");
	dijkstraOrPrim(tempNetPtr, 1);
}//Of testPrim

/**
 * The entrance.
 */
int main(){
	testPrim();
	return 1;
}//Of main

