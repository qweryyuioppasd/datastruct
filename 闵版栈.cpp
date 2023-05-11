#include <stdio.h>
#include <malloc.h>

#define STACK_MAX_SIZE 10

/**
 * Linear stack of integers. The key is data.
 */
typedef struct CharStack {
    int top;

    int data[STACK_MAX_SIZE]; //The maximum length is fixed.
} *CharStackPtr;

/**
 * Output the stack.
 */
void outputStack(CharStackPtr paraStack) {
    for (int i = 0; i <= paraStack->top; i ++) {
        printf("%c ", paraStack->data[i]);
    }// Of for i
    printf("\r\n");
}// Of outputStack

/**
 * Initialize an empty char stack. No error checking for this function.
 * @param paraStackPtr The pointer to the stack. It must be a pointer to change the stack.
 * @param paraValues An int array storing all elements.
 */
CharStackPtr charStackInit() {
	CharStackPtr resultPtr = (CharStackPtr)malloc(sizeof(CharStack));
	resultPtr->top = -1;

	return resultPtr;
}//Of charStackInit

/**
 * Push an element to the stack.
 * @param paraValue The value to be pushed.
 */
void push(CharStackPtr paraStackPtr, int paraValue) {
    // Step 1. Space check.
    if (paraStackPtr->top >= STACK_MAX_SIZE - 1) {
        printf("Cannot push element: stack full.\r\n");
        return;
    }//Of if

    // Step 2. Update the top.
	paraStackPtr->top ++;

	// Step 3. Push element.
    paraStackPtr->data[paraStackPtr->top] = paraValue;
}// Of push

/**
 * Pop an element from the stack.
 * @return The poped value.
 */
char pop(CharStackPtr paraStackPtr) {
    // Step 1. Space check.
    if (paraStackPtr->top < 0) {
        printf("Cannot pop element: stack empty.\r\n");
        return '\0';
    }//Of if

    // Step 2. Update the top.
	paraStackPtr->top --;

	// Step 3. Push element.
    return paraStackPtr->data[paraStackPtr->top + 1];
}// Of pop

/**
 * Test the push function.
 */
void pushPopTest() {
    printf("---- pushPopTest begins. ----\r\n");

	// Initialize.
    CharStackPtr tempStack = charStackInit();
    printf("After initialization, the stack is: ");
	outputStack(tempStack);

	// Pop.
	char ch;
	for ( ch = 'a'; ch < 'm'; ch ++) {
		printf("Pushing %c.\r\n", ch);
		push(tempStack, ch);
		outputStack(tempStack);
	}//Of for i

	// Pop.
	int i;
	for ( i = 0; i < 3; i ++) {
		ch = pop(tempStack);
		printf("Pop %c.\r\n", ch);
		outputStack(tempStack);
	}//Of for i

    printf("---- pushPopTest ends. ----\r\n");
}// Of pushPopTest

/**
 The entrance.
 */
int main() {
	pushPopTest();
	return 0;
}// Of main

