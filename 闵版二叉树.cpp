#include <stdio.h>
#include <malloc.h>
#define queue_SIZE 5
//���ڵ� 
typedef struct shu{
	char element;
	shu* left;
	shu* right;
}shu, *shuptr;

//���� 
typedef struct shuptrqueue{
	shuptr* nodeptrs;
	int front;
	int rear;
}shuptrqueue, *queueptr;

//���г�ʼ�� 
queueptr initqueue(){
	queueptr resultqueueptr = (queueptr)malloc(sizeof(struct shuptrqueue));
	resultqueueptr->nodeptrs = (shuptr*)malloc(queue_SIZE * sizeof(shuptr));
	resultqueueptr->front = 0;
	resultqueueptr->rear = 1;
	return resultqueueptr;
}

//�ж��Ƿ�Ϊ�� 
bool isqueueEmpty(queueptr paraqueueptr){
	if ((paraqueueptr->front + 1) % queue_SIZE == paraqueueptr->rear) {
		return true;
	}
	return false;
}

//��� 
void enqueue(queueptr paraqueueptr, shuptr parashuptr){
	printf("front = %d, rear = %d.\r\n", paraqueueptr->front, paraqueueptr->rear);
	if ((paraqueueptr->rear + 1) % queue_SIZE == paraqueueptr->front % queue_SIZE) {
		printf("Error, trying to enqueue %c. queue full.\r\n", parashuptr->element);
		return;
	}
	paraqueueptr->nodeptrs[paraqueueptr->rear] = parashuptr;
	paraqueueptr->rear = (paraqueueptr->rear + 1) % queue_SIZE;
	printf("enqueue %c ends.\r\n", parashuptr->element);
}

//�ƶ� 
shuptr dequeue(queueptr paraqueueptr){
	if (isqueueEmpty(paraqueueptr)) {
		printf("�����޷�����\r\n");
		return NULL;
	}

	paraqueueptr->front = (paraqueueptr->front + 1) % queue_SIZE;
	//shuptr tempptr = paraqueueptr->nodeptrs[paraqueueptr->front + 1];
	printf("dequeue %c ends.\r\n", paraqueueptr->nodeptrs[paraqueueptr->front]->element);
	return paraqueueptr->nodeptrs[paraqueueptr->front];
}

/*���ø���Ԫ�ع��� */
shuptr constructshu(char paraChar){
	shuptr resultptr = (shuptr)malloc(sizeof(shu));
	resultptr->element = paraChar;
	resultptr->left = NULL;
	resultptr->right = NULL;
	return resultptr;
}
//������ 
shuptr stringToBTree(char* paraString){
	int i;
	char ch;
	queueptr tempqueueptr = initqueue();
	shuptr resultHeader;
	shuptr tempParent, tempLeftChild, tempRightChild;
	i = 0;
	ch = paraString[i];
	resultHeader = constructshu(ch);
	enqueue(tempqueueptr, resultHeader);
	while(!isqueueEmpty(tempqueueptr)) {
		tempParent = dequeue(tempqueueptr);
		i ++;
		ch = paraString[i];
		if (ch == '#') {
			tempParent->left = NULL;
		} else {
			tempLeftChild = constructshu(ch);
			enqueue(tempqueueptr, tempLeftChild);
			tempParent->left = tempLeftChild;
		}
		i ++;
		ch = paraString[i];
		if (ch == '#') {
			tempParent->right = NULL;
		} else {
			tempRightChild = constructshu(ch);
			enqueue(tempqueueptr, tempRightChild);
			tempParent->right = tempRightChild;
		}
	}
	return resultHeader;
}

//��α��� 
void levelwise(shuptr paraTreeptr){
	char tempString[100];
	int i = 0;
	queueptr tempqueueptr = initqueue();
	shuptr tempNodeptr;
	enqueue(tempqueueptr, paraTreeptr);
	while(!isqueueEmpty(tempqueueptr)) {
		tempNodeptr = dequeue(tempqueueptr);
		tempString[i] = tempNodeptr->element;
		i ++;
		if (tempNodeptr->left != NULL){
			enqueue(tempqueueptr, tempNodeptr->left);
		}
		if (tempNodeptr->right != NULL){
			enqueue(tempqueueptr, tempNodeptr->right);
		}
	}
	tempString[i] = '\0';
	printf("Levelwise: %s\r\n", tempString);
}

//������� 
void preorder(shuptr tempptr){
	if (tempptr == NULL){
		return;
	}
	printf("%c", tempptr->element);
	preorder(tempptr->left);
	preorder(tempptr->right);
}

//������� 
void inorder(shuptr tempptr){
	if (tempptr == NULL) {
		return;
	}
	inorder(tempptr->left);
	printf("%c", tempptr->element);
	inorder(tempptr->right);
}

//�������� 
void postorder(shuptr tempptr){
	if (tempptr == NULL) {
		return;
	}
	postorder(tempptr->left);
	postorder(tempptr->right);
	printf("%c", tempptr->element);
}

//���������� 
int main(){
	shuptr tempHeader;
	tempHeader = constructshu('c');
	printf("��ִ�в���: ");
	preorder(tempHeader);
	printf("\r\n");
	char* tempString = "acde#bf######";
	tempHeader = stringToBTree(tempString);
	printf("�������: ");
	preorder(tempHeader);
	printf("\r\n");
	printf("�������: ");
	inorder(tempHeader);
	printf("\r\n");
	printf("��������: ");
	postorder(tempHeader);
	printf("\r\n");
	printf("��α���: ");
	levelwise(tempHeader);
	printf("\r\n");
	return 1;
}
