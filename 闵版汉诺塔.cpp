#include <stdio.h>

/**
 * Hanoi.
 */
void hanoi(int paraN, char paraSource, char paraDestination, char paraTransit) {
	if (paraN <= 0) {
		return;
	} else {
		hanoi(paraN - 1, paraSource, paraTransit, paraDestination);
		printf("%c -> %c \r\n", paraSource, paraDestination);
		hanoi(paraN - 1, paraTransit, paraDestination, paraSource);
	}// Of if
}// Of hanoi

/**
 * Test the hanoi function.
 */
void hanoiTest() {
    printf("---- addToTest begins. ----\r\n");

	printf("2 plates\r\n");
	hanoi(2, 'A', 'B', 'C');

	printf("3 plates\r\n");
	hanoi(3, 'A', 'B', 'C');

    printf("---- addToTest ends. ----\r\n");
}// Of addToTest

/**
 The entrance.
 */
int main() {
	hanoiTest();
	return 0;
}// Of main

