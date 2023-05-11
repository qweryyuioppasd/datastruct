#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define Hen 4
#define Shu 5


typedef struct TwoDArray{
	int hen;
	int shu;
	int** elements;
} TwoDArray, *TwoDArrayPtr;


typedef struct TwoDStaticArray{
	int hen;
	int shu;
	int elements[Hen][Shu];
} TwoDStaticArray, *TwoDStaticArrayPtr;

//初始化矩阵 
TwoDArrayPtr initTwoDArray(int parahen, int parashu){
	int i;
	TwoDArrayPtr resultPtr = (TwoDArrayPtr)malloc(sizeof(struct TwoDArray));
	resultPtr->hen = parahen;
	resultPtr->shu = parashu;
	resultPtr->elements = (int**)malloc(parahen * sizeof(int*));
	for (i = 0; i < parahen; i ++){
		resultPtr->elements[i] = (int*)malloc(parashu * sizeof(int));
	}

	return resultPtr;
}

//随机化 
void randomizeTwoDArray(TwoDArrayPtr paraPtr, int paraLowerBound, int paraUpperBound){
	int i, j;	
	for (i = 0; i < paraPtr->hen; i ++){
		for (j = 0; j < paraPtr->shu; j ++) {
			paraPtr->elements[i][j] = rand() % (paraUpperBound - paraLowerBound) + paraLowerBound;
		}
	}
}

//打印函数 
void printTwoDArray(TwoDArrayPtr paraPtr){
	int i, j;	
	for (i = 0; i < paraPtr->hen; i ++){
		for (j = 0; j < paraPtr->shu; j ++) {
			printf("%d, ", paraPtr->elements[i][j]);
		}
		printf("\r\n");
	}
}

//矩阵的运算 
TwoDArrayPtr matrixMultiply(TwoDArrayPtr paraPtr1, TwoDArrayPtr paraPtr2){
	int i, j, k, sum;
	if (paraPtr1->shu != paraPtr2->hen){
		printf("Matrices cannot be multiplied.\r\n");
		return NULL;
	}

	TwoDArrayPtr resultPtr = initTwoDArray(paraPtr1->hen, paraPtr2->shu);

	for (i = 0; i < paraPtr1->hen; i ++){
		for (j = 0; j < paraPtr2->shu; j ++) {
			sum = 0;
			for (k = 0; k < paraPtr1->shu; k ++) {
				sum += paraPtr1->elements[i][k] * paraPtr2->elements[k][j];
			}
			resultPtr->elements[i][j] = sum;
			printf("sum = %d, ", sum);
		}
	}

	return resultPtr;
}

//单元测试 
void twoDArrayTest(){
	TwoDArrayPtr tempPtr1, tempPtr2, tempPtr3;
	tempPtr1 = initTwoDArray(3, 2);
	randomizeTwoDArray(tempPtr1, 1, 5);
	printf("The first matrix:\r\n");
	printTwoDArray(tempPtr1);

	tempPtr2 = initTwoDArray(2, 4);
	randomizeTwoDArray(tempPtr2, 4, 9);
	printf("The second matrix:\r\n");
	printTwoDArray(tempPtr2);

	tempPtr3 = matrixMultiply(tempPtr1, tempPtr2);
	printf("The result:\r\n");
	printTwoDArray(tempPtr3);
}//Of twoDArrayTest


//初始化 
TwoDStaticArrayPtr initTwoDStaticArray(){
	int i, j;
	TwoDStaticArrayPtr resultPtr = (TwoDStaticArrayPtr)malloc(sizeof(struct TwoDStaticArray));
	resultPtr->hen = Hen;
	resultPtr->shu = Shu;
	for (i = 0; i < Hen; i ++){
		for (j = 0; j < Shu; j ++) {
			resultPtr->elements[i][j] = i * 10 + j;
		
			printf("(%d, %d): %d; ", i, j, &(resultPtr->elements[i][j]));
		}
	}
	
	return resultPtr;
}

//调用主函数 
int main(){
	twoDArrayTest();
	TwoDStaticArrayPtr tempPtr = initTwoDStaticArray();
	return 0;
}

