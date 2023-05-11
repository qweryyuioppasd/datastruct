#include <stdio.h>
#include <malloc.h>

#define STACK_MAX_SIZE 10

typedef struct CharStack {
    int top;

    int data[STACK_MAX_SIZE]; 
} *CharStackPtr;


void outputStack(CharStackPtr paraStack) {
    for (int i = 0; i <= paraStack->top; i ++) {
        printf("%c ", paraStack->data[i]);
    }
    printf("\r\n");
}

CharStackPtr charStackInit() {
	CharStackPtr resultPtr = (CharStackPtr)malloc(sizeof(struct CharStack));
	resultPtr->top = -1;

	return resultPtr;
}


void push(CharStackPtr paraStackPtr, int paraValue) {
    if (paraStackPtr->top >= STACK_MAX_SIZE - 1) {
        printf("Cannot push element: stack full.\r\n");
        return;
    }
	paraStackPtr->top ++;
    paraStackPtr->data[paraStackPtr->top] = paraValue;
}


char pop(CharStackPtr paraStackPtr) {
    if (paraStackPtr->top < 0) {
        printf("Cannot pop element: stack empty.\r\n");
        return '\0';
    }
	paraStackPtr->top --;
    return paraStackPtr->data[paraStackPtr->top + 1];
}
void pushPopTest() {
    printf("---- pushPopTest begins. ----\r\n");
    CharStackPtr tempStack = charStackInit();
    printf("After initialization, the stack is: ");
	outputStack(tempStack);
	for (char ch = 'a'; ch < 'm'; ch ++) {
		printf("Pushing %c.\r\n", ch);
		push(tempStack, ch);
		outputStack(tempStack);
	}
      char ch;

	for (int i = 0; i < 3; i ++) {
		ch = pop(tempStack);
		printf("Pop %c.\r\n", ch);
		outputStack(tempStack);
	}

    printf("---- pushPopTest ends. ----\r\n");
    printf("********************************************************************\r\n"); 
}
bool bracketMatching(char* paraString, int paraLength) {
    CharStackPtr tempStack = charStackInit();
	push(tempStack, '#');
	char tempChar, tempPopedChar;
	for (int i = 0; i < paraLength; i++) {
		tempChar = paraString[i];

		switch (tempChar) {
		case '(':
		case '[':
		case '{':
			push(tempStack, tempChar);
			break;
		case ')':
			tempPopedChar = pop(tempStack);
			if (tempPopedChar != '(') {
				return false;
			} 
			break;
		case ']':
			tempPopedChar = pop(tempStack);
			if (tempPopedChar != '[') {
				return false;
			} 
			break;
		case '}':
			tempPopedChar = pop(tempStack);
			if (tempPopedChar != '{') {
				return false;
			} 
			break;
		default:
			break;
		}
	}

	tempPopedChar = pop(tempStack);
	if (tempPopedChar != '#') {
		return false;
	} 
	return true;
}


void bracketMatchingTest() {
	char* tempExpression = "[2 + (1 - 3)] * 4";
	bool tempMatch = bracketMatching(tempExpression, 17);
	printf("Is the expression '%s' bracket matching? %d \r\n", tempExpression, tempMatch);


	tempExpression = "( )  )";
	tempMatch = bracketMatching(tempExpression, 6);
	printf("Is the expression '%s' bracket matching? %d \r\n", tempExpression, tempMatch);

	tempExpression = "()()(())";
	tempMatch = bracketMatching(tempExpression, 8);
	printf("Is the expression '%s' bracket matching? %d \r\n", tempExpression, tempMatch);

	tempExpression = "({}[])";
	tempMatch = bracketMatching(tempExpression, 6);
	printf("Is the expression '%s' bracket matching? %d \r\n", tempExpression, tempMatch);


	tempExpression = ")(";
	tempMatch = bracketMatching(tempExpression, 2);
	printf("Is the expression '%s' bracket matching? %d \r\n", tempExpression, tempMatch);
}


int main() {
	 pushPopTest();
	 bracketMatchingTest();
	return 0;
}

