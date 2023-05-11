#include <stdio.h>
#include <malloc.h>

typedef int elem;
typedef struct Triple{
    int i;
    int j;
    elem e;
} Triple, *TriplePtr;
typedef struct matrix{
    int heng,shu,numElements;
    Triple* elements;
} matrix, *matrixPtr;

//初始化 
matrixPtr initmatrix(int paraheng, int parashu, int paraElements, int** paraData){
	int i;
	matrixPtr resultPtr = (matrixPtr)malloc(sizeof(struct matrix));
	resultPtr->heng = paraheng;
	resultPtr->shu = parashu;
	resultPtr->numElements = paraElements;
	resultPtr->elements = (TriplePtr)malloc(paraElements * sizeof(struct Triple));

	for(i = 0; i < paraElements; i ++){
		resultPtr->elements[i].i = paraData[i][0];
		resultPtr->elements[i].j = paraData[i][1];
		resultPtr->elements[i].e = paraData[i][2];
	}
	return resultPtr;
}

//打印 
void printmatrix(matrixPtr paraPtr){
	int i;
	for(i = 0; i < paraPtr->numElements; i ++){
		printf("(%d, %d): %d\r\n", paraPtr->elements[i].i, paraPtr->elements[i].j, paraPtr->elements[i].e);
	}
}


matrixPtr transposematrix(matrixPtr paraPtr){
	int i, tempColumn, tempPosition;
	int *tempColumnCounts = (int*)malloc(paraPtr->shu * sizeof(int));
	int *tempOffsets = (int*)malloc(paraPtr->shu * sizeof(int));
	for(i = 0; i < paraPtr->shu; i ++){
		tempColumnCounts[i] = 0;
	}
	matrixPtr resultPtr = (matrixPtr)malloc(sizeof(struct matrix));
	resultPtr->heng = paraPtr->shu;
	resultPtr->shu = paraPtr->heng;
	resultPtr->numElements = paraPtr->numElements;
	resultPtr->elements = (TriplePtr)malloc(paraPtr->numElements * sizeof(struct Triple));
	for(i = 0; i < paraPtr->numElements; i ++) {
		tempColumnCounts[paraPtr->elements[i].j] ++;
	}
	tempOffsets[0] = 0;
	for(i = 1; i < paraPtr->shu; i ++){
		tempOffsets[i] = tempOffsets[i - 1] + tempColumnCounts[i - 1];
		printf("[%d] = %d \r\n", i, tempOffsets[i]);
	}
	for(i = 0; i < paraPtr->numElements; i ++) {
		tempColumn = paraPtr->elements[i].j;
		tempPosition = tempOffsets[tempColumn];
		resultPtr->elements[tempPosition].i = paraPtr->elements[i].j;
		resultPtr->elements[tempPosition].j = paraPtr->elements[i].i;
		resultPtr->elements[tempPosition].e = paraPtr->elements[i].e;

		tempOffsets[tempColumn]++;
	}

	return resultPtr;
}

//单元测试 
void matrixTest(){
	matrixPtr tempPtr1, tempPtr2;
	int i, j, tempElements;
	tempElements = 4;
	int** tempMatrix1 = (int**)malloc(tempElements * sizeof(int*));
	for(i = 0; i < tempElements; i ++){
		tempMatrix1[i] = (int*)malloc(3 * sizeof(int));
	}
	int tempMatrix2[4][3] = {{0, 0, 2}, {0, 2, 3}, {2, 0, 5}, {2, 1, 6}};
	for(i = 0; i < tempElements; i ++){
		for(j = 0; j < 3; j ++) {
			tempMatrix1[i][j] = tempMatrix2[i][j];
		}
	}
	
	tempPtr1 = initmatrix(2, 3, 4, tempMatrix1);

	printf("After initialization.\r\n");
	printmatrix(tempPtr1);

	tempPtr2 = transposematrix(tempPtr1);
	printf("After transpose.\r\n");
	printmatrix(tempPtr2);
}

int main(){
	matrixTest();
	return 1;
}

