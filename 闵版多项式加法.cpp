#include <stdio.h>
#include <malloc.h>


typedef struct LinkNode{
	int coefficient;
	int exponent;
	struct LinkNode *next;
} *LinkList, *NodePtr;

//初始化表 
LinkList initLinkList(){
	LinkList tempHeader = (LinkList)malloc(sizeof(struct LinkNode));
	tempHeader->coefficient = 0;
	tempHeader->exponent = 0;
	tempHeader->next = NULL;
	return tempHeader;
}

//打印函数(1) 
void printList(LinkList paraHeader){
	NodePtr p = paraHeader->next;
	while (p != NULL) {
		printf("%d * 10^%d + ", p->coefficient, p->exponent);
		p = p->next;
	}
	printf("\r\n");
}

//打印函数(2) 
void printNode(NodePtr paraPtr, char paraChar){
	if (paraPtr == NULL) {
		printf("NULL\r\n");
	} else {
		printf("The element of %c is (%d * 10^%d)\r\n", paraChar, paraPtr->coefficient, paraPtr->exponent);
	}
}

//添加 
void appendElement(LinkList paraHeader, int paraCoefficient, int paraExponent){
	NodePtr p, q;
	q = (NodePtr)malloc(sizeof(struct LinkNode));
	q->coefficient = paraCoefficient;
	q->exponent = paraExponent;
	q->next = NULL;
	p = paraHeader;
	while (p->next != NULL) {
		p = p->next;
	}
	p->next = q;
}

//加合 
void add(NodePtr paraList1, NodePtr paraList2){
	NodePtr p, q, r, s;
	p = paraList1->next;
	printNode(p, 'p');
	q = paraList2->next;
	printNode(q, 'q');
	r = paraList1; 
	printNode(r, 'r');
	free(paraList2); 
	
	while ((p != NULL) && (q != NULL)) {
		if (p->exponent < q->exponent) {
			printf("case 1\r\n");
			r = p;
			printNode(r, 'r');
			p = p->next;
			printNode(p, 'p');
		} else if ((p->exponent > q->exponent)) {
			printf("case 2\r\n");
			r->next = q;
			r = q;
			printNode(r, 'r');
			q = q->next;
			printNode(q, 'q');
		} else {
			printf("case 3\r\n");
			p->coefficient = p->coefficient + q->coefficient;
			printf("The coefficient is: %d.\r\n", p->coefficient);
			if (p->coefficient == 0) {
				printf("case 3.1\r\n");
				s = p;
				p = p->next;
				printNode(p, 'p');
			} else {
				printf("case 3.2\r\n");
				r = p;
				printNode(r, 'r');
				p = p->next;
				printNode(p, 'p');
			}
			s = q;
			q = q->next;
			free(s);
		}

		printf("p = %ld, q = %ld \r\n", p, q);
	} 
	printf("End of while.\r\n");

	if (p == NULL) {
		r->next = q;
	} else {
		r->next = p;
	} 

	printf("Addition ends.\r\n");
}
//单元测试 
void additionTest(){
	LinkList tempList1 = initLinkList();
	appendElement(tempList1, 7, 0);
	appendElement(tempList1, 3, 1);
	appendElement(tempList1, 9, 8);
	appendElement(tempList1, 5, 17);
	printList(tempList1);
	LinkList tempList2 = initLinkList();
	appendElement(tempList2, 8, 1);
	appendElement(tempList2, 22, 7);
	appendElement(tempList2, -9, 8);
	printList(tempList2);
	add(tempList1, tempList2);
	printList(tempList1);
}
//主函数 
int main(){
	additionTest();
	printf("Finish.\r\n");
	return 0; 
}


