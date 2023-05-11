#include<stdio.h>
#include<malloc.h>
#define max_size 10

typedef struct list{
	int actullength;
	int data[max_size];
}*listptr;

void printlist(listptr paralist)
{
	int i=0;
	for(i=0;i<paralist->actullength;i++)
	{
		printf("%d ",paralist->data[i]);
	}
	printf("\r\n");
}

listptr initlist(int paradata[],int paralength)
{
	listptr resultptr=(listptr)malloc(sizeof(list));
	int i; 
	for(i=0;i<paralength;i++)
	{
		resultptr->data[i]=paradata[i];
	}
	resultptr->actullength=paralength;
	return resultptr;
}

void insertlist(listptr paralistptr,int paraposition,int paravalue)
{
	if((paralistptr->actullength>=max_size)&&(paraposition<0)&&(paraposition>paralistptr->actullength))
	{
		printf("Error!\n");
	}
		for(int i=paralistptr->actullength;i>paraposition;i--)
		{
			paralistptr->data[i]=paralistptr->data[i-1];
		}
			paralistptr->data[paraposition]=paravalue;
			paralistptr->actullength++;
	
}


int getvalueinlist(listptr paralistptr,int value)
{
	int i;
	for(i=0;i<paralistptr->actullength;i++)
	{
		if(paralistptr->data[i]==value)
		{
			return i;
		}
	}
	return -1;
}


int findpositionlist(listptr paralistptr,int paraposition)
{
	int i;
	if((paraposition<0)&&(paralistptr->actullength<=paraposition))
	{
		printf("Error!\n");
		return -1;
	}
	else
	{
		return paralistptr->data[paraposition];
	}
}


void deletkeyinlist(listptr paralistptr,int paraposition)
{
	if((paraposition>=paralistptr->actullength)&&(paraposition<0))
	{
		printf("Error!\n");
	}
	else
	{
		int i;
		for(i=paraposition;i<paralistptr->actullength;i++)
		{
			paralistptr->data[i]=paralistptr->data[i+1];
		}
		paralistptr->actullength--;
	}
}

void cleanlist(listptr paralistptr)
{
	paralistptr->actullength=0;
}

void outputMemory(listptr paraListPtr) {
    printf("The address of the structure: %ld\r\n", paraListPtr);
    printf("The address of actualLength: %ld\r\n", &paraListPtr->actullength);
    printf("The address of data: %ld\r\n", &paraListPtr->data);
    printf("The address of actual data: %ld\r\n", &paraListPtr->data[0]);
    printf("The address of second data: %ld\r\n", &paraListPtr->data[1]);
}

void sequentialInsertTest() {
	int i;
	int tempArray[5] = {3, 5, 2, 7, 4};

    printf("---- sequentialInsertTest begins. ----\r\n");

	// Initialize.
    tempList = listptr initlist(tempArray, 5);
    printf("After initialization, the list is: ");
	printlist(tempList);

	// Insert to the first.
    printf("Now insert to the first, the list is: ");
	insertlist(tempList, 0, 8);
	printlist(tempList);

	// Insert to the last.
    printf("Now insert to the last, the list is: ");
	insertlist(tempList, 6, 9);
	printlist(tempList);

	// Insert beyond the tail.
    printf("Now insert beyond the tail. \r\n");
	insertlist(tempList, 8, 9);
    printf("The list is:");
	printlist(tempList);

	// Insert to position 3.
	for (i = 0; i < 5; i ++) {
		printf("Inserting %d.\r\n", (i + 10));
		insertlist(tempList, 0, (i + 10));
		printlist(tempList);
	}//Of for i

    printf("---- sequentialInsertTest ends. ----\r\n");
}// Of sequentialInsertTest


void sequentialDeleteTest() {
	int tempArray[5] = {3, 5, 2, 7, 4};

    printf("---- sequentialDeleteTest begins. ----\r\n");

	// Initialize.
    listptrtempList = listptr initlist(tempArray, 5);
    printf("After initialization, the list is: ");
	printlist(tempList);

	// Delete the first.
    printf("Now delete the first, the list is: ");
deletkeyinlist(tempList, 0);
	printlist(tempList);

	// Delete to the last.
    printf("Now delete the last, the list is: ");
deletkeyinlist(tempList, 3);
	printlist(tempList);

	// Delete the second.
    printf("Now delete the second, the list is: ");
deletkeyinlist(tempList, 1);
	printlist(tempList);

	// Delete the second.
    printf("Now delete the 5th, the list is: ");
deletkeyinlist(tempList, 5);
	printlist(tempList);

	// Delete the second.
    printf("Now delete the (-6)th, the list is: ");
deletkeyinlist(tempList, -6);
	printlist(tempList);

    printf("---- sequentialDeleteTest ends. ----\r\n");

	outputMemory(tempList);
}// Of sequentialDeleteTest

int main() {
	sequentialInsertTest();
	sequentialDeleteTest();
	return 0;
}// Of main

