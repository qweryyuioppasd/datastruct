#include <stdio.h>
#include <malloc.h>

#define LIST_MAX_LENGTH 10

/**
 * Linear list of integers. The key is data.
 */
typedef struct SequentialList {
    int actualLength;

    int data[LIST_MAX_LENGTH]; //The maximum length is fixed.
} *SequentialListPtr;

/**
 * Output the list.
 */
void outputList(SequentialListPtr paraList) {
    for(int i = 0; i < paraList->actualLength; i ++) {
        printf("%d ", paraList->data[i]);
    }// Of for i
    printf("\r\n");
}// Of outputList

/**
 * Output the memeory for the list.
 */
void outputMemory(SequentialListPtr paraListPtr) {
    printf("The address of the structure: %ld\r\n", paraListPtr);
    printf("The address of actualLength: %ld\r\n", &paraListPtr->actualLength);
    printf("The address of data: %ld\r\n", &paraListPtr->data);
    printf("The address of actual data: %ld\r\n", &paraListPtr->data[0]);
    printf("The address of second data: %ld\r\n", &paraListPtr->data[1]);
}// Of outputMemory

/**
 * Initialize a sequential list. No error checking for this function.
 * @param paraListPtr The pointer to the list. It must be a pointer to change the list.
 * @param paraValues An int array storing all elements.
 */
SequentialListPtr sequentialListInit(int paraData[], int paraLength) {
	SequentialListPtr resultPtr = (SequentialListPtr)malloc(sizeof(SequentialList));
	for (int i = 0; i < paraLength; i ++) {
		resultPtr->data[i] = paraData[i];
	}// Of for i
	resultPtr->actualLength = paraLength;

	return resultPtr;
}//Of sequentialListInit

/**
 * Insert an element into a sequential linear list.
 * @param paraListPtr The pointer to the list. It must be a pointer to change the list.
 * @param paraPosition The position, e.g., 0 stands for inserting at the first position.
 * @param paraValue The value to be inserted.
 */
void sequentialListInsert(SequentialListPtr paraListPtr, int paraPosition, int paraValue) {
    // Step 1. Space check.
    if (paraListPtr->actualLength >= LIST_MAX_LENGTH) {
        printf("Cannot insert element: list full.\r\n");
        return;
    }//Of if

    // Step 2. Position check.
    if (paraPosition < 0) {
        printf("Cannot insert element: negative position unsupported.");
        return;
    }//Of if
    if (paraPosition > paraListPtr->actualLength) {
        printf("Cannot insert element: the position %d is bigger than the list length %d.\r\n", paraPosition, paraListPtr->actualLength);
        return;
    }//Of if

    // Step 3. Move the remaining part.
    for (int i = paraListPtr->actualLength; i > paraPosition; i --) {
        paraListPtr->data[i] = paraListPtr->data[i - 1];
    }//Of for i

    // Step 4. Insert.
    paraListPtr->data[paraPosition] = paraValue;

    // Step 5. Update the length.
    paraListPtr->actualLength ++;
}// Of sequentialListInsert

/**
 * Test the insert function.
 */
void sequentialInsertTest() {
	int i;
	int tempArray[5] = {3, 5, 2, 7, 4};

    printf("---- sequentialInsertTest begins. ----\r\n");

	// Initialize.
    SequentialListPtr tempList = sequentialListInit(tempArray, 5);
    printf("After initialization, the list is: ");
	outputList(tempList);

	// Insert to the first.
    printf("Now insert to the first, the list is: ");
	sequentialListInsert(tempList, 0, 8);
	outputList(tempList);

	// Insert to the last.
    printf("Now insert to the last, the list is: ");
	sequentialListInsert(tempList, 6, 9);
	outputList(tempList);

	// Insert beyond the tail.
    printf("Now insert beyond the tail. \r\n");
	sequentialListInsert(tempList, 8, 9);
    printf("The list is:");
	outputList(tempList);

	// Insert to position 3.
	for (i = 0; i < 5; i ++) {
		printf("Inserting %d.\r\n", (i + 10));
		sequentialListInsert(tempList, 0, (i + 10));
		outputList(tempList);
	}//Of for i

    printf("---- sequentialInsertTest ends. ----\r\n");
}// Of sequentialInsertTest

/**
 * Delete an element from a sequential linear list.
 * @param paraListPtr The pointer to the list. It must be a pointer to change the list.
 * @param paraPosition The position, e.g., 0 stands for inserting at the first position.
 * @return The deleted value.
 */
int sequentialListDelete(SequentialListPtr paraListPtr, int Position){
	if(Position>=paraListPtr->actualLength){
		printf("too big,no delete\n");
		return -1;
	}
	if(Position<0){
		printf("too small,no delete\n");
	}
	for(int i=Position;i<paraListPtr->actualLength;i++){
		paraListPtr->data[i]=paraListPtr->data[i+1];
	}
	paraListPtr->actualLength--;
}
void sequentialDeleteTest() {
	int tempArray[5] = {3, 5, 2, 7, 4};

    printf("---- sequentialDeleteTest begins. ----\r\n");

	// Initialize.
    SequentialListPtr tempList = sequentialListInit(tempArray, 5);
    printf("After initialization, the list is: ");
	outputList(tempList);

	// Delete the first.
    printf("Now delete the first, the list is: ");
	sequentialListDelete(tempList, 0);
	outputList(tempList);

	// Delete to the last.
    printf("Now delete the last, the list is: ");
	sequentialListDelete(tempList, 3);
	outputList(tempList);

	// Delete the second.
    printf("Now delete the second, the list is: ");
	sequentialListDelete(tempList, 1);
	outputList(tempList);

	// Delete the second.
    printf("Now delete the 5th, the list is: ");
	sequentialListDelete(tempList, 5);
	outputList(tempList);

	// Delete the second.
    printf("Now delete the (-6)th, the list is: ");
	sequentialListDelete(tempList, -6);
	outputList(tempList);

    printf("---- sequentialDeleteTest ends. ----\r\n");

	outputMemory(tempList);
}// Of sequentialDeleteTest

/**
 * Locate an element in the list.
 * @param paraListPtr The pointer to the list.
 * @param paraValue the indicated value.
 * @return The position of the value, or  -1 indicating not exists
 */
int locateElement(SequentialListPtr paraListPtr,int value){
	for(int i=0;i<paraListPtr->actualLength;i++){
		if(paraListPtr->data[i]==value){
			return i;
		}
	}
	return -1;
} 


int getElement(SequentialListPtr paraListPtr,int position){
	if(position<0){
		printf("no get,too small");
		return -1;
	}
	
	if(position>=paraListPtr->actualLength){
		printf("no get,too big");
		return -1;
	}
	return paraListPtr->data[position];
}

/**
 * Clear elements in the list.
 * @param paraListPtr The pointer to the list.
 * @return The position of the value, or  -1 indicating not exists
 */
void clearList(SequentialListPtr paraListPtr) {
	paraListPtr->actualLength = 0;
}// Of clearList

/**
 The entrance.
 */
int main() {
	sequentialInsertTest();
	sequentialDeleteTest();
	return 0;
}// Of main

