#include <stdio.h>

/**
 * Recursive addition.
 */
int addTo(int paraN) {
	int tempSum;
	printf("entering addTo(%d)\r\n", paraN);
	if (paraN <= 0) {
		printf(" return 0\r\n");
		return 0;
	} else {
		tempSum = addTo(paraN - 1) + paraN;
		printf(" return %d\r\n", tempSum);
		return tempSum;
	}// Of if
}// Of addTo

/**
 * A clear version.
 */
int clearAddTo(int paraN) {
	if (paraN <= 0) {
		return 0;
	} else {
		return clearAddTo(paraN - 1) + paraN;
	}// Of if
}// Of clearAddTo

/**
 * Test the addTo function.
 */
void addToTest() {
	int n, sum;
    printf("---- addToTest begins. ----\r\n");

	n = 5;
	sum = addTo(n);
    printf("\r\n0 adds to %d gets %d.\r\n", n, sum);

	n = 1;
	sum = addTo(n);
    printf("\r\n0 adds to %d gets %d.\r\n", n, sum);

	n = -1;
	sum = addTo(n);
    printf("\r\n0 adds to %d gets %d.\r\n", n, sum);


    printf("---- addToTest ends. ----\r\n");
}// Of addToTest

/**
 The entrance.
 */
int main() {
	addToTest();
	return 0;
}// Of main

